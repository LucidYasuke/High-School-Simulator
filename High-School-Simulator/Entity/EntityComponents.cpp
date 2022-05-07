#include "EntityComponents.h"

void Wallet::addMoney(double amount)
{
	this->amount += amount;
}

void Wallet::subMoney(double amount)
{
	this->amount -= amount;
}
