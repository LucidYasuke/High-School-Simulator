#include "PauseState.h"


//===INITIALIZE FUNCTIONS===//
void PauseState::initTextures()
{
	std::cout << this->window->getView().getSize().x;
	//===Init Button Textures===//
	this->textureButton.insert({ "Continue", new sf::Texture });
	this->textureButton.insert({ "Settings", new sf::Texture });
	this->textureButton.insert({ "Quit", new sf::Texture });

	this->textureButton["Continue"]->loadFromFile("Assets/Buttons/ButtonContinue.png");
	this->textureButton["Settings"]->loadFromFile("Assets/Buttons/ButtonSettings.png");
	this->textureButton["Quit"]->loadFromFile("Assets/Buttons/ButtonQuit.png");
	//---Init Button Textures---//
}

void PauseState::initTitle()
{
	// Create scales based off window default view size
	float scale = (this->window->getDefaultView().getSize().x + this->window->getDefaultView().getSize().y) / 2000.f;
	float scaleX = this->window->getDefaultView().getSize().x / 1280.f;
	float scaleY = this->window->getDefaultView().getSize().y / 720.f;

	// Create text config
	this->textTitle.setFont(this->fontConnectionII);
	this->textTitle.setCharacterSize(static_cast<unsigned int>(128.f * scale));
	this->textTitle.setStyle(sf::Text::Bold);
	this->textTitle.setString("PAUSE");
	this->textTitle.setLetterSpacing(1.5f * scale);

	// Set Positions
	this->textTitle.setPosition(sf::Vector2f(this->window->getDefaultView().getSize().x / 2.f - this->textTitle.getGlobalBounds().width / 2.f, this->window->getDefaultView().getSize().y / 2.f - this->textTitle.getGlobalBounds().height / 2.f - 150.f * scaleY));
}

void PauseState::initButtons()
{
	this->booleans.insert({ "ContinueGameState", &this->quit }); // ContinueGameState = QuitPauseState

	this->buttons.push_back(new Button(this->window, this->textureButton["Continue"], this->booleans["ContinueGameState"], true, 0.f, 150.f));
	this->buttons.push_back(new Button(this->window, this->textureButton["Settings"], new bool, true, 0.f, 225.f));
	this->buttons.push_back(new Button(this->window, this->textureButton["Quit"], this->booleans["QuitGameState"], true, 0.f, 300.f));
}
//---INITIALIZE FUNCTIONS---//
PauseState::PauseState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed, std::map<std::string, bool*> booleans) : State(window, mosPosWindow, mosPosView, keyBinds, keyBindPressed, booleans)
{
	this->initTextures();
	this->initTitle();
	this->initButtons();

	this->cooldownCreationMax = sf::seconds(0.5f);
}

PauseState::~PauseState()
{
	// Delete All The Buttons
	for (auto& i : this->buttons)
	{
		delete i;
	}
	this->buttons.clear();

	delete this->textureButton["Continue"];
	delete this->textureButton["Settings"];
	delete this->textureButton["Quit"];
}

void PauseState::endState()
{
	*this->booleans["PauseGameState"] = false;
}

void PauseState::confirmQuit()
{
}

void PauseState::resetButton()
{
	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->reset();
	}
}


void PauseState::updateInput()
{
	if (this->keyBindPressed->at("PAUSE"))
	{
		if (this->cooldownCreation >= this->cooldownCreationMax)
		{
			this->quit = true;
		}
	}
}

void PauseState::update(const float& dt)
{
	this->cooldownCreation += sf::seconds(dt);
	this->updateInput();

	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->update(dt, *this->mosPosView);
	}
}

void PauseState::render(sf::RenderTarget* target)
{
	target->draw(this->textTitle);

	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->render(target);
	}
}

