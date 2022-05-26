#include "EntityComponents.h"


//===TOXICOLOGY===//

// .5 Game Hours = 1 Real Life Minutes
const float Toxicology::lastHighMax = 30.f;

// 3 Game Minutes = 6 Real Life Seconds
const float Toxicology::cdHighMax = 6.f;

Toxicology::Toxicology()
{
	// Last High Default | Default is Last High Max + 1.f
	this->lastHigh = sf::seconds(this->lastHighMax + 1.f);

	// Tolerance default
	this->tolerance = 1.0;

	// Sobriety default
	this->sobriety = 0;
}

Toxicology::~Toxicology()
{
}

void Toxicology::getHigh()
{
	// The higher your tolerance, the less the drugs will effect
	this->sobriety -= 100 / this->tolerance;
	this->tolerance = percentRange(this->tolerance, 0.015);
	this->lastHigh = sf::seconds(0.f); // RESET


	// Sobriety can't be less than -100
	if (this->sobriety < -100.0)
	{
		this->sobriety = -100.0;
	}
}

void Toxicology::update(const float& dt)
{
	this->cdHigh += sf::seconds(dt);

	// If greater than 3 game minute = 6 real life seconds
	// Every 3 game minutes, your high will be decreased
	if (this->cdHigh.asSeconds() >= this->cdHighMax && this->sobriety < 0)
	{
		this->sobriety += 1 * this->tolerance;
		this->cdHigh -= sf::seconds(this->cdHighMax);
	}
	
	// Sobriety can't be greater than zero
	if (this->sobriety > 0)
	{
		this->sobriety = 0;
	}

	// When the player comes down from their high, the last high meter time increases
	if (this->sobriety >= -20)
	{
		this->lastHigh += sf::seconds(dt);
	}
}

const float Toxicology::getLastHigh() const
{
	return this->lastHigh.asSeconds();
}

const float& Toxicology::getLastHighMax() const
{
	return this->lastHighMax;
}
//---TOXICOLOGY---//


//===PSYCHOLOGY===//

// 8 Game Hours = 16 Real Life Minutes
const float Psychology::cdLastStudyMax = 960.f;

// 4 Game Minutes = 8 Real Life Seconds
const float Psychology::cdStatChangeMax = 8.f;

Psychology::Psychology()
{
	this->intelligence = 55.0;
	this->joy = 80.0;
	this->sadness = 15;
	this->fatigue = 10;

	this->isAsleep = false;
	this->isStudying = false;
}

Psychology::Psychology(Demographic demographic)
{
	this->intelligence = 0;

	switch (demographic)
	{
	case Demographic::LOWER:
		this->intelligence = static_cast<double>(rand() % 11) + 65; // Random from 65 to 75
		break;
	case Demographic::MIDDLE:
		this->intelligence = static_cast<double>(rand() % 21) + 55; // Random from 55 to 75
		break;
	case Demographic::UPPER:
		this->intelligence = static_cast<double>(rand() % 31) + 45; // Random from 45 to 75
		break;
	default:
		break;
	}
	this->joy = roundTo<double>(45.0 / (this->intelligence / 100), 2); // Base joy is 45, the lower your intelligence the higher it will be
	this->sadness = roundTo<double>(25.0 * (this->intelligence / 100), 2); // Base sadness is 25, the higher your intelligence the higher you sadness
	this->fatigue = roundTo<double>(20.0 * (this->intelligence / 100) - (this->joy / 20.0), 2); // Base fatigue is 20, the higher your intelligence and lower your joy, the higehr your fatigue 
	this->isAsleep = false;
	this->isStudying = false;
}

Psychology::~Psychology()
{
}

void Psychology::study()
{
	switch (this->isStudying)
	{
	case true:
		this->isStudying = false;
		break;
	case false:
		this->isStudying = true;
		break;
	default:
		break;
	}
	this->isAsleep = false; // Just Incase
}

void Psychology::sleep()
{
	switch (this->isAsleep)
	{
	case true:
		this->isAsleep = false;
		break;
	case false:
		this->isAsleep = true;
		break;
	default:
		break;
	}
	this->isStudying = false; // Just incase
}

void Psychology::updateStudy(const float& dt, Toxicology& toxic)
{
	if (this->isStudying)
	{
		this->cdIntelligenceIncrementStudy += sf::seconds(dt);
		this->cdFatigueIncrementStudy += sf::seconds(dt);

		if (toxic.getSobriety<double>() >= -10) // Intoxication is neglected in studying if less than 10
		{
			double percent = (static_cast<double>(rand() % 4) + 1.0) / 100;
			if (this->cdIntelligenceIncrementStudy.asSeconds() >= this->cdLastStudyMax)
			{
				this->intelligence = percentRange(this->intelligence, percent);
				this->cdIntelligenceIncrementStudy = sf::seconds(0.f); // RESET COOLDOWN
			}
			if (this->cdFatigueIncrementStudy.asSeconds() >= this->cdLastStudyMax)
			{
				this->fatigue = percentRange(this->fatigue, percent / 5.0);
				this->cdFatigueIncrementStudy = sf::seconds(0.f); // RESET COOLDOWN
			}
		}
		else
		{
			double percent = (static_cast<double>(rand() % 4) + 1.0) / 1000;
			if (this->cdIntelligenceIncrementStudy.asSeconds() >= this->cdLastStudyMax)
			{
				this->intelligence = percentRange(this->intelligence, percent);
				this->cdIntelligenceIncrementStudy = sf::seconds(0.f); // RESET COOLDOWN
			}
			if (this->cdFatigueIncrementStudy.asSeconds() >= this->cdLastStudyMax)
			{
				this->fatigue = percentRange(this->fatigue, percent * 10.0);
				this->cdFatigueIncrementStudy = sf::seconds(0.f); // RESET COOLDOWN
			}
		}
	}
}

void Psychology::updateIntelligence(const float& dt, Toxicology& toxic)
{
	this->cdLastStudy += sf::seconds(dt);

	if (this->cdLastStudy.asSeconds() >= this->cdLastStudyMax)
	{
		this->cdIntelligenceDecrementStudy += sf::seconds(dt);

		if (this->cdIntelligenceDecrementStudy.asSeconds() >= this->cdStatChangeMax)
		{
			this->intelligence = percentRange(this->intelligence, -0.025);
			this->cdIntelligenceDecrementStudy = sf::seconds(0.f); // RESET COOLDOWN
		}
	}

	if (toxic.getSobriety<double>() < -20.0)
	{
		this->cdIntelligenceDecrementSobriety += sf::seconds(dt);

		if (this->cdIntelligenceDecrementSobriety.asSeconds() >= this->cdStatChangeMax)
		{
			this->intelligence = percentRange(this->intelligence, -0.01);
			this->cdIntelligenceDecrementSobriety = sf::seconds(0.f); // RESET COOLDOWN
		}
	}
}

void Psychology::updateJoy(const float& dt, Toxicology& toxic)
{
	if (toxic.getSobriety<double>() < -30.0)
	{
		this->cdJoyIncrementSobriety += sf::seconds(dt);

		if (this->cdJoyIncrementSobriety.asSeconds() >= this->cdStatChangeMax)
		{
			this->joy = percentRange(this->joy, 0.03);
			this->cdJoyIncrementSobriety = sf::seconds(0.f); // RESET COOLDOWN
		}
	}

	// While it's been less than 3 Game Hours since last intoxicated
	if (toxic.getLastHighMax() - toxic.getLastHigh() > static_cast<float>(0) && toxic.getSobriety<double>() >= -20.0)
	{
		this->cdJoyDecrementSobriety += sf::seconds(dt);

		if (this->cdJoyDecrementSobriety.asSeconds() >= this->cdStatChangeMax)
		{
			this->joy = percentRange(this->joy, -0.004);
			this->cdJoyIncrementSobriety = sf::seconds(0.f); // RESET COOLDOWN
		}
	}
}

void Psychology::updateSadness(const float& dt, Toxicology& toxic)
{
	if (toxic.getLastHighMax() - toxic.getLastHigh() > 0 && toxic.getSobriety<double>() >= -20.0)
	{
		this->cdSadnessIncrementSobriety += sf::seconds(dt);

		if (this->cdSadnessIncrementSobriety.asSeconds() >= this->cdStatChangeMax)
		{
			this->sadness = percentRange(this->sadness, 0.015);
			this->cdSadnessIncrementSobriety = sf::seconds(0.f); // RESET COOLDOWN
		}
	}
}

void Psychology::updateFatigue(const float& dt, Toxicology& toxic)
{
	if (this->isAsleep)
	{
		this->cdFatigueDecrementSleep += sf::seconds(dt);

		if (this->cdFatigueDecrementSleep.asSeconds() >= this->cdStatChangeMax)
		{
			this->fatigue = percentRange(this->fatigue, -0.016);
			this->cdFatigueDecrementSleep = sf::seconds(0.f); // RESET
		}
	}

	if (toxic.getSobriety<double>() < -20)
	{
		this->cdFatigueIncrementSobriety += sf::seconds(dt);

		if (this->cdFatigueIncrementSobriety.asSeconds() >= this->cdStatChangeMax)
		{
			this->fatigue = percentRange(this->fatigue, 0.013);
			this->cdFatigueIncrementSobriety = sf::seconds(0.f); // RESET
		}
	}

	if (this->isSprinting)
	{
		this->cdFatigueIncrementSprinting += sf::seconds(dt);
		if (this->cdFatigueIncrementSprinting.asSeconds() >= this->cdStatChangeMax)
		{
			this->fatigue = percentRange(this->fatigue, 0.013);
			this->cdFatigueIncrementSprinting = sf::seconds(0.f); // RESET
		}
	}
}

void Psychology::updateLimits()
{
	if (this->intelligence > 100.0)
	{
		this->intelligence = 100.0;
	}
	if (this->intelligence < 0.0)
	{
		this->intelligence = 0.0;
	}

	if (this->joy > 100.0)
	{
		this->joy = 100.0;
	}
	if (this->joy < 0.0)
	{
		this->joy = 0.0;
	}

	if (this->sadness > 100.0)
	{
		this->sadness = 100.0;
	}
	if (this->sadness < 0.0)
	{
		this->sadness = 0.0;
	}

	if (this->fatigue > 100.0)
	{
		this->fatigue = 100.0;
	}
	if (this->fatigue < 0.0)
	{
		this->fatigue = 0.0;
	}
}

void Psychology::update(const float& dt, Toxicology& toxic)
{

	this->updateIntelligence(dt, toxic);
	this->updateJoy(dt, toxic);
	this->updateSadness(dt, toxic);
	this->updateFatigue(dt, toxic);

	this->updateStudy(dt, toxic);

	this->updateLimits();

	//===UPDATE MOOD===//
	//HAPPY=0, SAD, TIRED, DELERIOUS, BORED, INTOXICATED

	if (this->joy / this->sadness >= 1.75)
	{
		if (std::find(this->moods.begin(), this->moods.end(), MindState::HAPPY) != this->moods.end())
		{
			this->moods.push_back(MindState::HAPPY);
		}
		for (unsigned i = 0; i < moods.size(); i++)
		{
			if (this->moods[i] == MindState::SAD)
			{
				this->moods.erase(this->moods.begin() + i);
			}
		}
	}	
	
	if (this->sadness / this->joy >= 1.75)
	{
		if (std::find(this->moods.begin(), this->moods.end(), MindState::SAD) != this->moods.end())
		{
			this->moods.push_back(MindState::SAD);
		}
		for (unsigned i = 0; i < moods.size(); i++)
		{
			if (this->moods[i] == MindState::HAPPY)
			{
				this->moods.erase(this->moods.begin() + i);
			}
		}
	}

	if (toxic.getSobriety<double>() < - 20.0)
	{
		if (std::find(this->moods.begin(), this->moods.end(), MindState::INTOXICATED) != this->moods.end())
		{
			this->moods.push_back(MindState::INTOXICATED);
		}
	}	

	if (this->fatigue >= 55.0)
	{
		if (std::find(this->moods.begin(), this->moods.end(), MindState::TIRED) != this->moods.end())
		{
			this->moods.push_back(MindState::TIRED);
		}
	}	
	else
	{
		for (unsigned i = 0; i < moods.size(); i++)
		{
			if (this->moods[i] == MindState::TIRED)
			{
				this->moods.erase(this->moods.begin() + i);
			}
		}
	}
	//---UPDATE MOOD---//
}

const std::vector<MindState>& Psychology::getMoods() const
{
	return this->moods;
}

const bool& Psychology::getIsAsleep() const
{
	return this->isAsleep;
}

const bool& Psychology::getIsStudying() const
{
	return this->isStudying;
}

void Psychology::setIsSprinting(bool condition)
{
	this->isSprinting = true;
}

//---PSYCHOLOGY---//


//===WALLET===//
Wallet::Wallet()
{
	this->amount = 80;
}

Wallet::Wallet(Demographic demographic)
{
	this->amount = 0;

	switch (demographic)
	{
	case Demographic::LOWER:
		this->amount = static_cast<double>(rand() % 26) + 10; // Random from 10 to 35
		break;
	case Demographic::MIDDLE:
		this->amount = static_cast<double>(rand() % 26) + 60; // Random from 60 to 110
		break;
	case Demographic::UPPER:
		this->amount = static_cast<double>(rand() % 66) + 145; // Random from 145 to 210
		break;
	default:
		break;
	}
}

Wallet::~Wallet()
{
}

void Wallet::addMoney(double amount)
{
	this->amount += amount;
}

void Wallet::subMoney(double amount)
{
	this->amount -= amount;
}
//---WALLET---//
