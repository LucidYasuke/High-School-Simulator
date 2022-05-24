#ifndef MENU
#define MENU


#include "../Physics.h"


enum class MenuState{MAIN=0};


class Menu
{
private:
    MenuState state;

    sf::Font* font;

    sf::FloatRect bounds;

    sf::VertexArray background;
    sf::VertexArray border;
    sf::VertexArray mainDividers;
    sf::RectangleShape mainSelectors[5];

    sf::View view;
    sf::RenderWindow* window;

    void initGlobalVariable();
    void initMainMenuVariables();
public:
    Menu();
    Menu(sf::RenderWindow* window, sf::Font* fontConnectionII);
    virtual ~Menu();

    void updateMainMenu(const float& dt, sf::Vector2f& mosPosView);
    void update(const float& dt, sf::Vector2i*& mosPosWindow);

    void renderMainMenu(sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
};


#endif

