#include "GUI.h"


GUI::GUI(Align pos, float x, float y, float w, float l)
{
	this->w = w;
	this->l = l;

	switch (pos)
	{
	case Align::LEFT:
		this->x = x;
		this->y = y;
		break;
	case Align::CENTER:
		this->x = x - w/2.f;
		this->y = y - l/2.f;
		break;
	case Align::RIGHT:
		this->x = x - w;
		this->y = y - l;
		break;
	}
}


GUI::~GUI()
{

}
