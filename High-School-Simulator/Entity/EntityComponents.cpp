#include "EntityComponents.h"

//===TOXICOLOGY===//

// 3 Game Hours = 6 Real Life Minutes
const float Toxicology::lastHighMax = 360.f;

// 3 Game Minutes = 6 Real Life Seconds
const float Toxicology::cdHighMax = 6.f;

Toxicology::Toxicology()
{
	// Last High Default | Default is Last High Max
	this->lastHigh = sf::seconds(this->lastHighMax);

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
	if (this->sobriety >= -20 )
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

// 2.5 Game Hours = 5 Real Life Minutes
const float Psychology::cdStatChangeMax = 300.f;

Psychology::Psychology()
{
	this->intelligence = 65.0;
	this->joy = 75.0;
	this->sadness = 0.0;
	this->fatigue = 20.0;
}

Psychology::Psychology(Demographic demographic)
{
	switch (demographic)
	{
	case Demographic::LOWER:
		break;
	case Demographic::MIDDLE:
		this->intelligence = rand() % 16 + 55; // Random from 55 to 70
		this->joy = roundTo<double>(50.0 / (this->intelligence / 100), 2); // Base joy is 50, the lower your intelligence the higher it will be
		this->sadness = roundTo<double>(30.0 * (this->intelligence / 100), 2); // Base sadness is 30, the higher your intelligence the higher you sadness
		this->fatigue = rand() % 16 + 5; // Random from 5 to 20
		break;
	case Demographic::UPPER:
		break;
	default:
		break;
	}
}

Psychology::~Psychology()
{
}

void Psychology::update(const float& dt, Toxicology& toxic)
{
	//===UPDATE INTELLIGENCE===//
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
			this->intelligence = percentRange(this->intelligence, -0.03);
			this->cdIntelligenceDecrementSobriety = sf::seconds(0.f); // RESET COOLDOWN
		}
	}
	//---UPDATE INTELLIGENCE---//

	//===UPDATE JOY===//
	if (toxic.getSobriety<double>() < -30.0)
	{
		this->cdJoyIncrementSobriety += sf::seconds(dt);

		if (this->cdJoyIncrementSobriety.asSeconds() >= this->cdStatChangeMax)
		{
			this->joy = percentRange(this->joy, 0.03);
			this->cdJoyIncrementSobriety = sf::seconds(0.f); // RESET COOLDOWN
		}
	}

	// While it's been more than 3 Game Hours since last intoxicated
	if(toxic.getLastHighMax() - toxic.getLastHigh() > 0 && toxic.getSobriety<double>() >= -20.0)
	{
		this->cdJoyDecrementSobriety += sf::seconds(dt);

		if (this->cdJoyDecrementSobriety.asSeconds() >= this->cdStatChangeMax)
		{
			this->joy = percentRange(this->joy, -0.010);
			this->cdJoyIncrementSobriety = sf::seconds(0.f); // RESET COOLDOWN
		}
	}
	//---UPDATE JOY---//

	//===UPDATE SADNESS===//
	if (toxic.getLastHighMax() - toxic.getLastHigh() > 0 && toxic.getSobriety<double>() >= -20.0)
	{
		this->cdSadnessIncrementSobriety += sf::seconds(dt);

		if (this->cdSadnessIncrementSobriety.asSeconds() >= this->cdStatChangeMax)
		{
			this->sadness = percentRange(this->sadness, 0.015);
			this->cdSadnessIncrementSobriety = sf::seconds(0.f); // RESET COOLDOWN
		}
	}
	//---UPDATE SAD---//
}

//---PSYCHOLOGY---//

void Wallet::addMoney(double amount)
{
	this->amount += amount;
}

void Wallet::subMoney(double amount)
{
	this->amount -= amount;
}
