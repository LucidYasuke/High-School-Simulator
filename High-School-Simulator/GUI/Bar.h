#ifndef BAR_H
#define BAR_H


#include "BarComponents.h"


class Bar : sf::Sprite
{
private:
	//===COMPONENTS===//
	Component::Bar::Progress* progressComponent;
	//---COMPONENTS---//
public:
	Bar();
	Bar(const sf::Texture& texture);
	Bar(const sf::Texture& texture, const sf::IntRect& rectangle);
	virtual ~Bar();


	void add(Component::Bar::Progress* progressComponent);


	Component::Bar::Progress*& getProgressComponent();
};


#endif
