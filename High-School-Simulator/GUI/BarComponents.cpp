#include "BarComponents.h"


void Component::Bar::Progress::update(double ratio)
{
	this->layer.setSize(sf::Vector2f(this->base.getGlobalBounds().width * static_cast<float>(ratio), this->base.getGlobalBounds().height));
}

void Component::Bar::Progress::render(sf::RenderTarget* target)
{
	target->draw(base);
	target->draw(layer);
	target->draw(border);
}
