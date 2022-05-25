#include "Player.h"


void Player::initInventory()
{
	this->inventory = new Inventory(100);
}

Player::Player(std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed) : Entity()
{
	this->keyBinds = keyBinds;
	this->keyBindPressed = keyBindPressed;
	this->demographic = Demographic::MIDDLE;
	this->psych = Psychology(this->demographic);
	this->wallet = Wallet(this->demographic);
}

Player::Player(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed) : Entity(texture, position, scale)
{
	this->keyBinds = keyBinds;
	this->keyBindPressed = keyBindPressed;
	this->demographic = Demographic::MIDDLE;
	this->psych = Psychology(this->demographic);
	this->wallet = Wallet(this->demographic);
}

Player::~Player()
{
	delete this->inventory;
}

void Player::setDemographic(Demographic demographic)
{
	this->demographic = demographic;
	this->psych = Psychology(demographic);
	this->wallet = Wallet(demographic);
}


Toxicology& Player::getToxicology()
{
	return this->toxic;
}

Psychology& Player::getPsychology()
{
	return this->psych;
}

Wallet& Player::getWallet()
{
	return this->wallet;
}

void Player::updateMovement(const float& dt)
{
	//Keyboard Input
	if ((this->keyBindPressed->at("MOVE_LEFT") && this->keyBindPressed->at("MOVE_RIGHT")) || (!this->keyBindPressed->at("MOVE_LEFT") && !this->keyBindPressed->at("MOVE_RIGHT")))
	{
		this->direction.x = 0.f;
	}
	else if (this->keyBindPressed->at("MOVE_LEFT"))
	{
		this->direction.x = -1.f;
	}
	else if (this->keyBindPressed->at("MOVE_RIGHT"))
	{
		this->direction.x = 1.f;
	}

	if ((this->keyBindPressed->at("MOVE_UP") && this->keyBindPressed->at("MOVE_DOWN")) || (!this->keyBindPressed->at("MOVE_UP") && !this->keyBindPressed->at("MOVE_DOWN")))
	{
		this->direction.y = 0.f;
	}
	else if (this->keyBindPressed->at("MOVE_UP"))
	{
		this->direction.y = -1.f;
	}
	else if (this->keyBindPressed->at("MOVE_DOWN"))
	{
		this->direction.y = 1.f;
	}

	if (this->keyBindPressed->at("SPRINT"))
	{
		// pythag(sf::Vector2f(percentRange(this->velocity.x, .5f, 1), percentRange(this->velocity.y, .5f, 1)))
		this->move(normalize(this->direction) * percentRange(100.f, .5f, 1) * dt);
	}
	else
	{
		this->move(normalize(this->direction) * 100.f * dt);
	}
}

void Player::updateCollision(const sf::FloatRect& bounds)
{
	// Left Collision
	if (this->getGlobalBounds().left < bounds.left)
	{
		std::cout << this->getPosition().x << std::endl;
		this->setPosition(bounds.left, this->getGlobalBounds().top);
	}
	// Right Collision
	else if (this->getGlobalBounds().left + this->getGlobalBounds().width > bounds.left + bounds.width)
	{
		this->setPosition(bounds.left + bounds.width - this->getGlobalBounds().width, this->getGlobalBounds().top);
	}

	// Top Collision
	if (this->getGlobalBounds().top < bounds.top)
	{
		this->setPosition(this->getGlobalBounds().left, bounds.top);
	}
	// Bottom Collision
	else if (this->getGlobalBounds().top + this->getGlobalBounds().height > bounds.top + bounds.height)
	{
		this->setPosition(this->getGlobalBounds().left, bounds.top + bounds.height - this->getGlobalBounds().height);
	}
}

void Player::update(const float& dt)
{
	this->toxic.update(dt);
	this->psych.update(dt, this->toxic);
	this->updateMovement(dt);
}
