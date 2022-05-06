#include "TitleState.h"


//===INITIALIZE FUNCTIONS===//
void TitleState::initTextures()
{
	//===Init Button Textures===//
	this->textureButton.insert({ "Start", new sf::Texture });
	this->textureButton.insert({ "Blank", new sf::Texture });
	this->textureButton.insert({ "Settings", new sf::Texture });
	this->textureButton.insert({ "Quit", new sf::Texture });

	this->textureButton["Start"]->loadFromFile("Assets/Buttons/ButtonStart.png");
	this->textureButton["Blank"]->loadFromFile("Assets/Buttons/ButtonBlank.png");
	this->textureButton["Settings"]->loadFromFile("Assets/Buttons/ButtonSettings.png");
	this->textureButton["Quit"]->loadFromFile("Assets/Buttons/ButtonQuit.png");
	//---Init Button Textures---//
}

void TitleState::initTitle()
{
	// Create scales based off window default view size
	float scale = (this->window->getDefaultView().getSize().x + this->window->getDefaultView().getSize().y) / 2000.f;
	float scaleX = this->window->getDefaultView().getSize().x / 1280.f;
	float scaleY = this->window->getDefaultView().getSize().y / 720.f;

	// Create text config
	this->textTitle[0].setFont(this->fontConnectionII);
	this->textTitle[0].setCharacterSize(static_cast<unsigned int>(128.f * scale));
	this->textTitle[0].setStyle(sf::Text::Bold);
	this->textTitle[0].setLetterSpacing(1.1f * scale);

	// Copying Objects with same configs
	this->textTitle[1] = this->textTitle[0];

	// Set the names
	this->textTitle[0].setString("HIGH SCHOOL");
	this->textTitle[1].setString("SIMULATOR");

	// Set Positions
	this->textTitle[0].setPosition(sf::Vector2f(this->window->getDefaultView().getSize().x / 2.f - this->textTitle[0].getGlobalBounds().width / 2.f, this->window->getDefaultView().getSize().y / 2.f - this->textTitle[0].getGlobalBounds().height / 2.f - 250.f * scaleY));
	this->textTitle[1].setPosition(sf::Vector2f(this->window->getDefaultView().getSize().x / 2.f - this->textTitle[1].getGlobalBounds().width / 2.f, this->window->getDefaultView().getSize().y / 2.f - this->textTitle[1].getGlobalBounds().height / 2.f - 100.f * scaleY));
}

void TitleState::initButtons()
{
	this->booleans.insert({ "QuitGame", &this->quit });

	this->buttons.push_back(new Button(this->window, this->textureButton["Start"], this->booleans["CreateGameState"], true, -132.5f, 150.f));
	this->buttons.push_back(new Button(this->window, this->textureButton["Blank"], new bool, true, 132.5f, 150.f));
	this->buttons.push_back(new Button(this->window, this->textureButton["Blank"], new bool, true, -132.5f, 225.f));
	this->buttons.push_back(new Button(this->window, this->textureButton["Settings"], new bool, true, 132.5f, 225.f));
	this->buttons.push_back(new Button(this->window, this->textureButton["Quit"], this->booleans["QuitGame"], true, 0.f, 300.f));
}
//---INITIALIZE FUNCTIONS---//

TitleState::TitleState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed, std::map<std::string, bool*> booleans) : State(window, mosPosWindow, mosPosView, keyBinds, keyBindPressed, booleans)
{
	this->initTextures();
	this->initTitle();
	this->initButtons();
}

TitleState::~TitleState()
{
	// Delete All The Buttons
	for (auto& i : this->buttons)
	{
		delete i;
	}
	this->buttons.clear();

	delete this->textureBackground;
	delete this->textureButton["Start"];
	delete this->textureButton["Blank"];
	delete this->textureButton["Settings"];
	delete this->textureButton["Quit"];

}

void TitleState::endState()
{
}

void TitleState::confirmQuit()
{
}

void TitleState::resetButton()
{
	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->reset();
	}
}

void TitleState::updateInput()
{
}

void TitleState::update(const float& dt)
{
	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->update(dt, *this->mosPosView);
	}
}

void TitleState::render(sf::RenderTarget* target)
{
	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->render(target);
	}

	for (int i = 0; i < 2; i++)
	{
		target->draw(this->textTitle[i]);
	}
}