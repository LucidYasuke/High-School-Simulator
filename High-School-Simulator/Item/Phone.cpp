#include "Phone.h"

Phone::Phone()
{
	sf::ConvexShape convex;

	convex.setPointCount(4);

	convex.setPoint(0, sf::Vector2f(0,0));
	convex.setPoint(1, sf::Vector2f(0,5));
	convex.setPoint(2, sf::Vector2f(2,5));
	convex.setPoint(3, sf::Vector2f(2,0));
}

Phone::~Phone()
{
}

Phone* Phone::clone()
{
	return nullptr;
}

void Phone::update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center)
{
}

void Phone::render(sf::RenderTarget& target)
{
}
