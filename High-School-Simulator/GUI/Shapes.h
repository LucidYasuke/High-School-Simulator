#ifndef SHAPES_H
#define SHAPES_H


#include <SFML/Graphics.hpp>


class PillShape
{
private:
	sf::Vector2f circleDefaultScale;

	sf::CircleShape left, right;
	sf::RectangleShape middle;
public:
	PillShape(sf::Vector2f size = sf::Vector2f(0.f, 0.f));
	virtual ~PillShape();

	void setPosition(sf::Vector2f position);
	void setSize(sf::Vector2f size);
	void setScale(sf::Vector2f scale);
	void setFillColor(sf::Color color);

	sf::FloatRect getGlobalBounds();

	void draw(sf::RenderTarget* target);
};


#endif
