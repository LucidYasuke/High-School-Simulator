#ifndef ENTITY_H
#define ENTITY_H

#include "../Includes.h"
#include "../Physics.h"

class Entity : public sf::Drawable, public sf::Transformable
{
protected:
    int level;
    bool deleted;

    //===Movement===//
    sf::Vector2f velocity;
    sf::Vector2f direction;
    //---Movement---//

    //===Graphics===//
    sf::Texture* texture;
    sf::VertexArray vertices;
    //---Graphics---//

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    Entity();
    Entity(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale);
    virtual ~Entity();

    const bool& getDeleted() const;
    const int& getLevel() const;
    const sf::Vector2f& getVelocity() const;
    const sf::Vector2f& getDirection() const;
    sf::FloatRect getGlobalBounds();

    //===Update===//
    virtual void updateMovement(const float& dt) = 0;
    virtual void updateCollision(const sf::FloatRect& bounds) = 0;
    virtual void update(const float& dt) = 0;
    //---Update---//
};

#endif
