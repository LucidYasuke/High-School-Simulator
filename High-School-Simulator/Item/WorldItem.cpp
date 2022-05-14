#include "WorldItem.h"

WorldItem::WorldItem() : Item()
{
	this->collisionButton.radius = this->getGlobalBounds();
	this->collisionButton.radius.left -= 10.f;
	this->collisionButton.radius.top -= 10.f;
	this->collisionButton.radius.width += 20.f;
	this->collisionButton.radius.height += 20.f;

	this->collisionButton.button = nullptr;
}

WorldItem::WorldItem(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale) : Item (texture, position, scale)
{
	this->collisionButton.radius = this->getGlobalBounds();
	this->collisionButton.radius.left -= 10.f;
	this->collisionButton.radius.top -= 10.f;
	this->collisionButton.radius.width += 20.f;
	this->collisionButton.radius.height += 20.f;

	this->collisionButton.button = nullptr;
}

WorldItem::~WorldItem()
{
}

CollisionButton& WorldItem::getCollisionButton()
{
	return this->collisionButton;
}
