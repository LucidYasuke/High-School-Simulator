#ifndef ITEM_H
#define ITEM_H


#include "../Includes.h"
#include "../Physics.h"


class Item : public sf::Drawable, public sf::Transformable
{
protected:
    bool deleted;

    //===Graphics===//
    sf::Texture* texture;
    sf::VertexArray vertices;
    //---Graphics---//

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    Item();
    Item(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale);
    virtual ~Item();

    const bool& getDeleted() const;
    sf::FloatRect getGlobalBounds();

    //===Update===//
    void update(const float& dt);
    //---Update---//
};


#endif
