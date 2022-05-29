#include "Item.h"


Item::Item() : Sprite()
{
	this->collisionComponent = 0;
	this->inventoryComponent = 0;
}

Item::Item(const sf::Texture& texture) : Sprite(texture)
{
	this->collisionComponent = 0;
	this->inventoryComponent = 0;
}

Item::Item(const sf::Texture& texture, const sf::IntRect& rectangle) : Sprite(texture, rectangle)
{
	this->collisionComponent = 0;
	this->inventoryComponent = 0;
}

Item::~Item()
{
	if (this->collisionComponent)
	{
		delete this->collisionComponent;
	}
	if (this->inventoryComponent)
	{
		delete this->inventoryComponent;
	}
}

void Item::add(ItemComponent::WorldCollision* collisionComponent)
{
	this->collisionComponent = collisionComponent;

	this->collisionComponent->button = nullptr;
	this->collisionComponent->radius = this->getGlobalBounds();

	this->collisionComponent->radius.left -= this->getGlobalBounds().width / 10.f;
	this->collisionComponent->radius.top -= this->getGlobalBounds().height / 10.f;
	this->collisionComponent->radius.width += this->getGlobalBounds().width / 5.f;
	this->collisionComponent->radius.height += this->getGlobalBounds().height / 5.f;
}

void Item::add(ItemComponent::Inventory* inventoryComponent)
{
	this->inventoryComponent = inventoryComponent;
}

ItemComponent::WorldCollision*& Item::getCollisionComponent()
{
	return this->collisionComponent;
}

ItemComponent::Inventory*& Item::getInventoryComponent()
{
	return this->inventoryComponent;
}

void Item::setPosition(sf::Vector2f position)
{
	this->sf::Transformable::setPosition(position);

	if (this->collisionComponent)
	{
		this->collisionComponent->radius = this->getGlobalBounds();

		this->collisionComponent->radius.left -= this->getGlobalBounds().width / 10.f;
		this->collisionComponent->radius.top -= this->getGlobalBounds().height / 10.f;
		this->collisionComponent->radius.width += this->getGlobalBounds().width / 5.f;
		this->collisionComponent->radius.height += this->getGlobalBounds().height / 5.f;
	}
}

const bool& Item::getDeleted() const
{
	return this->deleted;
}

void Item::setDeleted(bool condition)
{
	this->deleted = condition;
}

void Item::update(const float& dt)
{
}
