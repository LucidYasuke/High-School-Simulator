#ifndef ENTITYCOMPONENTS_H
#define ENTITYCOMPONENTS_H

#include "../Physics.h"

enum class demographic { LOWER = 0, MIDDLE, UPPER };

class Mood
{
};

class Drug 
{
};

class Brain
{
private:
	double intelligence;
	sf::Time cooldownLastStudy, cooldownLastStudyMax;

public:
	Brain();
	virtual ~Brain();

	const double& getIntelligence() const;
	const int& getIntell() const;
	void study();
	void update(const float& dt);
};

#endif