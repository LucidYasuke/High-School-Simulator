#include "GameState.h"


Date::Date()
{
}

Date::~Date()
{
}

void Date::update(const float& dt)
{
	minute += sf::seconds(dt);

	// 1 Game Hour ≈ 2 Real Minutes
	// 1 Day ≈ 48 Real Minutes
	// If the minutes is divisible by 120, then an hour has passed 
	if (static_cast<int>(minute.asSeconds()) >= 120)
	{
		this->hour += static_cast<int>(minute.asSeconds()) / 120;
		while (static_cast<int>(minute.asSeconds()) >= 120)
		{
			this->minute -= sf::seconds(120.f);
		}
	}

	if (this->hour >= 24)
	{
		this->hour -= 24;
		if (this->day == Day::SATURDAY)
		{
			this->day = Day::SUNDAY;
		}
		else
		{
			this->day = static_cast<Day>(static_cast<int>(this->day) + 1);
		}
	}
}

const Day& Date::getDay() const
{
	return day;
}

const int& Date::getHour() const
{
	return hour;
}

const sf::Time Date::getMinute() const
{
	return minute;
}

const std::string Date::getDayAsString() const
{
	switch (this->day)
	{
	case Day::SUNDAY:
		return "SUNDAY";
	case Day::MONDAY:
		return "MONDAY";
	case Day::TUESDAY:
		return "TUESDAY";
	case Day::WEDNESDAY:
		return "WEDNESDAY";
	case Day::THURSDAY:
		return "THURSDAY";
	case Day::FRIDAY:
		return "FRIDAY";
	case Day::SATURDAY:
		return "SATURDAY";
	default:
		return "NULL";
	}
}

const std::string Date::getHourAsString() const
{
	return std::to_string(this->hour);
}

const std::string Date::getMinuteAsString() const
{
	return std::to_string(static_cast<int>(this->minute.asSeconds() / 2.f));
}

void Date::setDay(Day& day)
{
	this->day = day;
}

void Date::setHour(int& hour)
{
	this->hour = hour;
}

void Date::setMinute(float& minute)
{
	this->minute = sf::seconds(minute);
}

//===INITIALIZE FUNCTIONS===//
void GameState::initTextures()
{
	//===Init Background Texture===//
	this->texturePlayer = new sf::Texture;
	this->texturePlayer->loadFromFile("Assets/Tiles/Sprite-0003.png");
	//---Init Background Texture---//
}

void GameState::initBackground()
{
}

void GameState::initButtons()
{
}

//---INITIALIZE FUNCTIONS---//
GameState::GameState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed, std::map<std::string, bool*> booleans) : State(window, mosPosWindow, mosPosView, keyBinds, keyBindPressed, booleans)
{
	this->initTextures();
	this->initBackground();
	this->initButtons();

	float scaleX = this->window->getView().getSize().x / 1280.f;
	float scaleY = this->window->getView().getSize().y / 720.f;

	//===Init Boolean (Maps)===//
	this->pause = false;
	this->gameOver = false;

	this->booleansPause.insert({ "PauseGameState", &this->pause });
	this->booleansPause.insert({ "QuitGameState", &this->quit });
	//---Init Boolean (Maps)---//



	//===Init Timers===//
	this->cooldownPauseCreationMax = sf::seconds(0.5f);
	this->cooldownPauseCreation = this->cooldownPauseCreationMax;
	//---Init Timers---//

	// define the level with an array of tile indices
	const int level[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	// create the tilemap from the level definition
	if (!this->map.load("Assets/Tiles/floorTileSheet.png", sf::Vector2u(64, 64), level, 16, 8))
		std::cout << "IT AINT LOAD" << std::endl;

	this->map.setPosition(sf::Vector2f(this->window->getView().getSize().x / 2.f - this->map.getGlobalBounds().width / 2.f, this->window->getView().getSize().y / 2.f - this->map.getGlobalBounds().height / 2.f));

	this->player = new Player(this->texturePlayer, sf::Vector2f(this->map.getGlobalBounds().left + this->map.getGlobalBounds().width / 2.f, this->map.getGlobalBounds().top + this->map.getGlobalBounds().height / 2.f), sf::Vector2f(scaleX, scaleY), this->keyBinds, this->keyBindPressed);
	this->player->setPosition(sf::Vector2f(this->player->getGlobalBounds().left - this->player->getGlobalBounds().width / 2.f, this->player->getGlobalBounds().top - this->player->getGlobalBounds().height / 2.f));
}

GameState::~GameState()
{
	while (!this->stateStack.empty())
	{
		delete this->stateStack.top();
		this->stateStack.pop();
	}
}

void GameState::endState()
{
	this->window->setView(this->window->getDefaultView());
}

void GameState::confirmQuit()
{
}

void GameState::resetButton()
{
}

void GameState::updateLevel()
{
}

void GameState::updateTimers(const float& dt)
{
	this->cooldownPauseCreation += sf::seconds(dt);
}

void GameState::updateInput()
{
	if (this->keyBindPressed->at("PAUSE"))
	{
		if (this->cooldownPauseCreation >= this->cooldownPauseCreationMax)
		{
			switch (this->pause)
			{
			case false:
				this->pause = true;
				break;
			default:
				break;
			}
			this->cooldownPauseCreation = sf::seconds(0.f);
		}
	}
}

void GameState::update(const float& dt)
{
	if ((this->pause && !this->gameOver) && (this->stateStack.empty())) // Checks if the player has initiated pause AND the stack is already empty
	{
		this->stateStack.push(new PauseState(this->window, this->mosPosWindow, this->mosPosView, this->keyBinds, this->keyBindPressed, this->booleansPause));
	}

	if (!this->stateStack.empty()) // If the stack isn't empty, that state will be updated
	{
		this->stateStack.top()->update(dt);
		if (this->stateStack.top()->getQuit())
		{
			this->stateStack.top()->confirmQuit();
			if (this->stateStack.top()->getQuit()) // Done Twice because the it will first confirm that user still chooses to quit, saving etc
			{
				this->stateStack.top()->endState();
				delete this->stateStack.top();
				this->stateStack.pop();
			}
		}
		return;
	}

	this->updateTimers(dt);

	this->updateInput();

	this->player->update(dt);

	this->player->updateCollision(this->map.getGlobalBounds());

}

void GameState::render(sf::RenderTarget* target)
{
	/*
	Render Hierarchy
		Map
		Player
	*/

	this->window->setView(this->player->getView());

	target->draw(this->map);

	target->draw(*this->player);

	if (!this->stateStack.empty()) // As long as the stack is not empty, it will render the top
	{
		this->window->setView(this->window->getDefaultView());

		this->stateStack.top()->render(target);
	}
}


