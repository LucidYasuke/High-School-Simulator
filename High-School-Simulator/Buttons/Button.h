#ifndef LBUTTON_H
#define LBUTTON_H

#include "../Physics.h"

enum class buttonStates { BTNIDLE = 0, BTNHOVER, BTNPRESSED };

class Button : public sf::Drawable, public sf::Transformable
{
protected:
    bool active;

    bool boolean;    
    bool* condition;	

    buttonStates buttonState;

    sf::Vector2f originalScale;
    
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
    Button(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale, bool* condition, bool boolean);
    virtual ~Button();

    sf::FloatRect getGlobalBounds();

    void onClick();
    void setActive();
    void setUnactive();
    void setBool(bool* condition, bool boolean);
    void reset();

    //===Update===//
    void updateTimers(const float& dt);
    void update(const float& dt, const sf::Vector2f mosPos);
    //---Update---//
};

#endif
