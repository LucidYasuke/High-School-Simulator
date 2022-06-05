#ifndef BARCOMPONENTS_H
#define BARCOMPONENTS_H


#include "../Physics.h"
#include "Shapes.h"


namespace Component { namespace Bar {

	struct Progress
	{
		CapsuleShape base;
		CapsuleShape layer;
		CapsuleShape border;
		

		void update(double ratio);
		void render(sf::RenderTarget* target);
	};
}}


#endif
