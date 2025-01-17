﻿#include "GameState.h"


Date::Date()
{
	this->day = Day::MONDAY;
	this->hour = 6;
	this->minute = sf::seconds(0.f);
}

Date::~Date()
{
}

void Date::update(const float& dt)
{
	minute += sf::seconds(dt);

	// 1 Game Hour ≈ 1 Real Minutes
	// 1 Day ≈ 24 Real Minutes
	// If the minutes is divisible by 60, then an hour has passed 
	if (static_cast<int>(minute.asSeconds()) >= 60)
	{
		while (static_cast<int>(minute.asSeconds()) >= 60)
		{
			this->hour++;
			this->minute -= sf::seconds(60.f);
		}
	}

	if (this->hour >= 24)
	{
		this->hour -= 24;
		switch (this->day)
		{
		case Day::SATURDAY:
			this->day = Day::SUNDAY;
			break;
		default:
			this->day = static_cast<Day>(static_cast<int>(this->day) + 1);
			break;
		}
	}
}

const Day& Date::getDay() const
{
	return this->day;
}

const int& Date::getHour() const
{
	return this->hour;
}

const int Date::getMinute() const
{
	return static_cast<int>(this->minute.asSeconds());
}

const float Date::getTrueMinute() const
{
	return this->minute.asSeconds();
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
	if (this->hour < 10)
	{
		return "0" + std::to_string(this->hour);
	}
	return std::to_string(this->hour);
}

const std::string Date::getMinuteAsString() const
{
	if (this->getMinute() < 10)
	{
		return "0" + std::to_string(this->getMinute());
	}
	return std::to_string(this->getMinute());
}

const std::string Date::getTimeAsString() const
{
	return this->getHourAsString() + ":" + this->getMinuteAsString();
}

void Date::setDay(Day& day)
{
	this->day = day;
}

void Date::setHour(int& hour)
{
	this->hour = hour;
}

void Date::setMinute(int& minute)
{
	this->minute = sf::seconds(static_cast<float>(minute));
}


//===INITIALIZE FUNCTIONS===//
void GameState::initTextures()
{
	this->texturePlayer = new sf::Texture;
	this->texturePlayer->loadFromFile("Assets/Tiles/Sprite-0003.png");

	this->textureBed = new sf::Texture;
	this->textureBed->loadFromFile("Assets/Tiles/Sprite-0004.png");	
}

void GameState::initViews()
{
	//===INIT WORLD VIEW===//
	this->viewWorld = window->getDefaultView();

	sf::Vector2f scale;
	scale.x = window->getDefaultView().getSize().x / 1280.f;
	scale.y = window->getDefaultView().getSize().y / 720.f;

	this->viewWorld.setViewport(sf::FloatRect(0, 0, .6f, 1.f));
	//---INIT WORLD VIEW---//

	//===INIT PLAYER VIEW===//
	this->miniview = HUD(this->window, this->fontConnectionII);
	//===INIT PLAYER VIEW===//

	//===INIT PLAYER MENU===//
	this->playerMenu = Menu(this->window, &this->fontConnectionII);
	//---INIT PLAYER MENU---//
}

void GameState::initBackground()
{
}

void GameState::initBools()
{
	this->booleansPlayerFunctions.insert({"Sleep", new bool});
	this->booleansPlayerFunctions.insert({"GetHigh", new bool});
	this->booleansPlayerFunctions.insert({"Study", new bool});

	for (auto iter = this->booleansPlayerFunctions.begin(); iter != this->booleansPlayerFunctions.end(); iter++)
	{
		*this->booleansPlayerFunctions[iter->first] = false;
	}
}

void GameState::initButtons()
{
	sf::Vector2f viewWorldScale;
	viewWorldScale.x = this->window->getDefaultView().getSize().x / 1280.f / this->viewWorld.getViewport().width;
	viewWorldScale.y = this->window->getDefaultView().getSize().y / 720.f / this->viewWorld.getViewport().height;

	this->buttonsHidden.insert({ "Sleep", new Button(sf::Vector2f(256.f, 64.f)) });
	this->buttonsHidden["Sleep"]->setBoolean(this->booleansPlayerFunctions["Sleep"], true);
	this->buttonsHidden["Sleep"]->add(new ButtonComponent::Movement);
	this->buttonsHidden["Sleep"]->setScale(sf::Vector2f(viewWorldScale.x * .5f, viewWorldScale.y * .5f));
	this->buttonsHidden["Sleep"]->getMovementComponent()->change = sf::Vector2f(-7.5f * viewWorldScale.x, -7.5f * viewWorldScale.y);

	this->buttonsHidden.insert({ "Study", new Button(sf::Vector2f(256.f, 64.f)) });
	this->buttonsHidden["Study"]->setBoolean(this->booleansPlayerFunctions["Study"], true);
	this->buttonsHidden["Study"]->add(new ButtonComponent::Movement);
	this->buttonsHidden["Study"]->setScale(sf::Vector2f(viewWorldScale.x * .5f, viewWorldScale.y * .5f));
	this->buttonsHidden["Study"]->getMovementComponent()->change = sf::Vector2f(-7.5f * viewWorldScale.x, -7.5f * viewWorldScale.y);

	//====MAIN VIEW===//
	this->playerMenu.getButtons(0).setBoolean(this->booleansPlayerFunctions["GetHigh"], true);
	//---MAIN VIEW---//
}

//---INITIALIZE FUNCTIONS---//
GameState::GameState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed, std::map<std::string, bool*> booleans) : State(window, mosPosWindow, mosPosView, keyBinds, keyBindPressed, booleans)
{
	this->initTextures();
	this->initViews();
	this->initBackground();
	this->initBools();
	this->initButtons();

	sf::Vector2f scale;
	scale.x = this->window->getDefaultView().getSize().x / 1280.f;
	scale.y = this->window->getDefaultView().getSize().y / 720.f;

	sf::Vector2f viewWorldScale;
	viewWorldScale.x = scale.x / this->viewWorld.getViewport().width;
	viewWorldScale.y = scale.y / this->viewWorld.getViewport().height;

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
	if (!this->map.load("Assets/Tiles/floorTileSheet.png", sf::Vector2u(64, 64), level, 16, 8, viewWorldScale))
		std::cout << "IT AINT LOAD" << std::endl;

	this->map.setPosition(sf::Vector2f(this->window->getView().getSize().x / 2.f - this->map.getGlobalBounds().width / 2.f, this->window->getView().getSize().y / 2.f - this->map.getGlobalBounds().height / 2.f));

	this->player = new Player(this->texturePlayer, sf::Vector2f(this->map.getGlobalBounds().left + this->map.getGlobalBounds().width / 2.f, this->map.getGlobalBounds().top + this->map.getGlobalBounds().height / 2.f), viewWorldScale, this->keyBinds, this->keyBindPressed);
	this->player->setPosition(sf::Vector2f(this->player->getGlobalBounds().left - this->player->getGlobalBounds().width / 2.f, this->player->getGlobalBounds().top - this->player->getGlobalBounds().height / 2.f));


	this->worldItems.push_back(new Item(*this->textureBed)); // BED
	this->worldItems[0]->setScale(viewWorldScale);
	this->worldItems[0]->add(new ItemComponent::WorldCollision);
	this->worldItems[0]->setPosition(sf::Vector2f(this->map.getGlobalBounds().left, this->map.getGlobalBounds().top + this->map.getGlobalBounds().height - this->worldItems[0]->getGlobalBounds().height));
	this->worldItems[0]->getCollisionComponent()->button = this->buttonsHidden["Sleep"];
	this->buttonsHidden["Sleep"]->setPosition(sf::Vector2f(this->worldItems[0]->getGlobalBounds().left + this->worldItems[0]->getGlobalBounds().width / 2.f - this->buttonsHidden["Sleep"]->getGlobalBounds().width / 2.f, this->worldItems[0]->getGlobalBounds().top - this->buttonsHidden["Sleep"]->getGlobalBounds().height * 1.5f));


	this->worldItems.push_back(new Item(*this->textureBed)); // DESK
	this->worldItems[1]->setColor(sf::Color(192, 64, 0));
	this->worldItems[1]->setScale(viewWorldScale);
	this->worldItems[1]->add(new ItemComponent::WorldCollision);
	this->worldItems[1]->setPosition(sf::Vector2f(this->map.getGlobalBounds().left + this->map.getGlobalBounds().width / 2.f - this->worldItems[1]->getGlobalBounds().width / 2.f, this->map.getGlobalBounds().top));
	this->worldItems[1]->getCollisionComponent()->button = this->buttonsHidden["Study"];
	this->buttonsHidden["Study"]->setPosition(sf::Vector2f(this->worldItems[1]->getGlobalBounds().left + this->worldItems[1]->getGlobalBounds().width / 2.f - this->buttonsHidden["Study"]->getGlobalBounds().width / 2.f, this->worldItems[1]->getGlobalBounds().top - this->buttonsHidden["Study"]->getGlobalBounds().height * 1.5f));



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

void GameState::updateTimers(const float& dt)
{
	this->cooldownPauseCreation += sf::seconds(dt);
}

void GameState::updateDate(const float& dt)
{
	float timeBlend = 0;

	if (this->player->getToxicology().getSobriety<double>() < 80.0)
	{
		timeBlend += 5;
	}
	if (80.0 <= this->player->getToxicology().getSobriety<double>() && this->player->getToxicology().getSobriety<double>() < 95)
	{
		timeBlend += 1.5 + std::pow(2.5, 100.0 / this->player->getToxicology().getSobriety<double>());
	}
	if (this->player->getPsychology().getIsStudying())
	{
		timeBlend += 7;
	}	
	if (this->player->getPsychology().getIsAsleep())
	{
		timeBlend += 15;
	}
	
	if (static_cast<int>(timeBlend) == 0)
	{
		this->date.update(dt);
	}
	else
	{
		this->date.update(dt * timeBlend);
	}
	std::cout << "Day: " << this->date.getDayAsString() << " Time: " << this->date.getTimeAsString() << std::endl;
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

void GameState::updatePlayerFunctions()
{
	switch (*this->booleansPlayerFunctions["GetHigh"])
	{
	case true:
		if (!this->player->getPsychology().getIsAsleep())
		{
			this->player->getToxicology().getHigh();
		}
		*this->booleansPlayerFunctions["GetHigh"] = false;
		break;
	default:
		break;
	}

	switch (*this->booleansPlayerFunctions["Sleep"])
	{
	case true:
		this->player->getPsychology().sleep();
		*this->booleansPlayerFunctions["Sleep"] = false;
		if (!this->player->getPsychology().getIsAsleep())
		{
			this->player->setPosition(sf::Vector2f(this->worldItems[0]->getCollisionComponent()->radius.left + this->worldItems[0]->getCollisionComponent()->radius.width, this->worldItems[0]->getCollisionComponent()->radius.top));
		}
		break;
	default:
		break;
	}	

	switch (*this->booleansPlayerFunctions["Study"])
	{
	case true:
		this->player->getPsychology().study();
		*this->booleansPlayerFunctions["Study"] = false;
		break;
	default:
		break;
	}	
}

void GameState::updateViewWorld(const float& dt)
{
	this->updateTimers(dt);

	this->updateDate(dt);

	this->updateInput();

	this->updatePlayerFunctions();

	this->player->update(dt);

	this->player->updateCollision(this->map.getGlobalBounds());

	//===UPDATE PLAYER-WORLDITEM COLLISION===//
	sf::Vector2f relativeMousePosView = this->window->mapPixelToCoords(*this->mosPosWindow, viewWorld);

	sf::Vector2f mtv;
	for (int i = 0; i < this->worldItems.size(); i++)
	{
		satCollision(this->player->getGlobalBounds(), this->worldItems[i]->getGlobalBounds(), &mtv);
	}
	if (!this->player->getPsychology().getIsAsleep())
	{
		this->player->move(mtv);
	}
	else
	{
		this->player->setPosition(sf::Vector2f(this->worldItems[0]->getGlobalBounds().left + this->worldItems[0]->getGlobalBounds().width / 2.f - this->player->getGlobalBounds().width / 2.f, this->worldItems[0]->getGlobalBounds().top));
	}
	//---UPDATE PLAYER-WORLDITEM COLLISION---//

	//===UPDATE POPUP BUTTONS===//
	for (int i = 0; i < this->worldItems.size(); i++)
	{
		if (satCollision(this->player->getGlobalBounds(), this->worldItems[i]->getCollisionComponent()->radius))
		{
			if (this->worldItems[i]->getCollisionComponent()->button) // If it's not a nullptr
			{
				// Create Mouse Position relative to the current view, not default view
				this->worldItems[i]->getCollisionComponent()->button->update(dt, relativeMousePosView);
			}
		}
	}

	//---UPDATE POPUP BUTTONS---//

	this->viewWorld.setCenter(sf::Vector2f(this->player->getGlobalBounds().left + this->player->getGlobalBounds().width / 2.f, this->player->getGlobalBounds().top + this->player->getGlobalBounds().height / 2.f));
}

void GameState::updateViews(const float& dt)
{
	std::string stats[6];
	stats[0] = this->player->getPsychology().getIntelligenceAsString<int>();
	stats[1] = this->player->getPsychology().getJoyAsString<int>();
	stats[2] = this->player->getToxicology().getSobrietyAsString<int>();
	stats[3] = "0"; // GPA
 	stats[4] = this->player->getPsychology().getSadnessAsString<int>();
	stats[5] = this->player->getPsychology().getFatigueAsString<int>();

	this->miniview.update(dt, stats);

	this->playerMenu.update(dt, this->mosPosWindow);
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

	this->updateViewWorld(dt);
	this->updateViews(dt);
}

void GameState::renderViewWorld(sf::RenderTarget* target)
{
	target->setView(this->viewWorld);

	target->draw(this->map);

	for (int i = 0; i < this->worldItems.size(); i++)
	{
		target->draw(*this->worldItems[i]);
	}
	target->draw(*this->player);


	for (int i = 0; i < this->worldItems.size(); i++)
	{
		if (satCollision(this->player->getGlobalBounds(), this->worldItems[i]->getCollisionComponent()->radius))
		{
			if (this->worldItems[i]->getCollisionComponent()->button) // If it's not a nullptr
			{
				target->draw(*this->worldItems[i]->getCollisionComponent()->button);
			}
		}
	}

	target->setView(this->window->getDefaultView());
}

void GameState::renderViews(sf::RenderTarget* target)
{
	this->miniview.render(target);
	this->playerMenu.render(target);
}

void GameState::render(sf::RenderTarget* target)
{
	/*
	Render Hierarchy
		Map
		Player
	*/

	this->renderViewWorld(target);
	this->renderViews(target);

	if (!this->stateStack.empty()) // As long as the stack is not empty, it will render the top
	{
		this->stateStack.top()->render(target);
	}
}
