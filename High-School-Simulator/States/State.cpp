#include "State.h"


//===ABSTRACT STATE===//
State::State(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed)
{
	this->window = window;
	this->quit = false;
	this->mosPosWindow = mosPosWindow;
	this->mosPosView = mosPosView;

	this->fontConnectionII.loadFromFile("Assets/Fonts/ConnectionIi-2wj8.otf");

	this->keyBinds = keyBinds;
	this->keyBindPressed = keyBindPressed;
}

State::State(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed, std::map<std::string, bool*> booleans)
{
	this->window = window;
	this->quit = false;
	this->mosPosWindow = mosPosWindow;
	this->mosPosView = mosPosView;

	this->fontConnectionII.loadFromFile("Assets/Fonts/ConnectionIi-2wj8.otf");

	this->keyBinds = keyBinds;
	this->keyBindPressed = keyBindPressed;

	this->booleans = booleans;
}

State::~State()
{
}

const bool& State::getQuit() const
{
	return this->quit;
}

/*
void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->quit = true;
	}
}
*/
