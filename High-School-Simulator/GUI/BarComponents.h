#ifndef BARCOMPONENTS_H
#define BARCOMPONENTS_H


#include "../Physics.h"


namespace Components { namespace Bar {

	struct Progress
	{
		sf::RectangleShape base;
		sf::RectangleShape layer;

		void update(double ratio);
		void render(sf::RenderTarget* target);
	};
}}


#endif
