#include "Button.h"


const sf::Time Button::lastClickedMax = sf::seconds(0.25f);

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= this->getTransform(); // getTransform() is defined by sf::Transformable

    // apply the texture
    states.texture = this->texture;

    // you may also override states.shader or states.blendMode if you want

    // draw the vertex array
    target.draw(this->vertices, states);
}

Button::Button()
{
    this->buttonState = buttonStates::BTNIDLE;

    this->vertices = sf::VertexArray(sf::Quads, 4);

    // Defines it as a rectangle, located at (0, 0) and with size 4x4
    this->vertices[0].position = sf::Vector2f(0, 0);
    this->vertices[1].position = sf::Vector2f(64, 0);
    this->vertices[2].position = sf::Vector2f(64, 64);
    this->vertices[3].position = sf::Vector2f(0, 64);

    // Default color white
    this->vertices[0].color = sf::Color::White;
    this->vertices[1].color = sf::Color::White;
    this->vertices[2].color = sf::Color::White;
    this->vertices[3].color = sf::Color::White;

    sf::Vector2f scale(1.f, 1.f);
    sf::Vector2f position(0.f, 0.f);

    this->originalScale = scale;
    this->modifiedScale.x = scale.x + .05f * scale.x;
    this->modifiedScale.y = scale.y + .05f * scale.y;

    this->originalPosition = position;
    this->modifiedPosition.x = position.x - 7.5f * scale.x;
    this->modifiedPosition.y = position.y - 7.5f * scale.y;
}

Button::Button(sf::Vector2f position, sf::Vector2f scale, bool* condition, bool boolean)
{
    this->condition = condition;
    this->boolean = boolean;
    this->buttonState = buttonStates::BTNIDLE;

    this->vertices = sf::VertexArray(sf::Quads, 4);

    // Defines it as a rectangle, located at (0, 0) and with size (texture.size.x*scaleX)x(texture.size.y*scaleY)
    this->vertices[0].position = sf::Vector2f(0, 0);
    this->vertices[1].position = sf::Vector2f(256 * scale.x, 0);
    this->vertices[2].position = sf::Vector2f(256 * scale.x, 64 * scale.y);
    this->vertices[3].position = sf::Vector2f(0, 64 * scale.y);

    this->sf::Transformable::setPosition(position);

    this->originalScale = this->getScale();
    this->modifiedScale.x = percentRange(this->getScale().x, .05f);
    this->modifiedScale.y = percentRange(this->getScale().y, .05f);

    this->originalPosition = position;
    this->modifiedPosition.x = position.x - 7.5f * scale.x;
    this->modifiedPosition.y = position.y - 7.5f * scale.y;

    this->viewScale = scale;
}

Button::Button(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale, bool* condition, bool boolean)
{
    this->condition = condition;
    this->boolean = boolean;
    this->buttonState = buttonStates::BTNIDLE;

    this->texture = texture;

    this->vertices = sf::VertexArray(sf::Quads, 4);

    this->originalScale = scale;

    float textSizeX = static_cast<float>(this->texture->getSize().x);
    float textSizeY = static_cast<float>(this->texture->getSize().y);

    // Defines it as a rectangle, located at (0, 0) and with size (texture.size.x*scaleX)x(texture.size.y*scaleY)
    this->vertices[0].position = sf::Vector2f(0, 0);
    this->vertices[1].position = sf::Vector2f(textSizeX * scale.x, 0);
    this->vertices[2].position = sf::Vector2f(textSizeX * scale.x, textSizeY * scale.y);
    this->vertices[3].position = sf::Vector2f(0, textSizeY * scale.y);

    sf::Vector2f modPos;
    modPos.x = 1280.f * scale.x / 2.f - textSizeX * scale.x / 2.f + position.x * scale.x;
    modPos.y = 720.f * scale.y / 2.f - textSizeY * scale.y / 2.f + position.y * scale.y;

    this->sf::Transformable::setPosition(modPos);

    // define its texture area to be a (texture.size.x)x(texture.size.y) rectangle starting at (0, 0)
    this->vertices[0].texCoords = sf::Vector2f(0, 0);
    this->vertices[1].texCoords = sf::Vector2f(textSizeX, 0);
    this->vertices[2].texCoords = sf::Vector2f(textSizeX, textSizeY);
    this->vertices[3].texCoords = sf::Vector2f(0, textSizeY);

    this->originalScale = this->getScale();
    this->modifiedScale.x = percentRange(this->getScale().x, .05f);
    this->modifiedScale.y = percentRange(this->getScale().y, .05f);

    this->originalPosition = modPos;
    this->modifiedPosition.x = modPos.x - 7.5f * scale.x;
    this->modifiedPosition.y = modPos.y - 7.5f * scale.y;

    this->viewScale = scale;
}

Button::~Button()
{
}

sf::FloatRect Button::getGlobalBounds()
{
    return sf::FloatRect(this->getPosition().x, this->getPosition().y, this->vertices[2].position.x - this->vertices[0].position.x, this->vertices[2].position.y - this->vertices[0].position.y);
}

void Button::setPosition(sf::Vector2f position)
{
    this->sf::Transformable::setPosition(position);

    this->originalPosition = position;
    this->modifiedPosition.x = position.x - 7.5f * this->viewScale.x;
    this->modifiedPosition.y = position.y - 7.5f * this->viewScale.y;
}

void Button::setBool(bool* condition, bool boolean)
{
    this->condition = condition;
    this->boolean = boolean;
}

void Button::reset()
{
    this->lastClicked = sf::seconds(0.f);
}

void Button::updateTimers(const float& dt)
{
    this->lastClicked += sf::seconds(dt);

    if (this->lastClicked >= this->lastClickedMax * 3.f) { this->lastClicked = this->lastClickedMax; } // Just so it doesn't hold up too much space
}

void Button::update(const float& dt, const sf::Vector2f mosPos)
{
    this->updateTimers(dt);

    if (this->getGlobalBounds().contains(mosPos))
    {
        this->buttonState = buttonStates::BTNHOVER;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (this->lastClicked >= this->lastClickedMax)
            {
                this->buttonState = buttonStates::BTNPRESSED;
                this->lastClicked = sf::seconds(0.f); // RESET
            }
        }
    }
    else
    {
        this->buttonState = buttonStates::BTNIDLE;
    }

    switch (this->buttonState)
    {
    case buttonStates::BTNIDLE:
        if (this->active)
        {
            this->setScale(this->originalScale);
            this->sf::Transformable::setPosition(this->originalPosition);
            this->active = false;
        }
        break;
    case buttonStates::BTNHOVER:
        if (!this->active) 
        { 
            this->setScale(this->modifiedScale);
            this->sf::Transformable::setPosition(this->modifiedPosition);
            this->active = true;
        }
        break;
    case buttonStates::BTNPRESSED:
        *this->condition = this->boolean;
        if (this->active)
        {
            this->setScale(this->originalScale);
            this->sf::Transformable::setPosition(this->originalPosition);
            this->active = false;
        }
        this->buttonState = buttonStates::BTNIDLE;
        break;
    }
}
