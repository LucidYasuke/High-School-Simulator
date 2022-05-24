#ifndef LBUTTON_H
#define LBUTTON_H


#include "../Physics.h"


enum class ButtonStates { BTNIDLE = 0, BTNHOVER, BTNPRESSED };

namespace ButtonComponent
{
    struct Movement
    {
        sf::Vector2f originalPosition;
        sf::Vector2f change;
        sf::Vector2f modifiedPosition;
    };


    struct Animation
    {
        float cdAnimationIntervalMax;
        sf::Time cdAnimationInterval;
        std::vector<sf::Vector2f> idleTexturePositions;
        std::vector<sf::Vector2f> hoverTexturePositions;
        std::vector<sf::Vector2f> activeTexturePositions;
    };

    struct Color
    {
        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;
    };
}


class LButton : public sf::RectangleShape
{
protected:
    bool active;

    bool boolean;
    bool* booleanPointer;

    ButtonStates buttonState;

    //===COMPONENTS===//
    ButtonComponent::Movement* movementComponent;
    ButtonComponent::Animation* animationComponent;
    ButtonComponent::Color* colorComponent;
    //---COMPONENTS---//

    //===Time===//
    sf::Time lastClicked;
    static const float lastClickedMax;
    //---Time---//

    //===Graphics===//
    sf::Texture* texture;
    sf::VertexArray vertices;
    //---Graphics---//
public:
    LButton(const sf::Vector2f& size = sf::Vector2f(0, 0));
    virtual ~LButton();


    void setPosition(sf::Vector2f position);
    void setBoolean(bool* booleanPointer, bool boolean);


    void add(ButtonComponent::Movement* movementComponent);
    void add(ButtonComponent::Animation* animationComponent);
    void add(ButtonComponent::Color* colorComponent);

    ButtonComponent::Movement*& getMovementComponent();
    ButtonComponent::Animation*& getAnimationComponent();
    ButtonComponent::Color*& getColorComponent();


    //===Update===//
    void updateTimers(const float& dt);
    void update(const float& dt, const sf::Vector2f mosPos);
    //---Update---//
};

#endif // !LBUTTON_H



