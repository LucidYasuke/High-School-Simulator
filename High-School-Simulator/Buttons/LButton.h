#ifndef LBUTTON_H
#define LBUTTON_H

#include "../Includes.h"
#include "../Physics.h"

enum class buttonStates { BTNIDLE = 0, BTNHOVER, BTNPRESSED };


class LButton : public sf::Drawable, public sf::Transformable
{
protected:
    bool boolean, active;
    
    bool* condition;	
    buttonStates buttonState;
    
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
    LButton();
    LButton(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale);
    virtual ~LButton();

    sf::FloatRect getGlobalBounds();

    //===Update===//
    virtual void update(const float& dt) = 0;
    //---Update---//
};

#endif
