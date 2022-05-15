#include "HUD.h"



HUD::HUD()
{
    // Use pointer
}

HUD::HUD(sf::RenderWindow* window)
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
    this->vertices[1].position = sf::Vector2f(1280.f*scaleX, 0.f);
    this->vertices[2].position = sf::Vector2f(1280.f*scaleX, 720.f*scaleY);
    this->vertices[3].position = sf::Vector2f(0.f, 720.f*scaleY);
    this->vertices[0].color = sf::Color::Red;
    this->vertices[1].color = sf::Color::Blue;
    this->vertices[2].color = sf::Color::Green;
    this->vertices[3].color = sf::Color::Yellow;

    float x = ((1280.f - (1280.f * .4f)) * scaleX) / (1280.f * scaleX);
    float y = ((720.f - (720.f * .5f)) * scaleY) / (720.f * scaleY);
    this->view.setViewport(sf::FloatRect(x, y, .4f, .5f));
}

HUD::~HUD()
{
}



void HUD::update(const float& dt)
{
    

}

void HUD::render(sf::RenderTarget* target)
{
    target->setView(view);
    target->draw(this->vertices);
    target->setView(this->window->getDefaultView());


}