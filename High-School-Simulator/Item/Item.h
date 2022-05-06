#ifndef ITEM_H
#define ITEM_H

#include "../Includes.h"

class Item
{
protected:
	float x, y, width, height, scaleX, scaleY;
	bool deleted, unlocked;

	sf::RenderWindow* window;
	sf::Texture* texture;
	sf::Sprite sprite, hiddenSprite;
public:
	Item(sf::RenderWindow* window, sf::Texture* texture, float x, float y);
	Item(sf::RenderWindow* window, sf::Texture* textures[], float x, float y);
	virtual ~Item();

	const bool& getDeleted() const;
	const sf::Sprite& getSprite() const;

	void setDeleted();

	virtual void update(const float& dt) = 0;

	virtual void render(sf::RenderTarget* target) = 0;
};

#endif

