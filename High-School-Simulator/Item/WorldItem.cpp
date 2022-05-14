#include "WorldItem.h"


WorldItem::WorldItem() : Item()
{
	this->collisionButton.button = nullptr;
	this->collisionButton.radius = this->getGlobalBounds();

	this->collisionButton.radius.left -= this->getGlobalBounds().width / 10.f;
	this->collisionButton.radius.top -= this->getGlobalBounds().height / 10.f;
	this->collisionButton.radius.width += this->getGlobalBounds().width / 5.f;
	this->collisionButton.radius.height += this->getGlobalBounds().height / 5.f;
}

WorldItem::WorldItem(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale) : Item (texture, position, scale)
{
	this->collisionButton.button = nullptr;
	this->collisionButton.radius = this->getGlobalBounds();

	this->collisionButton.radius.left -= this->getGlobalBounds().width / 10.f;
	this->collisionButton.radius.top -= this->getGlobalBounds().height / 10.f;
	this->collisionButton.radius.width += this->getGlobalBounds().width / 5.f;
	this->collisionButton.radius.height += this->getGlobalBounds().height / 5.f;
}

WorldItem::~WorldItem()
{
}

void WorldItem::setPosition(sf::Vector2f position)
{
	this->sf::Transformable::setPosition(position);

	this->collisionButton.radius = this->getGlobalBounds();

	this->collisionButton.radius.left -= this->getGlobalBounds().width / 10.f;
	this->collisionButton.radius.top -= this->getGlobalBounds().height / 10.f;
	this->collisionButton.radius.width += this->getGlobalBounds().width / 5.f;
	this->collisionButton.radius.height += this->getGlobalBounds().height / 5.f;
}

CollisionButton& WorldItem::getCollisionButton()
{
	return this->collisionButton;
}
