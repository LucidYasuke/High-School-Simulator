#include "Shapes.h"


const float CapsuleShape::pi = 3.141592654f;

CapsuleShape::CapsuleShape(const sf::Vector2f& size) : ConvexShape(38)
{
    this->setSize(size);
}

void CapsuleShape::setSize(sf::Vector2f size)
{
    if (size.x < 0.f)
    {
        size.x = 0.f;
    }
    if (size.y < 0.f)
    {
        size.y = 0.f;
    }

    sf::Vector2f radius;
    radius.x = size.x * 1.f / 10.f;
    radius.y = size.y * 1.f / 2.f;


    for (int i = 0; i < 19; i++)
    {
        float angle = i * 2 * pi / 36 - pi / 2;
        this->setPoint(i, sf::Vector2f((size.x * 4.f / 5.f) + radius.x + std::cos(angle) * radius.x, radius.y + std::sin(angle) * radius.y));
    }

    this->setPoint(19, sf::Vector2f(this->getPoint(18).x - (size.x * 3.f / 5.f), this->getPoint(18).y));

    for (int i = 20; i < 38; i++)
    {
        float angle = (i - 1) * 2 * pi / 36 - pi / 2;
        this->setPoint(i, sf::Vector2f(radius.x + std::cos(angle) * radius.x, radius.y + std::sin(angle) * radius.y));
    }
    this->sf::ConvexShape::update();
}

void CapsuleShape::setPointCount(std::size_t count)
{
    this->sf::ConvexShape::setPointCount(38);
}
