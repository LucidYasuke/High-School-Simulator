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
	float totalScale = (this->window->getDefaultView().getSize().x + this->window->getDefaultView().getSize().y) / 2000.f;

	float scaleX = this->window->getDefaultView().getSize().x / 1280.f;
	float scaleY = this->window->getDefaultView().getSize().y / 720.f;

	// Create text config
	this->textTitle[0].setFont(this->fontConnectionII);
	this->textTitle[0].setCharacterSize(static_cast<unsigned int>(128.f * totalScale));
	this->textTitle[0].setStyle(sf::Text::Bold);
	this->textTitle[0].setLetterSpacing(1.1f * totalScale);

	// Copying Objects with same configs
	this->textTitle[1] = this->textTitle[0];
	this->textTitle[1].setCharacterSize(static_cast<unsigned int>(96.f * totalScale));

	// Set the names
	this->textTitle[0].setString("HIGH SCHOOL");
	this->textTitle[1].setString("SIMULATOR");

	// Set Positions
	this->textTitle[0].setPosition(sf::Vector2f(this->window->getDefaultView().getSize().x / 2.f - this->textTitle[0].getGlobalBounds().width / 2.f, this->window->getDefaultView().getSize().y / 2.f - this->textTitle[0].getGlobalBounds().height / 2.f - 250.f * scaleY));
	this->textTitle[1].setPosition(sf::Vector2f(this->window->getDefaultView().getSize().x / 2.f - this->textTitle[1].getGlobalBounds().width / 2.f, this->window->getDefaultView().getSize().y / 2.f - this->textTitle[1].getGlobalBounds().height / 2.f - 100.f * scaleY));
}

void TitleState::initButtons()
{
	sf::Vector2f scale = divideVector(this->window->getDefaultView().getSize(), sf::Vector2f(1280.f, 720.f));

	this->booleans.insert({ "QuitGame", &this->quit });

	for (int i = 0; i < 5; i++)
	{
		this->buttons.push_back(new Button(sf::Vector2f(256.f, 64.f)));
		this->buttons[i]->setTexture(this->textureButton["Blank"]);

		this->buttons[i]->add(new ButtonComponent::Movement);
		this->buttons[i]->setScale(scale);
		this->buttons[i]->setPosition(sf::Vector2f(this->window->getDefaultView().getSize().x / 2.f - this->buttons[i]->getGlobalBounds().width / 2.f, this->window->getDefaultView().getSize().y / 2.f - this->buttons[i]->getGlobalBounds().height / 2.f));
		
		switch (i)
		{
		case 0:
			this->buttons[i]->setBoolean(this->booleans["CreateGameState"], true);
			this->buttons[i]->setTexture(this->textureButton["Start"]);
			this->buttons[i]->getMovementComponent()->change = multiplyVector(sf::Vector2f(-7.5f, -7.5f), scale);
			this->buttons[i]->setPosition(this->buttons[i]->getPosition() + multiplyVector(sf::Vector2f(-132.5f, 150.f), scale));
			break;
		case 1:
			this->buttons[i]->setBoolean(new bool, true);
			this->buttons[i]->setTexture(this->textureButton["Blank"]);
			this->buttons[i]->getMovementComponent()->change = multiplyVector(sf::Vector2f(7.5, -7.5f), scale);
			this->buttons[i]->setPosition(this->buttons[i]->getPosition() + multiplyVector(sf::Vector2f(132.5f, 150.f), scale));
			break;
		case 2:
			this->buttons[i]->setBoolean(new bool, true);
			this->buttons[i]->setTexture(this->textureButton["Blank"]);
			this->buttons[i]->getMovementComponent()->change = multiplyVector(sf::Vector2f(-7.5, -7.5f), scale);
			this->buttons[i]->setPosition(this->buttons[i]->getPosition() + multiplyVector(sf::Vector2f(-132.5f, 225.f), scale));
			break;		
		case 3:
			this->buttons[i]->setBoolean(new bool, true);
			this->buttons[i]->setTexture(this->textureButton["Settings"]);
			this->buttons[i]->getMovementComponent()->change = multiplyVector(sf::Vector2f(7.5, -7.5f), scale);
			this->buttons[i]->setPosition(this->buttons[i]->getPosition() + multiplyVector(sf::Vector2f(132.5f, 225.f), scale));
			break;		
		case 4:
			this->buttons[i]->setBoolean(this->booleans["QuitGame"], true);
			this->buttons[i]->setTexture(this->textureButton["Quit"]);
			this->buttons[i]->getMovementComponent()->change = multiplyVector(sf::Vector2f(-7.5, 7.5f), scale);
			this->buttons[i]->setPosition(this->buttons[i]->getPosition() + multiplyVector(sf::Vector2f(0.f, 300.f), scale));
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < this->buttons.size(); i++)
	{
		//std::cout << i << " [" << this->buttons[i]->getPosition().x << "," << this->buttons[i]->getPosition().y << "]" << std::endl;
	}
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
		target->draw(*buttons[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		target->draw(this->textTitle[i]);
	}
}
