#ifndef TITLESTATE_H
#define TITLESTATE_H


#include "State.h"
#include "../Buttons/Button.h"


class TitleState : public State
{
private:
	sf::Text textTitle[2];
	sf::Text textTitleTop, textTitleBot;

	std::map<std::string, sf::Texture*> textureButton;
	sf::Texture* textureBackground;

	void initTextures() override;
	void initTitle();
	void initButtons() override;
public:
	//===CONSTRUCTORS||DESTRUCTORS===//
	TitleState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed, std::map<std::string, bool*> booleans);
	virtual ~TitleState();

	void endState() override;
	void confirmQuit() override;
	void resetButton() override;
	void updateInput() override;
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = NULL) override;
};


#endif
