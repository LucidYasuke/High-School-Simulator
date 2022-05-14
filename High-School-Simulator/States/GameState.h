#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "PauseState.h"
#include "../Entity/Player.h"
#include "../TileSets/TileMap.h"

enum class Day {SUNDAY=0, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY};

class Date 
{
private:
	Day day;
	int hour;
	sf::Time minute;
public:
	Date();
	virtual ~Date();

	void update(const float& dt);
	
	const Day& getDay() const;
	const int& getHour() const;
	const int getMinute() const;
	const float getTrueMinute() const;

	const std::string getDayAsString() const;
	const std::string getHourAsString() const;
	const std::string getMinuteAsString() const;

	void setDay(Day& day);
	void setHour(int& hour);
	void setMinute(int& minute);
	void setTrueMinute(float& minute);
};

class GameState : public State
{
private:
	Date date;

	TileMap map;

	//===Textures===//
	sf::Texture* texturePlayer;
	//---Textures---//

	//===GUI===//
	//===GUI===//

	//===Views===//
	sf::View viewWorld;
	//---Views---//

	//===Booleans===//
	bool pause, gameOver;

	std::map<std::string, bool*> booleansPause;
	std::map<std::string, bool*> booleansPlayer;
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
	void initViews();
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
	void updateDate(const float& dt);
	void update(const float& dt) override;

	void renderViewWorld(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = NULL) override;
};

#endif