#include "LButton.h"

const sf::Time LButton::lastClickedMax = sf::seconds(0.25f);

void LButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= this->getTransform(); // getTransform() is defined by sf::Transformable

    // apply the texture
    states.texture = this->texture;

    // you may also override states.shader or states.blendMode if you want

    // draw the vertex array
    target.draw(this->vertices, states);
}

LButton::LButton()
{
    this->vertices = sf::VertexArray(sf::Quads, 4);

    // Defines it as a rectangle, located at (0, 0) and with size 4x4
    this->vertices[0].position = sf::Vector2f(0, 0);
    this->vertices[1].position = sf::Vector2f(4, 0);
    this->vertices[2].position = sf::Vector2f(4, 4);
    this->vertices[3].position = sf::Vector2f(0, 4);

    // Default color white
    this->vertices[0].color = sf::Color::White;
    this->vertices[1].color = sf::Color::White;
    this->vertices[2].color = sf::Color::White;
    this->vertices[3].color = sf::Color::White;


}

LButton::LButton(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale)
{
    this->texture = texture;

    this->vertices = sf::VertexArray(sf::Quads, 4);

    float textSizeX = static_cast<float>(this->texture->getSize().x);
    float textSizeY = static_cast<float>(this->texture->getSize().y);

    // Defines it as a rectangle, located at (0, 0) and with size (texture.size.x*scaleX)x(texture.size.y*scaleY)
    this->vertices[0].position = sf::Vector2f(0, 0);
    this->vertices[1].position = sf::Vector2f(textSizeX * scale.x, 0);
    this->vertices[2].position = sf::Vector2f(textSizeX * scale.x, textSizeY * scale.y);
    this->vertices[3].position = sf::Vector2f(0, textSizeY * scale.y);

    this->setPosition(position);

    // define its texture area to be a (texture.size.x)x(texture.size.y) rectangle starting at (0, 0)
    this->vertices[0].texCoords = sf::Vector2f(0, 0);
    this->vertices[1].texCoords = sf::Vector2f(textSizeX, 0);
    this->vertices[2].texCoords = sf::Vector2f(textSizeX, textSizeY);
    this->vertices[3].texCoords = sf::Vector2f(0, textSizeY);

}

LButton::~LButton()
{
}


sf::FloatRect LButton::getGlobalBounds()
{
    return sf::FloatRect(this->getPosition().x, this->getPosition().y, this->vertices[2].position.x - this->vertices[0].position.x, this->vertices[2].position.y - this->vertices[0].position.y);
}
