#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "PauseState.h"
#include "../Entity/Player.h"
#include "../TileSets/TileMap.h"


class GameState : public State
{
private:
	TileMap map;

	//===Textures===//
	sf::Texture* texturePlayer;
	//---Textures---//

	//===GUI===//
	//===GUI===//

	//===Booleans===//
	bool pause, gameOver;

	std::map<std::string, bool*> booleansPause;
	//---Booleans---//

	//===Entities===//
	Player* player;
	//---Entities---//

	//===Timers===//
	sf::Time cooldownPauseCreation, cooldownPauseCreationMax; // Pause State Creation Timer
	//---Timers---//

	std::stack<State*> stateStack;

	void initTextures() override;
	void initBackground();
	void initButtons() override;
public:
	//===CONSTRUCTORS||DESTRUCTORS===//
	GameState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed, std::map<std::string, bool*> booleans);
	virtual ~GameState();

	void endState() override;
	void confirmQuit() override;
	void resetButton() override;

	void updateLevel();
	void updateTimers(const float& dt);
	void updateInput() override;
	void update(const float& dt) override;

	void render(sf::RenderTarget* target = NULL) override;
};

#endif