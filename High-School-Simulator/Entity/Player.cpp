#include "Player.h"

Player::Player(std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed) : Entity()
{
	this->keyBinds = keyBinds;
	this->keyBindPressed = keyBindPressed;
}

Player::Player(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed) : Entity(texture, position, scale)
{
	this->keyBinds = keyBinds;
	this->keyBindPressed = keyBindPressed;
}

Player::Player(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale, unsigned int width, unsigned int height, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed) : Entity(texture, position, scale, width, height)
{
	this->keyBinds = keyBinds;
	this->keyBindPressed = keyBindPressed;
}

Player::~Player()
{
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
		this->facing = Direction::WEST;
	}
	else if (this->keyBindPressed->at("MOVE_RIGHT"))
	{
		this->direction.x = 1.f;
		this->facing = Direction::EAST;
	}

	if ((this->keyBindPressed->at("MOVE_UP") && this->keyBindPressed->at("MOVE_DOWN")) || (!this->keyBindPressed->at("MOVE_UP") && !this->keyBindPressed->at("MOVE_DOWN")))
	{
		this->direction.y = 0.f;
	}
	else if (this->keyBindPressed->at("MOVE_UP"))
	{
		this->direction.y = -1.f;
		this->facing = Direction::NORTH;
	}
	else if (this->keyBindPressed->at("MOVE_DOWN"))
	{
		this->direction.y = 1.f;
		this->facing = Direction::SOUTH;
	}

	if (this->keyBindPressed->at("SPRINT"))
	{
		// pythag(sf::Vector2f(percentRange(this->velocity.x, .5f, 1), percentRange(this->velocity.y, .5f, 1)))
		this->move(normalize(this->direction) * percentRange(100.f, .75f, 1) * dt);
		this->lastAnimationShift += sf::seconds(dt); // SPEEDS UP ANIMATION
	}
	else
	{
		this->move(normalize(this->direction) * 100.f * dt);
	}
}

void Player::updateTexture(const float& dt)
{
	if (this->texture->getSize().x == this->getGlobalBounds().width || this->texture->getSize().y == this->getGlobalBounds().height)
	{
		return;
	}

	if (this->direction.x == 0.f && this->direction.y == 0.f) // Idle
	{
		switch (this->facing)
		{
		case Direction::NORTH:
			this->vertices[0].texCoords = sf::Vector2f(16, 16);
			this->vertices[1].texCoords = sf::Vector2f(32, 16);
			this->vertices[2].texCoords = sf::Vector2f(32, 32);
			this->vertices[3].texCoords = sf::Vector2f(16, 32);
			break;
		case Direction::SOUTH:
			this->vertices[0].texCoords = sf::Vector2f(0, 0);
			this->vertices[1].texCoords = sf::Vector2f(16, 0);
			this->vertices[2].texCoords = sf::Vector2f(16, 16);
			this->vertices[3].texCoords = sf::Vector2f(0, 16);
			break;
		case Direction::WEST:
			this->vertices[0].texCoords = sf::Vector2f(32, 32);
			this->vertices[1].texCoords = sf::Vector2f(48, 32);
			this->vertices[2].texCoords = sf::Vector2f(48, 48);
			this->vertices[3].texCoords = sf::Vector2f(32, 48);
			break;
		case Direction::EAST:
			this->vertices[0].texCoords = sf::Vector2f(48, 48);
			this->vertices[1].texCoords = sf::Vector2f(64, 48);
			this->vertices[2].texCoords = sf::Vector2f(64, 64);
			this->vertices[3].texCoords = sf::Vector2f(48, 64);
			break;
		default:
			break;
		}
	}

	switch (this->facing) // Fix Facing Direction
	{
	case Direction::NORTH:
		if (this->vertices[0].texCoords.x != 16.f)
		{
			this->vertices[0].texCoords = sf::Vector2f(16, 16);
			this->vertices[1].texCoords = sf::Vector2f(32, 16);
			this->vertices[2].texCoords = sf::Vector2f(32, 32);
			this->vertices[3].texCoords = sf::Vector2f(16, 32);
		}
		break;
	case Direction::SOUTH:
		if (this->vertices[0].texCoords.x != 0.f)
		{
			this->vertices[0].texCoords = sf::Vector2f(0, 0);
			this->vertices[1].texCoords = sf::Vector2f(16, 0);
			this->vertices[2].texCoords = sf::Vector2f(16, 16);
			this->vertices[3].texCoords = sf::Vector2f(0, 16);
		}
		break;
	case Direction::WEST:
		if (this->vertices[0].texCoords.x != 32.f)
		{
		this->vertices[0].texCoords = sf::Vector2f(32, 32);
		this->vertices[1].texCoords = sf::Vector2f(48, 32);
		this->vertices[2].texCoords = sf::Vector2f(48, 48);
		this->vertices[3].texCoords = sf::Vector2f(32, 48);
		}
		break;
	case Direction::EAST:
		if (this->vertices[0].texCoords.x != 48.f)
		{
		this->vertices[0].texCoords = sf::Vector2f(48, 48);
		this->vertices[1].texCoords = sf::Vector2f(64, 48);
		this->vertices[2].texCoords = sf::Vector2f(64, 64);
		this->vertices[3].texCoords = sf::Vector2f(48, 64);
		}
		break;
	default:
		break;
	}

	if (this->direction.x != 0.f || this->direction.y != 0.f) 
	{
		if (this->lastAnimationShift.asSeconds() >= this->lastAnimationShiftMax)
		{
			if (this->vertices[2].texCoords.y == 64.f)
			{
				this->vertices[0].texCoords = sf::Vector2f(this->vertices[0].texCoords.x, 0);
				this->vertices[1].texCoords = sf::Vector2f(this->vertices[1].texCoords.x, 0);
				this->vertices[2].texCoords = sf::Vector2f(this->vertices[2].texCoords.x, 16);
				this->vertices[3].texCoords = sf::Vector2f(this->vertices[3].texCoords.x, 16);
			}
			else
			{
				this->vertices[0].texCoords.y += 16.f;
				this->vertices[1].texCoords.y += 16.f;
				this->vertices[2].texCoords.y += 16.f;
				this->vertices[3].texCoords.y += 16.f;
			}
			this->lastAnimationShift = sf::seconds(0.f); // RESET
		}
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
	this->lastAnimationShift += sf::seconds(dt);
	this->toxic.update(dt);
	this->psych.update(dt, this->toxic);
	this->updateMovement(dt);
	this->updateTexture(dt);
}

