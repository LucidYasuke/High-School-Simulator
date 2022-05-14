#ifndef WORLDITEM_H
#define WORLDITEM_H


#include "Item.h"
#include "../Buttons/Button.h"


struct CollisionButton
{
	Button* button;
	sf::FloatRect radius;
	sf::VertexArray vertices;
};


class WorldItem : public Item
{
private:
	CollisionButton collisionButton;
public:
	WorldItem();
	WorldItem(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale);
	virtual ~WorldItem();

	void setPosition(sf::Vector2f position);
	CollisionButton& getCollisionButton();
};

#endif // !WORLDITEM_H
