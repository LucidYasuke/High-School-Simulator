#include "Shapes.h"


PillShape::PillShape(sf::Vector2f size)
{
    this->circleDefaultScale = sf::Vector2f(1.f, size.y / (size.x * 1.f / 5.f));

    this->left.setRadius(size.x * 1.f / 10.f); // Total diameter is 1/5
    this->left.setScale(this->circleDefaultScale);

    this->right.setRadius(size.x * 1.f / 10.f);
    this->right.setScale(this->circleDefaultScale);

    this->middle.setSize(sf::Vector2f(size.x * 4.f / 5.f, size.y));
    this->middle.setPosition(sf::Vector2f(this->left.getGlobalBounds().left + this->left.getGlobalBounds().width / 2.f, this->left.getGlobalBounds().top));
    
    this->right.setPosition(sf::Vector2f(this->middle.getGlobalBounds().left + this->middle.getGlobalBounds().width - this->right.getGlobalBounds().width / 2.f, this->middle.getGlobalBounds().top));
}

PillShape::~PillShape()
{
}

void PillShape::setPosition(sf::Vector2f position)
{
    this->left.setPosition(position);
    this->middle.setPosition(sf::Vector2f(this->left.getGlobalBounds().left + this->left.getGlobalBounds().width / 2.f, this->left.getGlobalBounds().top));
    this->right.setPosition(sf::Vector2f(this->middle.getGlobalBounds().left + this->middle.getGlobalBounds().width - this->right.getGlobalBounds().width / 2.f, this->middle.getGlobalBounds().top));
}

void PillShape::setSize(sf::Vector2f size)
{
    sf::Vector2f currentScale = this->left.getScale();
    currentScale = sf::Vector2f(currentScale.x / this->circleDefaultScale.x, currentScale.y / this->circleDefaultScale.y);

    this->circleDefaultScale = sf::Vector2f(1.f, size.y / (size.x * 1.f / 5.f));


    this->left.setRadius(size.x * 1.f / 10.f);
    this->right.setRadius(size.x * 1.f / 10.f);
    this->middle.setSize(sf::Vector2f(size.x * 4.f / 5.f, size.y));

    this->setScale(currentScale);
}

void PillShape::setScale(sf::Vector2f scale)
{
    this->left.setScale(sf::Vector2f(this->circleDefaultScale.x * scale.x, this->circleDefaultScale.y * scale.y));
    this->right.setScale(sf::Vector2f(this->circleDefaultScale.x * scale.x, this->circleDefaultScale.y * scale.y));
    this->middle.setScale(scale);
}

void PillShape::setFillColor(sf::Color color)
{
    this->left.setFillColor(color);
    this->middle.setFillColor(color);
    this->right.setFillColor(color);
}

sf::FloatRect PillShape::getGlobalBounds()
{
    float width;
    width = this->left.getGlobalBounds().width / 2.f + this->middle.getGlobalBounds().width + this->right.getGlobalBounds().width / 2.f;
    width = std::ceil(width);

    return sf::FloatRect(this->left.getGlobalBounds().left, this->left.getGlobalBounds().top, width, this->middle.getGlobalBounds().height);
}

void PillShape::draw(sf::RenderTarget* target)
{
    target->draw(this->left);
    target->draw(this->middle);
    target->draw(this->right);
}
