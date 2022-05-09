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

	static const float cdStatChangeMax;

	sf::Time cdLastStudy;
	static const float cdLastStudyMax;

	sf::Time cdIntelligenceDecrementStudy;
	sf::Time cdIntelligenceDecrementSobriety;

	sf::Time cdJoyIncrementSobriety;
public:
	Psychology();
	virtual ~Psychology();

	void study();
	void update(const float& dt, Toxicology& toxic);

	template <typename T>
	T getIntelligence();

	template <typename T>
	std::string getIntelligenceAsString();
};

class Wallet
{
private:
	double amount;
public:
	void addMoney(double amount);
	void subMoney(double amount);
};

#endif

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
inline std::string Psychology::getIntelligenceAsString()
{
	return std::to_string(this->getIntelligence<T>());
}
