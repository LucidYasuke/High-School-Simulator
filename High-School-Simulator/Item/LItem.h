#ifndef LITEM_H
#define LTIME_H


#include "../Buttons/Button.h"


namespace ItemComponent
{
	struct WorldCollision
	{
		Button* button;
		sf::FloatRect radius;
	};
}


class LItem : public sf::Sprite
{

};


#endif // !LITEM_H


