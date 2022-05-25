#include "Button.h"


const float Button::lastClickedMax = 0.25f;

Button::Button(const sf::Vector2f& size) : RectangleShape (size)
{
    this->movementComponent = 0;
    this->animationComponent = 0;
    this->colorComponent = 0;
    this->booleanPointer = 0;
}

Button::~Button()
{
}

void Button::setPosition(sf::Vector2f position)
{
    this->sf::Transformable::setPosition(position);

    if (this->movementComponent)
    {
        this->movementComponent->originalPosition = position;
        this->movementComponent->modifiedPosition.x = position.x + this->movementComponent->change.x;
        this->movementComponent->modifiedPosition.y = position.y + this->movementComponent->change.y;
    }
}

void Button::setScale(sf::Vector2f scale)
{
    this->sf::Transformable::setScale(scale);
    if (this->movementComponent)
    {
        this->movementComponent->originalScale = this->getScale();
        this->movementComponent->modifiedScale = sf::Vector2f(percentRange(this->getScale().x, .05f), percentRange(this->getScale().y, .05f));
    }
}

void Button::setBoolean(bool* booleanPointer, bool boolean)
{
    this->booleanPointer = booleanPointer;
    this->boolean = boolean;
}

void Button::add(ButtonComponent::Movement* movementComponent)
{
    this->movementComponent = movementComponent;
    this->movementComponent->originalScale = this->getScale();
    this->movementComponent->modifiedScale = sf::Vector2f(percentRange(this->getScale().x, .05f), percentRange(this->getScale().y, .05f));
}

void Button::add(ButtonComponent::Animation* animationComponent)
{
    this->animationComponent = animationComponent;
}

void Button::add(ButtonComponent::Color* colorComponent)
{
    this->colorComponent = colorComponent;
}

ButtonComponent::Movement*& Button::getMovementComponent()
{
    return this->movementComponent;
}

ButtonComponent::Animation*& Button::getAnimationComponent()
{
    return this->animationComponent;
}

ButtonComponent::Color*& Button::getColorComponent()
{
    return this->colorComponent;
}

void Button::reset()
{
    this->lastClicked = sf::seconds(0.f);
}

void Button::updateTimers(const float& dt)
{
    this->lastClicked += sf::seconds(dt);
}

void Button::update(const float& dt, const sf::Vector2f mosPos)
{
    this->updateTimers(dt);

    if (this->getGlobalBounds().contains(mosPos))
    {
        if (this->colorComponent)
        {
            this->setFillColor(this->colorComponent->hoverColor);
        }
        this->buttonState = ButtonStates::BTNHOVER;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (this->lastClicked.asSeconds() >= this->lastClickedMax)
            {
                if (this->colorComponent)
                {
                    this->setFillColor(this->colorComponent->activeColor);
                }
                this->buttonState = ButtonStates::BTNPRESSED;
                this->lastClicked = sf::seconds(0.f); // RESET
            }
        }
    }
    else
    {
        if (this->colorComponent)
        {
            this->setFillColor(this->colorComponent->idleColor);
        }
        this->buttonState = ButtonStates::BTNIDLE;
    }

    switch (this->buttonState)
    {
    case ButtonStates::BTNIDLE:
        if (this->active)
        {
            if (this->movementComponent)
            {
                this->sf::Transformable::setScale(this->movementComponent->originalScale);
                this->sf::Transformable::setPosition(this->movementComponent->originalPosition);
            }
            this->active = false;
        }
        break;
    case ButtonStates::BTNHOVER:
        if (!this->active)
        {
            if (this->movementComponent)
            {
                this->sf::Transformable::setScale(this->movementComponent->modifiedScale);
                this->sf::Transformable::setPosition(this->movementComponent->modifiedPosition);
            }
            this->active = true;
        }
        break;
    case ButtonStates::BTNPRESSED:
        if (this->booleanPointer)
            *this->booleanPointer = this->boolean;

        if (this->active)
        {
            if (this->movementComponent)
            {
                this->sf::Transformable::setScale(this->movementComponent->originalScale);
                this->sf::Transformable::setPosition(this->movementComponent->originalPosition);
            }
            this->active = false;
        }
        this->buttonState = ButtonStates::BTNIDLE;
        break;
    }
}
