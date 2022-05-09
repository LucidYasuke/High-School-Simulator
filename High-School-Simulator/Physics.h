#ifndef PHYSICS_H
#define PHYSICS_H

#include "Includes.h"
#include <limits>

template <typename T>
const T roundTo(T& number, int place);

float pythag(const sf::Vector2f& vector);

float percentRange(float number, float percent, unsigned loop = 1);
double percentRange(double number, double percent, unsigned loop = 1);

sf::Vector2f normalize(sf::Vector2f vector);

template<typename T>
inline const T roundTo(T& number, int place)
{
	return static_cast<T>(std::round(number * std::pow(10, place)) / std::pow(10, place));
}

#endif