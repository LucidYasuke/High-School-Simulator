#ifndef ENTITYCOMPONENTS_H
#define ENTITYCOMPONENTS_H

#include "../Physics.h"

enum class Demographic { LOWER = 0, MIDDLE, UPPER };

enum class MindState {HAPPY=0, SAD, TIRED, DELERIOUS, BORED, INTOXICATED};

// Drug Manipulation System
class Toxicology 
{
private:
	double sobriety;
	double tolerance;

	sf::Time lastHigh;
	static const float lastHighMax;

	sf::Time cdHigh;
	static const float cdHighMax;
public:
	Toxicology();
	virtual ~Toxicology();

	void getHigh();
	void update(const float& dt);

	template <typename T>
	T getSobriety();

	template <typename T>
	std::string getSobrietyAsString();

	const float getLastHigh() const;
	const float& getLastHighMax() const;
};

class Psychology
{
private:
	double intelligence;
	double joy;
	double sadness;
	double fatigue;

	bool isAsleep;
	bool isStudying;

	std::vector<MindState> moods;

	sf::Time cdLastStudy;
	static const float cdLastStudyMax;

	static const float cdStatChangeMax;

	sf::Time cdIntelligenceDecrementStudy;
	sf::Time cdIntelligenceIncrementStudy;
	sf::Time cdIntelligenceDecrementSobriety;

	sf::Time cdJoyIncrementSobriety;
	sf::Time cdJoyDecrementSobriety;

	sf::Time cdSadnessIncrementSobriety;

	sf::Time cdFatigueIncrementSobriety;
	sf::Time cdFatigueDecrementSobriety;	
	sf::Time cdFatigueDecrementStudy;
public:
	Psychology();
	Psychology(Demographic demographic);
	virtual ~Psychology();

	void study();
	void sleep();

	void updateStudy(const float& dt, Toxicology& toxic);
	void updateLimits();
	void update(const float& dt, Toxicology& toxic);

	const std::vector<MindState>& getMoods() const;

	const bool& getIsAsleep() const;
	const bool& getIsStudying() const;

	template <typename T>
	T getIntelligence();	
	template <typename T>
	T getJoy();
	template <typename T>
	T getSadness();
	template <typename T>
	T getFatigue();

	template <typename T>
	std::string getIntelligenceAsString();	
	template <typename T>
	std::string getJoyAsString();	
	template <typename T>
	std::string getSadnessAsString();
	template <typename T>
	std::string getFatigueAsString();
};

class Wallet
{
private:
	double amount;
public:
	Wallet();
	Wallet(Demographic demographic);
	virtual ~Wallet();

	void addMoney(double amount);
	void subMoney(double amount);

	template <typename T>
	T getMoney();

	template <typename T>
	std::string getMoneyAsString();
};


template<typename T>
inline T Toxicology::getSobriety()
{
	return static_cast<T>(roundTo<double>(this->sobriety, 2));
}

template<typename T>
inline std::string Toxicology::getSobrietyAsString()
{
	return std::to_string(this->getSobriety<T>());
}

template<typename T>
inline T Psychology::getIntelligence()
{
	return static_cast<T>(roundTo<double>(this->intelligence, 2));
}

template<typename T>
inline T Psychology::getJoy()
{
	return static_cast<T>(roundTo<double>(this->joy, 2));
}

template<typename T>
inline T Psychology::getSadness()
{
	return static_cast<T>(roundTo<double>(this->sadness, 2));
}

template<typename T>
inline T Psychology::getFatigue()
{
	return static_cast<T>(roundTo<double>(this->fatigue, 2));
}

template<typename T>
inline std::string Psychology::getIntelligenceAsString()
{
	return std::to_string(this->getIntelligence<T>());
}

template<typename T>
inline std::string Psychology::getJoyAsString()
{
	return std::to_string(this->getJoy<T>());
}

template<typename T>
inline std::string Psychology::getSadnessAsString()
{
	return std::to_string(this->getSadness<T>());
}

template<typename T>
inline std::string Psychology::getFatigueAsString()
{
	return std::to_string(this->getFatigue<T>());
}

template<typename T>
inline T Wallet::getMoney()
{
	return static_cast<T>(roundTo<double>(this->amount, 2));
}

template<typename T>
inline std::string Wallet::getMoneyAsString()
{
	return std::to_string(this->getMoney<T>());
}

#endif
