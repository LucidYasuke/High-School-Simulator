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

    sf::Vertex vertex;

    Toxicology Toxicology;
    Psychology Psychology;
    Wallet Wallet;
public:
    HUD();
    HUD(int Toxicology,int Psychology,int Wallet);
    HUD(sf::RenderWindow* window);
    virtual ~HUD();

    void update(const float& dt);
    void render(sf::RenderTarget* target);
};

#endif // !HUD_H

