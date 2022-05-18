#include "Entity.h"


const float Entity::lastAnimationShiftMax = .30f;

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= this->getTransform(); // getTransform() is defined by sf::Transformable

    // apply the texture
    states.texture = this->texture;

    // you may also override states.shader or states.blendMode if you want

    // draw the vertex array
    target.draw(this->vertices, states);
}

Entity::Entity()
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

    this->velocity = sf::Vector2f(100.f, 100.f);

}

Entity::Entity(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale)
{
    this->texture = texture;

    this->vertices = sf::VertexArray(sf::Quads, 4);

    float textSizeX = static_cast<float>(this->texture->getSize().x);
    float textSizeY = static_cast<float>(this->texture->getSize().y);

    // Defines it as a rectangle, located at (0, 0) and with size (texture.size.x*scaleX)x(texture.size.y*scaleY)
    this->vertices[0].position = sf::Vector2f(0, 0);
    this->vertices[1].position = sf::Vector2f(textSizeX, 0);
    this->vertices[2].position = sf::Vector2f(textSizeX, textSizeY);
    this->vertices[3].position = sf::Vector2f(0, textSizeY);

    this->sf::Transformable::setPosition(position);
    this->sf::Transformable::setScale(scale);

    // define its texture area to be a (texture.size.x)x(texture.size.y) rectangle starting at (0, 0)
    this->vertices[0].texCoords = sf::Vector2f(0, 0);
    this->vertices[1].texCoords = sf::Vector2f(textSizeX, 0);
    this->vertices[2].texCoords = sf::Vector2f(textSizeX, textSizeY);
    this->vertices[3].texCoords = sf::Vector2f(0, textSizeY);

    this->velocity = sf::Vector2f(100.f, 100.f);
}

Entity::Entity(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale, unsigned int width, unsigned int height)
{
    this->texture = texture;

    this->vertices = sf::VertexArray(sf::Quads, 4);

    float textSizeX = static_cast<float>(this->texture->getSize().x) / width;
    float textSizeY = static_cast<float>(this->texture->getSize().y) / height;

    // Defines it as a rectangle, located at (0, 0) and with size (texture.size.x*scaleX)x(texture.size.y*scaleY)
    this->vertices[0].position = sf::Vector2f(0, 0);
    this->vertices[1].position = sf::Vector2f(textSizeX, 0);
    this->vertices[2].position = sf::Vector2f(textSizeX, textSizeY);
    this->vertices[3].position = sf::Vector2f(0, textSizeY);

    this->sf::Transformable::setPosition(position);
    this->sf::Transformable::setScale(scale);

    // define its texture area to be a (texture.size.x)x(texture.size.y) rectangle starting at (0, 0)
    this->vertices[0].texCoords = sf::Vector2f(0, 0);
    this->vertices[1].texCoords = sf::Vector2f(textSizeX, 0);
    this->vertices[2].texCoords = sf::Vector2f(textSizeX, textSizeY);
    this->vertices[3].texCoords = sf::Vector2f(0, textSizeY);

    this->velocity = sf::Vector2f(100.f, 100.f);
}

Entity::~Entity()
{
}

const bool& Entity::getDeleted() const
{
    return deleted;
}

const sf::Vector2f& Entity::getVelocity() const
{
    return this->velocity;
}

const sf::Vector2f& Entity::getDirection() const
{
    return this->direction;
}

sf::FloatRect Entity::getGlobalBounds()
{
    return sf::FloatRect(this->getPosition().x, this->getPosition().y, this->vertices[2].position.x - this->vertices[0].position.x, this->vertices[2].position.y - this->vertices[0].position.y);
}

sf::IntRect Entity::getTextureRect()
{
    return sf::IntRect(this->getGlobalBounds());
}
