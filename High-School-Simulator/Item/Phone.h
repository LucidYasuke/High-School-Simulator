#ifndef PHONE_H
#define PHONE_H

#include "MOVABLE.h"

class MOVABLE;

class Phone//:
	//public MOVABLE
{
private:
public:
	Phone();
	virtual ~Phone();

	virtual Phone* clone();

	virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center);
	virtual void render(sf::RenderTarget& target);
};

#endif

