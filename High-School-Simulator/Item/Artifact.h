#ifndef ARTIFACT_H
#define ARTIFACT_H

#include "Item.h"
class Artifact : public Item
{
protected:
	unsigned short int inventory;
	unsigned short int level;

	sf::Time currentTime, maxTime;
public:
	Artifact(sf::RenderWindow* window, sf::Texture* texture, float x, float y, sf::Time currentTime, sf::Time maxTime);
	virtual ~Artifact();

	sf::Time* getCurrentTimePointer();
	sf::Time* getMaxTimePointer();

	void updateTimer(const float& dt);
	void update(const float& dt) override;

	void render(sf::RenderTarget* target) override;
};

#endif

