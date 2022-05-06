#include "Artifact.h"

Artifact::Artifact(sf::RenderWindow* window, sf::Texture* texture, float x, float y, sf::Time currentTime, sf::Time maxTime) : Item(window, texture, x, y)
{
	this->currentTime = currentTime;
	this->maxTime = maxTime;

	this->x = x - this->width / 2.f;
	this->y = y - this->height / 2.f;
	this->sprite.setPosition(sf::Vector2f(this->x, this->y));
	this->hiddenSprite.setPosition(sf::Vector2f(this->x, this->y));
}

Artifact::~Artifact()
{
}

sf::Time* Artifact::getCurrentTimePointer()
{
	return &this->currentTime;
}

sf::Time* Artifact::getMaxTimePointer()
{
	return &this->maxTime;
}

void Artifact::updateTimer(const float& dt)
{
	switch (this->unlocked)
	{
	case true:
		this->currentTime += sf::seconds(dt);
		break;
	case false:
		break;
	}
}

void Artifact::update(const float& dt)
{
	this->updateTimer(dt);

	switch (this->unlocked)
	{
	case true:
		if (this->currentTime >= this->maxTime)
		{
			this->inventory++;
			this->currentTime = sf::seconds(0.f);
		}
		break;
	case false:
		break;
	}

	if (this->inventory > 9999)
	{
		this->inventory = 9999;
	}
}

void Artifact::render(sf::RenderTarget* target)
{
	switch (this->unlocked)
	{
	case true:
		target->draw(this->sprite);
		break;
	case false:
		target->draw(this->hiddenSprite);
		break;
	}
}
