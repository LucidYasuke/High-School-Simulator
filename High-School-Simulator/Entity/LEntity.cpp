#include "LEntity.h"


LEntity::LEntity() : Sprite()
{
	this->deleted = false;
	this->movementComponent = 0;
}

LEntity::LEntity(const sf::Texture& texture) : Sprite(texture)
{
	this->deleted = false;
	this->movementComponent = 0;
}

LEntity::LEntity(const sf::Texture& texture, const sf::IntRect& rectangle) : Sprite(texture, rectangle)
{
	this->deleted = false;
	this->movementComponent = 0;
}

LEntity::~LEntity()
{
	if (this->movementComponent) { delete this->movementComponent; }
}

void LEntity::add(EntityComponent::Movement* movementComponent)
{
	this->movementComponent = movementComponent;
}

EntityComponent::Movement*& LEntity::getMovementComponent()
{
	return this->movementComponent;
}

const bool& LEntity::getDeleted() const
{
	return this->deleted;
}

void LEntity::setDeleted(bool condition)
{
	this->deleted = condition;
}

void LEntity::updateMovement(const float& dt)
{
}

void LEntity::update(const float& dt)
{
}

const double& EntityComponent::Intoxication::getSobriety() const
{
	return this->sobriety;
}

const double& EntityComponent::Intoxication::getTolerance() const
{
	return this->tolerance;
}

std::string EntityComponent::Intoxication::getSobrietyAsString()
{
	return std::string();
}
