#include "Bar.h"

Bar::Bar()
{
	this->progressComponent = 0;
}

Bar::Bar(const sf::Texture& texture)
{
	this->progressComponent = 0;
}

Bar::Bar(const sf::Texture& texture, const sf::IntRect& rectangle)
{
	this->progressComponent = 0;
}

Bar::~Bar()
{
}

void Bar::add(Component::Bar::Progress* progressComponent)
{
	this->progressComponent = progressComponent;
}

Component::Bar::Progress*& Bar::getProgressComponent()
{
	return this->progressComponent;
}
