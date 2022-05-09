#ifndef ENTITYCOMPONENTS_H
#define ENTITYCOMPONENTS_H

#include "../Physics.h"

enum class Demographic { LOWER = 0, MIDDLE, UPPER };

enum class MindState {HAPPY=0, SAD, TIRED, DELERIOUS, BORED, INTOXICATED};

class Mood
{
};

// Drug Manipulation System
class Toxicology 
{
private:
	double sobriety;
	double tolerance;

	sf::Time lastHigh;
	static const float lastHighMax;

	sf::Time cooldownHigh;
	static const float cooldownHighMax;
public:
	Toxicology();
	virtual ~Toxicology();

	void getHigh();
	void update(const float& dt);

	template <typename T>
	const T& getSobriety() const;

	template <typename T>
	const std::string& getSobrietyAsString() const;

	const float& getLastHigh() const;
	const float& getLastHighMax() const;
};

class Psychology
{
private:
	double intelligence;
	double joy;
	double sadness;
	double fatigue;

	sf::Time cdLastStudy;
	static const float cdLastStudyMax;

	sf::Time cdIntelligenceDepletionStudy;
	sf::Time cdIntelligenceDepletionSobriety;
	static const float cdIntelligenceDepletionMax;

public:
	Psychology();
	virtual ~Psychology();

	void study();
	void update(const float& dt, Toxicology& toxic);

	template <typename T>
	const T& getIntelligence() const;

	template <typename T>
	const std::string& getIntelligenceAsString() const;
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
