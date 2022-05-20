#include "Menu.h"

Menu::Menu()
{
}

Menu::Menu(sf::RenderWindow* window, sf::Font* fontConnectionII)
{
    this->window = window;
    this->font = fontConnectionII;

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
    for (int i  = 0; i < 4; i++)
    {
        this->background[i].color = sf::Color::White;
    }

    this->border = sf::VertexArray(sf::Quads, 16);
    // TOP
    this->border[0].position = multiplyVector(sf::Vector2f(0.f, 0.f), scale);
    this->border[1].position = multiplyVector(sf::Vector2f(1280.f, 0.f), scale);
    this->border[2].position = multiplyVector(sf::Vector2f(1280.f, 45.f), scale);
    this->border[3].position = multiplyVector(sf::Vector2f(0.f, 45.f), scale);
    // RIGHT
    this->border[4].position = multiplyVector(sf::Vector2f(1235.f, 0.f), scale);
    this->border[5].position = multiplyVector(sf::Vector2f(1280.f, 0.f), scale);
    this->border[6].position = multiplyVector(sf::Vector2f(1280.f, 720.f), scale);
    this->border[7].position = multiplyVector(sf::Vector2f(1235.f, 720.f), scale);
    // BOT
    this->border[8].position = multiplyVector(sf::Vector2f(0.f, 675.f), scale);
    this->border[9].position = multiplyVector(sf::Vector2f(1280.f, 675.f), scale);
    this->border[10].position = multiplyVector(sf::Vector2f(1235.f, 720.f), scale);
    this->border[11].position = multiplyVector(sf::Vector2f(0.f, 720.f), scale);
    // LEFT
    this->border[12].position = multiplyVector(sf::Vector2f(0.f, 0.f), scale);
    this->border[13].position = multiplyVector(sf::Vector2f(45.f, 0.f), scale);
    this->border[14].position = multiplyVector(sf::Vector2f(45.f, 720.f), scale);
    this->border[15].position = multiplyVector(sf::Vector2f(0.f, 720.f), scale);
    for (int i = 0; i < 16; i++)
    {
        this->border[i].color = sf::Color::Black;
    }

    this->bounds = sf::FloatRect(45.f * scale.x, 45.f * scale.y, 1190.f * scale.x, 630 * scale.y); // Non Border Area | Pre Scaled
     
    this->view.setViewport(sf::FloatRect(.6f, 0, .4f, .5f));
}

Menu::~Menu()
{
}

void Menu::updateMainMenu()
{
}

void Menu::update(const float& dt)
{
}

void Menu::renderMainMenu(sf::RenderTarget* target)
{
    float totalScale = (this->window->getDefaultView().getSize().x + this->window->getDefaultView().getSize().y) / 2000.f;
    sf::Vector2f defualtSize = this->window->getDefaultView().getSize();
    sf::Vector2f scale = divideVector(this->window->getDefaultView().getSize(), sf::Vector2f(1280.f, 720.f));

    sf::Text numbers[5];
    numbers[0].setFont(*this->font);
    numbers[0].setCharacterSize(50.f * totalScale);
    numbers[0].setFillColor(sf::Color::Magenta);
    numbers[0].setString("1");

    for (int i = 1; i < 5; i++)
    {
        numbers[i] = numbers[0];
        numbers[i].setString(std::to_string(i + 1));
    }

    // Add bounds.left if not centered
    numbers[0].setPosition(sf::Vector2f(this->bounds.left + this->bounds.width * 1.f / 8.f - numbers[0].getGlobalBounds().width / 2.f, this->bounds.top + this->bounds.height * 1.f / 10.f - numbers[0].getGlobalBounds().height / 2.f));
    numbers[1].setPosition(sf::Vector2f(this->bounds.left + this->bounds.width * 1.f / 8.f - numbers[1].getGlobalBounds().width / 2.f, this->bounds.top + this->bounds.height * 3.f / 10.f - numbers[1].getGlobalBounds().height / 2.f));
    numbers[2].setPosition(sf::Vector2f(this->bounds.left + this->bounds.width * 1.f / 8.f - numbers[2].getGlobalBounds().width / 2.f, this->bounds.top + this->bounds.height * 5.f / 10.f - numbers[2].getGlobalBounds().height / 2.f));
    numbers[3].setPosition(sf::Vector2f(this->bounds.left + this->bounds.width * 1.f / 8.f - numbers[3].getGlobalBounds().width / 2.f, this->bounds.top + this->bounds.height * 7.f / 10.f - numbers[3].getGlobalBounds().height / 2.f));
    numbers[4].setPosition(sf::Vector2f(this->bounds.left + this->bounds.width * 1.f / 8.f - numbers[4].getGlobalBounds().width / 2.f, this->bounds.top + this->bounds.height * 9.f / 10.f - numbers[4].getGlobalBounds().height / 2.f));

    for (int i = 0; i < 5; i++)
    {
        target->draw(numbers[i]);
    }
}

void Menu::render(sf::RenderTarget* target)
{
    target->setView(this->view);
    target->draw(this->background);
    target->draw(this->border);
    this->renderMainMenu(target);

    target->setView(this->window->getDefaultView());
}
