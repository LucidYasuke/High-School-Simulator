#ifndef HUD_H
#define HUD_H

#include "../Physics.h"

class HUD
{
private:
    sf::VertexArray vertices;
    sf::View view;
    sf::RenderWindow* window;

    sf::Vertex vertex;



public:
    HUD();
    HUD(sf::RenderWindow* window);
    virtual ~HUD();

    void update(const float& dt);
    void render(sf::RenderTarget* target);
};

#endif // !HUD_H

