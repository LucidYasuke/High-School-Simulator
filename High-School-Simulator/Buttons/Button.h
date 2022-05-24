#ifndef BUTTON_H
#define BUTTON_H


#include "../Physics.h"


struct ButtonMovementComponent
{
    sf::Vector2f originalPosition;
    sf::Vector2f change;
    sf::Vector2f modifiedPosition;
};

struct ButtonAnimationComponent
{
    float cdAnimationIntervalMax;
    sf::Time cdAnimationInterval;
    std::vector<sf::Vector2f> idleTexturePositions;
    std::vector<sf::Vector2f> hoverTexturePositions;
    std::vector<sf::Vector2f> activeTexturePositions;
};


enum class buttonStates { BTNIDLE = 0, BTNHOVER, BTNPRESSED };

class Button : public sf::Drawable, public sf::Transformable
{
protected:
    bool active;

    bool boolean;    
    bool* condition;	

    buttonStates buttonState;

    //===COMPONENTS===//
    ButtonMovementComponent* movementComponent;
    ButtonAnimationComponent* animationComponent;
    //---COMPONENTS---//

    sf::Vector2f viewScale;
    
    //===Time===//
    sf::Time lastClicked;
    static const sf::Time lastClickedMax;
    //---Time---//

    //===Graphics===//
    sf::Texture* texture;
    sf::VertexArray vertices;
    //---Graphics---//

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    Button();
    Button(sf::Vector2f position, sf::Vector2f scale, bool* condition, bool boolean);
    Button(sf::Vector2f position, sf::Vector2f size, sf::Vector2f scale, bool* condition, bool boolean);
    Button(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale, bool* condition, bool boolean);
    Button(sf::Texture* texture, sf::Vector2f position, sf::Vector2f size, sf::Vector2f scale, bool* condition, bool boolean);
    virtual ~Button();

    sf::FloatRect getGlobalBounds();

    void add(ButtonMovementComponent* movementComponent);
    void add(ButtonAnimationComponent* animationComponent);

    ButtonMovementComponent*& getMovementComponent();
    ButtonAnimationComponent*& getAnimationComponent();

    void setPosition(sf::Vector2f position);
    void setBool(bool* condition, bool boolean);
    void reset();

    //===Update===//
    void updateTimers(const float& dt);
    void update(const float& dt, const sf::Vector2f mosPos);
    //---Update---//
};


#endif
