#include "LButton.h"


const float LButton::lastClickedMax = 0.25f;

LButton::LButton(const sf::Vector2f& size) : RectangleShape (size)
{
    this->movementComponent = 0;
    this->animationComponent = 0;
    this->colorComponent = 0;
    this->booleanPointer = 0;
}

LButton::~LButton()
{
}

void LButton::setPosition(sf::Vector2f position)
{
    this->sf::Transformable::setPosition(position);

    if (this->movementComponent)
    {
        this->movementComponent->originalPosition = position;
        this->movementComponent->modifiedPosition.x = position.x + this->movementComponent->change.x;
        this->movementComponent->modifiedPosition.y = position.y + this->movementComponent->change.y;
    }
}

void LButton::setBoolean(bool* booleanPointer, bool boolean)
{
    this->booleanPointer = booleanPointer;
    this->boolean = boolean;
}

void LButton::add(ButtonComponent::Movement* movementComponent)
{
    this->movementComponent = movementComponent;
}

void LButton::add(ButtonComponent::Animation* animationComponent)
{
    this->animationComponent = animationComponent;
}

void LButton::add(ButtonComponent::Color* colorComponent)
{
    this->colorComponent = colorComponent;
}

ButtonComponent::Movement*& LButton::getMovementComponent()
{
    return this->movementComponent;
}

ButtonComponent::Animation*& LButton::getAnimationComponent()
{
    return this->animationComponent;
}

ButtonComponent::Color*& LButton::getColorComponent()
{
    return this->colorComponent;
}

void LButton::updateTimers(const float& dt)
{
    this->lastClicked += sf::seconds(dt);
}

void LButton::update(const float& dt, const sf::Vector2f mosPos)
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
                this->setScale(sf::Vector2f(1.f, 1.f));
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
                this->setScale(sf::Vector2f(1.05f, 1.05f));
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
                this->setScale(sf::Vector2f(1.f, 1.f));
                this->sf::Transformable::setPosition(this->movementComponent->originalPosition);
            }
            this->active = false;
        }
        this->buttonState = ButtonStates::BTNIDLE;
        break;
    }
}
