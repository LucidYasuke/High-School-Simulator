#ifndef HUD_H
#define HUD_H
#include "../Entity/ENTITYCOMPONENTS.h"
#include "../Physics.h"

class HUD
{
private:
    sf::VertexArray vertices;
    sf::View view;
    sf::RenderWindow* window;
    
    sf::Text textNames[5];
    sf::Text textStats[5];
public: 
    HUD();
    HUD(sf::RenderWindow* window, sf::Font& fontConnectionII);
    virtual ~HUD();
   
    void update(const float& dt, std::string stats[5]);
    void render(sf::RenderTarget* target);
};

#endif // !HUD_H

