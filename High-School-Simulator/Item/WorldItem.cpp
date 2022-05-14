#include "WorldItem.h"


WorldItem::WorldItem() : Item()
{
	this->collisionButton.button = nullptr;
	this->collisionButton.radius = this->getGlobalBounds();
	this->collisionButton.vertices = sf::VertexArray(sf::Quads, 4);

	this->collisionButton.radius.left -= this->getGlobalBounds().width / 10.f;
	this->collisionButton.radius.top -= this->getGlobalBounds().height / 10.f;
	this->collisionButton.radius.width += this->getGlobalBounds().width / 5.f;
	this->collisionButton.radius.height += this->getGlobalBounds().height / 5.f;

	this->collisionButton.vertices[0].position = sf::Vector2f(this->collisionButton.radius.left, this->collisionButton.radius.top);
	this->collisionButton.vertices[1].position = sf::Vector2f(this->collisionButton.radius.left + this->collisionButton.radius.width, this->collisionButton.radius.top);
	this->collisionButton.vertices[2].position = sf::Vector2f(this->collisionButton.radius.left + this->collisionButton.radius.width, this->collisionButton.radius.top + this->collisionButton.radius.height);
	this->collisionButton.vertices[3].position = sf::Vector2f(this->collisionButton.radius.left, this->collisionButton.radius.top + this->collisionButton.radius.height);

	this->collisionButton.vertices[0].color = sf::Color::Green;
	this->collisionButton.vertices[1].color = sf::Color::Green;
	this->collisionButton.vertices[2].color = sf::Color::Green;
	this->collisionButton.vertices[3].color = sf::Color::Green;
}

WorldItem::WorldItem(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale) : Item (texture, position, scale)
{
	this->collisionButton.button = nullptr;
	this->collisionButton.radius = this->getGlobalBounds();
	this->collisionButton.vertices = sf::VertexArray(sf::Quads, 4);

	this->collisionButton.radius.left -= this->getGlobalBounds().width / 10.f;
	this->collisionButton.radius.top -= this->getGlobalBounds().height / 10.f;
	this->collisionButton.radius.width += this->getGlobalBounds().width / 5.f;
	this->collisionButton.radius.height += this->getGlobalBounds().height / 5.f;

	this->collisionButton.vertices[0].position = sf::Vector2f(this->collisionButton.radius.left, this->collisionButton.radius.top);
	this->collisionButton.vertices[1].position = sf::Vector2f(this->collisionButton.radius.left + this->collisionButton.radius.width, this->collisionButton.radius.top);
	this->collisionButton.vertices[2].position = sf::Vector2f(this->collisionButton.radius.left + this->collisionButton.radius.width, this->collisionButton.radius.top + this->collisionButton.radius.height);
	this->collisionButton.vertices[3].position = sf::Vector2f(this->collisionButton.radius.left, this->collisionButton.radius.top + this->collisionButton.radius.height);

	this->collisionButton.vertices[0].color = sf::Color::Green;
	this->collisionButton.vertices[1].color = sf::Color::Green;
	this->collisionButton.vertices[2].color = sf::Color::Green;
	this->collisionButton.vertices[3].color = sf::Color::Green;
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

	this->collisionButton.vertices[0].position = sf::Vector2f(this->collisionButton.radius.left, this->collisionButton.radius.top);
	this->collisionButton.vertices[1].position = sf::Vector2f(this->collisionButton.radius.left + this->collisionButton.radius.width, this->collisionButton.radius.top);
	this->collisionButton.vertices[2].position = sf::Vector2f(this->collisionButton.radius.left + this->collisionButton.radius.width, this->collisionButton.radius.top + this->collisionButton.radius.height);
	this->collisionButton.vertices[3].position = sf::Vector2f(this->collisionButton.radius.left, this->collisionButton.radius.top + this->collisionButton.radius.height);
}

CollisionButton& WorldItem::getCollisionButton()
{
	return this->collisionButton;
}
