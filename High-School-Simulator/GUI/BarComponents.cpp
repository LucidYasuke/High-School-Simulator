#include "BarComponents.h"


void Components::Bar::Progress::update(double ratio)
{
	this->layer.setSize(sf::Vector2f(this->base.getGlobalBounds().width * static_cast<float>(ratio), this->base.getGlobalBounds().height));
}

void Components::Bar::Progress::render(sf::RenderTarget* target)
{
	target->draw(base);
	target->draw(layer);
}
