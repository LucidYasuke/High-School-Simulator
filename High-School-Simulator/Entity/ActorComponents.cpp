#include "ActorComponents.h"

void ActorComponents::Bank::add(double amount)
{
	this->amount += amount;
}

void ActorComponents::Bank::allowance(Demographic demographic)
{
	switch (demographic)
	{
	case Demographic::LOWER:
		this->amount += static_cast<double>(rand() % 8); // Random from 0 to 7
		break;
	case Demographic::MIDDLE:
		this->amount += static_cast<double>(rand() % 16) + 10; // Random from 10 to 25
		break;
	case Demographic::UPPER:
		this->amount += static_cast<double>(rand() % 21) + 30; // Random from 30 to 50
		break;
	default:
		break;
	}
}

double ActorComponents::Bank::getMoney()
{
	return roundTo<double>(this->amount, 2);
}

std::string ActorComponents::Bank::getMoneyAsString()
{
	return std::to_string(this->getMoney());
}
