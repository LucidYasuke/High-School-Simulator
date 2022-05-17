#include "HUD.h"

HUD::HUD()
{
    
    // Use pointer
}

HUD::HUD(sf::RenderWindow* window, sf::Font& fontConnectionII)
{
    this->window = window;

    // 1280.f x 720.f
    //as long as we're dealing with a window use getDefaultView
    float scaleX = this->window->getDefaultView().getSize().x / 1280.f;
    float scaleY = this->window->getDefaultView().getSize().y / 720.f;

    //set size to view (window is the window, get default view is the size you get when you open the window, get size searches the current size of the window, scale is the defaultview().getsize/ by 1280 or 720 and finally that number is multiplied by .25 

    this->view = this->window->getDefaultView();
    this->view.setViewport(sf::FloatRect(0.25f, 0.25, 0.5f, 0.5f));

    this->vertices = sf::VertexArray(sf::Quads, 4);
    this->vertices[0].position = sf::Vector2f(0.f, 0.f);
    this->vertices[1].position = sf::Vector2f(1280.f * scaleX, 0.f);
    this->vertices[2].position = sf::Vector2f(1280.f * scaleX, 720.f * scaleY);
    this->vertices[3].position = sf::Vector2f(0.f, 720.f * scaleY);


    this->vertices[0].color = sf::Color::White;
    this->vertices[1].color = sf::Color::White;
    this->vertices[2].color = sf::Color::White;
    this->vertices[3].color = sf::Color::White;

    this->view.setViewport(sf::FloatRect(.6f, .5f, .4f, .5f));

    // BRIAN:: SET THE POSITIONS OF THE NAMES FIRST, AND MAKE THE STATS RELATIVE OT THE NAME
    // TEXT ME ON DISCORD FOR MORE

    this->textStats[0].setFont(fontConnectionII);
    this->textStats[0].setCharacterSize(100.f * scaleX);
    this->textStats[0].setString("0");


    this->textStats[1] = this->textStats[0];

    this->textStats[0].setPosition(sf::Vector2f(this->window->getDefaultView().getSize().x / 2.f - this->textStats[0].getGlobalBounds().width / 2.f, this->window->getDefaultView().getSize().y / 2.f - this->textStats[0].getGlobalBounds().height / 2.f - 250.f * scaleY));
    /**
    this->textStats[0].setseo();
    this->textStats[0].set();
    **/
}


HUD::~HUD()
{
}

void HUD::update(const float& dt, std::string stats[5])
{
    // FOR LOOP THROUGH GIVEN LIST
    /**
    fOR I IN RANGE 5
    THIS->TEXTsTATS[I].SETSTRING(STATS[I]);
    **/

}

void HUD::render(sf::RenderTarget* target)
{
    target->setView(view);
    target->draw(this->vertices);

    /**
    FOR IN IN RANGE 5
    TARGET->DRAW(THIS->TEXtStats[i])
    **/

    target->setView(this->window->getDefaultView());
}