#ifndef HUD_H
#define HUD_H


#include "../Physics.h"


class PlayerFace : public sf::Drawable, public sf::Transformable
{
private:
    sf::VertexArray vertices;
    sf::Texture* texture;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    PlayerFace();
    PlayerFace(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale);
};


class HUD
{
private:
    sf::VertexArray vertices;
    sf::View view;
    sf::RenderWindow* window;
    sf::Texture* texturePlayer;

    PlayerFace playerFace;

    sf::Text textNames[6];
    sf::Text textStats[6];
public: 
    HUD();
    HUD(sf::RenderWindow* window, sf::Font& fontConnectionII);
    virtual ~HUD();
   
    void update(const float& dt, std::string stats[5]);
    void render(sf::RenderTarget* target);
};


#endif // !HUD_H
