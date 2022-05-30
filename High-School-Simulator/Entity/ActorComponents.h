#ifndef ACTORCOMPONENTS_H
#define ACTORCOMPONENTS_H


#include "../Physics.h"


namespace ActorComponents
{
	enum class Demographic { LOWER = 0, MIDDLE, UPPER };


	enum class MindState { HAPPY = 0, SAD, TIRED, DELERIOUS, BORED, INTOXICATED };


	struct Movement
	{
		bool isSprinting;
		sf::Vector2f velocity;
		sf::Vector2f direction;
	};


	struct Bank
	{
	private:
		double amount;
	public:
		void add(double amount);
		void allowance(Demographic demographic = Demographic::MIDDLE); 

		double getMoney();
		std::string getMoneyAsString();
	};
}


#endif
