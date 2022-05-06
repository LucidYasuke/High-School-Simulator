#ifndef PHYSICS_H
#define PHYSICS_H

#include "Includes.h"
#include <limits>

template <typename T>
T round(const T& number, int place);

float pythag(const sf::Vector2f& vector);

float percentRange(float number, float percent, unsigned loop = 1);
double percentRange(double number, double percent, unsigned loop = 1);

sf::Vector2f normalize(sf::Vector2f vector);

#endif