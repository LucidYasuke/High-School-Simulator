#ifndef ITEM_H
#define ITEM_H


#include "../Includes.h"
#include "../Physics.h"

enum ItemTypes{IT_DEFAULT = 0,MOVABLE};

class Item : public sf::Drawable, public sf::Transformable
{
private:
    void initVariables();
protected:
    bool deleted;

    //===Graphics===//
    sf::Texture* texture;
    sf::VertexArray vertices;
    //---Graphics---//

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    //INVENTORY RELATED 
    short unsigned type;
    unsigned value;

    //EL FIN DE ESO

public:
    Item();
    Item(unsigned value);
    Item(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale);
    virtual ~Item();

    virtual Item* clone() = 0;
    const bool& getDeleted() const;
    sf::FloatRect getGlobalBounds();

    //===Update===//
    void update(const float& dt);
    //---Update---//
};


#endif
