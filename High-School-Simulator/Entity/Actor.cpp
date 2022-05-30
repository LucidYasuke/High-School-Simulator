#include "Actor.h"


Actor::Actor() : Sprite()
{
	this->deleted = false;
	this->movementComponent = 0;
}

Actor::Actor(const sf::Texture& texture) : Sprite(texture)
{
	this->deleted = false;
	this->movementComponent = 0;
}

Actor::Actor(const sf::Texture& texture, const sf::IntRect& rectangle) : Sprite(texture, rectangle)
{
	this->deleted = false;
	this->movementComponent = 0;
}

Actor::~Actor()
{
	if (this->movementComponent) { delete this->movementComponent; }
}

void Actor::add(ActorComponents::Movement* movementComponent)
{
	this->movementComponent = movementComponent;
}

ActorComponents::Movement*& Actor::getMovementComponent()
{
	return this->movementComponent;
}

const bool& Actor::getDeleted() const
{
	return this->deleted;
}

void Actor::setDeleted(bool condition)
{
	this->deleted = condition;
}

void Actor::updateMovement(const float& dt)
{
}

void Actor::update(const float& dt)
{
}
