#ifndef GUI_H
#define GUI_H

#include "../Includes.h"

enum class Align{LEFT=0, CENTER, RIGHT};

class GUI
{
protected:
	float x, y, w, l;
public:
	GUI(Align pos, float x, float y, float w, float l);
	virtual ~GUI();

	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target) = 0;
};

#endif

