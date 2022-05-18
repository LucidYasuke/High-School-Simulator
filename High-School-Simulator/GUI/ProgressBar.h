#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H


#include "GUI.h"


class ProgressBar : public GUI
{
protected:
	sf::Time* currentTime;
	sf::Time* maxTime;

	float ratio;
	sf::RectangleShape back, front;
public:
	ProgressBar(Align pos, float x, float y, float w, float l, sf::Time* currentTime, sf::Time* maxTime);
	virtual ~ProgressBar();

	void update() override;
	void render(sf::RenderTarget* target) override;
};


#endif
