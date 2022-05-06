#include "Item.h"

Item::Item(sf::RenderWindow* window, sf::Texture* texture, float x, float y)
{
	//===PRIMARY===//
	this->window = window;
	this->texture = texture;

	this->scaleX = 1.5f * (this->window->getSize().x / 1280.f);
	this->scaleY = 1.5f * (this->window->getSize().y / 720.f);
	//---PRIMARY---//

	//===BASIC DATA===//
	this->deleted = false;
	this->unlocked = false;

	this->x = x;
	this->y = y;

	this->width = this->texture->getSize().x * this->scaleX;
	this->height = this->texture->getSize().y * this->scaleY;

	if (this->x + this->width > this->window->getSize().x) { this->x = this->window->getSize().x - this->width; }
	//---BASIC DATA===//

	//===GRAPHICS===//
	this->sprite = sf::Sprite(*this->texture);
	this->sprite.setScale(sf::Vector2f(this->scaleX, this->scaleY));
	this->sprite.setPosition(this->x, this->y);

	this->hiddenSprite = this->sprite;
	this->hiddenSprite.setColor(sf::Color::Black);
	//---GRAPHICS---//
}

Item::Item(sf::RenderWindow* window, sf::Texture* textures[], float x, float y)
{
	//===PRIMARY===//
	this->window = window;
	this->texture = textures[0];

	this->scaleX = 1.f * (this->window->getSize().x / 1280.f);
	this->scaleY = 1.f * (this->window->getSize().y / 720.f);
	//---PRIMARY---//

	//===BASIC DATA===//
	this->deleted = false;

	this->x = x;
	this->y = y;

	this->width = this->texture->getSize().x * this->scaleX;
	this->height = this->texture->getSize().y * this->scaleY;

	if (this->x + this->width > this->window->getSize().x) { this->x = this->window->getSize().x - this->width; }
	//---BASIC DATA===//

	//===GRAPHICS===//
	this->sprite = sf::Sprite(*this->texture);
	this->sprite.setScale(sf::Vector2f(this->scaleX, this->scaleY));
	this->sprite.setPosition(this->x, this->y);
	//---GRAPHICS---//
}

Item::~Item()
{

}

const bool& Item::getDeleted() const
{
	return this->deleted;
}

const sf::Sprite& Item::getSprite() const
{
	return this->sprite;
}

void Item::setDeleted()
{
	this->deleted = true;
}