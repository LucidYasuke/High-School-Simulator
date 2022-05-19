#include "Menu.h"

Menu::Menu()
{
}

Menu::Menu(sf::RenderWindow* window, sf::Font& fontConnectionII)
{
    this->window = window;

    // 1280.f x 720.f
    // As long as we're dealing with a window use getDefaultView
    float totalScale = (this->window->getDefaultView().getSize().x + this->window->getDefaultView().getSize().y) / 2000.f;
    sf::Vector2f defualtSize = this->window->getDefaultView().getSize();
    sf::Vector2f scale = divideVector(this->window->getDefaultView().getSize(), sf::Vector2f(1280.f, 720.f));

    this->view = this->window->getDefaultView();

    this->background = sf::VertexArray(sf::Quads, 4);
    this->background[0].position = multiplyVector(sf::Vector2f(0.f, 0.f), scale);
    this->background[1].position = multiplyVector(sf::Vector2f(1280.f, 0.f), scale);
    this->background[2].position = multiplyVector(sf::Vector2f(1280.f, 720.f), scale);
    this->background[3].position = multiplyVector(sf::Vector2f(0.f, 720.f), scale);

    this->border = sf::VertexArray(sf::Quads, 16);
    this->border[0].position = sf::Vector2f(0.f, 0.f);
    this->border[1].position = sf::Vector2f(1280.f * scaleX, 0.f);
    this->border[2].position = sf::Vector2f(1280.f * scaleX, 720.f * scaleY);
    this->border[3].position = sf::Vector2f(0.f, 720.f * scaleY);


    this->border[0].color = sf::Color::White;
    this->border[1].color = sf::Color::White;
    this->border[2].color = sf::Color::White;
    this->border[3].color = sf::Color::White;

    this->view.setViewport(sf::FloatRect(.6f, 0, .4f, .5f));
}

Menu::~Menu()
{
}
