#include "ProgressBar.h"


ProgressBar::ProgressBar(Align pos, float x, float y, float w, float l, sf::Time* currentTime, sf::Time* maxTime) : GUI(pos, x, y, w, l)
{
	this->currentTime = currentTime;
	this->maxTime = maxTime;
	this->ratio = this->currentTime->asSeconds() / this->maxTime->asSeconds();

	this->back.setSize(sf::Vector2f(this->w, this->l));
	this->back.setPosition(sf::Vector2f(this->x, this->y));
	this->back.setFillColor(sf::Color(39, 33, 79));

	this->front.setSize(sf::Vector2f(this->w * this->ratio, this->l));
	this->front.setPosition(sf::Vector2f(this->x, this->y));
	this->front.setFillColor(sf::Color(134, 59, 135));
}

ProgressBar::~ProgressBar()
{

}

void ProgressBar::update()
{	if (this->maxTime->asSeconds() < 0.009f)
	{
		this->front.setSize(sf::Vector2f(this->w, this->front.getSize().y));
		return;
	}
	this->ratio = this->currentTime->asSeconds() / this->maxTime->asSeconds();
	this->front.setSize(sf::Vector2f(this->w * this->ratio, this->front.getSize().y));
}

void ProgressBar::render(sf::RenderTarget* target)
{
	target->draw(this->back);
	target->draw(this->front);
}
