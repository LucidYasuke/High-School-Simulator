#ifndef ENTITY_H
#define ENTITY_H


#include "../Includes.h"
#include "../Physics.h"


class Entity : public sf::Drawable, public sf::Transformable
{
protected:
    bool deleted;

    //===Movement===//
    sf::Vector2f velocity;
    sf::Vector2f direction;
    Direction facing;
    //---Movement---//

    //===Graphics===//
    sf::Time lastAnimationShift;
    static const float lastAnimationShiftMax;
    sf::Texture* texture;
    sf::VertexArray vertices;
    //---Graphics---//

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    Entity();
    Entity(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale);
    Entity(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale, unsigned int width, unsigned int height);
    virtual ~Entity();

    const bool& getDeleted() const;
    const sf::Vector2f& getVelocity() const;
    const sf::Vector2f& getDirection() const;
    sf::FloatRect getGlobalBounds();

    //===Update===//
    virtual void updateMovement(const float& dt) = 0;
    virtual void updateCollision(const sf::FloatRect& bounds) = 0;
    virtual void updateTexture(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    //---Update---//
};

#endif
