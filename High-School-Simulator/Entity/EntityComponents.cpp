#include "EntityComponents.h"


//===TOXICOLOGY===//

// 3 Game Hours = 6 Real Life Minutes
const float Toxicology::lastHighMax = 360.f;

// 3 Game Minutes = 6 Real Life Seconds
const float Toxicology::cooldownHighMax = 6.f;

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
	this->lastHigh = sf::seconds(0.f);


	// Sobriety can't be less than -100
	if (this->sobriety < -100.0)
	{
		this->sobriety = -100.0;
	}
}

void Toxicology::update(const float& dt)
{
	this->cooldownHigh += sf::seconds(dt);

	// If greater than 3 game minute = 6 real life seconds
	// Every 3 game minutes, your high will be decreased
	if (this->cooldownHigh.asSeconds() >= this->cooldownHighMax && this->sobriety < 0)
	{
		this->sobriety += 1 * this->tolerance;
		this->cooldownHigh -= sf::seconds(this->cooldownHighMax);
	}
	
	// Sobriety can't be greater than zero
	if (this->sobriety > 0)
	{
		this->sobriety = 0;
	}

	// When the player comes down from their high, the last high meter time increases
	if (this->sobriety > -20 )
	{
		this->lastHigh += sf::seconds(dt);
	}
}

template<typename T>
const T& Toxicology::getSobriety() const
{
	return static_cast<T>(roundTo(this->sobriety, 2));
}

template<typename T>
const std::string& Toxicology::getSobrietyAsString() const
{
	return std::to_string(this->getSobriety<T>());
}

const float& Toxicology::getLastHigh() const
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
const float Psychology::cdIntelligenceDepletionMax = 300.f;

template<typename T>
inline const T& Psychology::getIntelligence() const
{
	return static_cast<T>(roundTo(this->intelligence, 2));
}

template<typename T>
const std::string& Psychology::getIntelligenceAsString() const
{
	return std::to_string(this->getIntelligence<T>());
}

void Psychology::update(const float& dt, Toxicology& toxic)
{
	//===UPDATE INTELLIGENCE===//
	this->cdLastStudy += sf::seconds(dt);

	if (this->cdLastStudy.asSeconds() >= this->cdLastStudyMax)
	{
		this->cdIntelligenceDepletionStudy += sf::seconds(dt);

		if (this->cdIntelligenceDepletionStudy.asSeconds() >= this->cdIntelligenceDepletionMax)
		{
			this->intelligence = percentRange(this->intelligence, -0.025);
			this->cdIntelligenceDepletionStudy = sf::seconds(0.f); // RESET COOLDOWN
		}
	}

	if (toxic.getSobriety<double>() < -20.0)
	{
		this->cdIntelligenceDepletionSobriety += sf::seconds(dt);

		if (this->cdIntelligenceDepletionSobriety.asSeconds() >= this->cdIntelligenceDepletionMax)
		{
			this->intelligence = percentRange(this->intelligence, -0.025);
			this->cdIntelligenceDepletionSobriety = sf::seconds(0.f); // RESET COOLDOWN
		}
	}
	//---UPDATE INTELLIGENCE---//
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
