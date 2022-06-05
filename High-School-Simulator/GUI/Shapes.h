#ifndef SHAPES_H
#define SHAPES_H


#include <SFML/Graphics.hpp>


class CapsuleShape : public sf::ConvexShape
{
private:
	static const float pi;
public:
	CapsuleShape(const sf::Vector2f& size = sf::Vector2f(0.f, 0.f));
	void setSize(sf::Vector2f size);

	void setPointCount(std::size_t count);
};


#endif
