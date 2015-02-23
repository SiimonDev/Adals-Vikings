#pragma once
#include "IndexRenderer.h"

#define FadeI Fade::getInstance()
class Fade
{
public:

	static Fade &getInstance();
	void initialize();

	void update(sf::Time &frameTime);
	void render(IndexRenderer &iRenderer);

	void fadeIn(sf::Time frameTime);
	void fadeOut(sf::Time frameTime);
	void setFadeDuration(sf::Time duration);
	void setAlpha(float alpha);

	bool &getFaded();

private:
	Fade();
	Fade(const Fade&);
	void operator=(const Fade&);
	sf::RectangleShape mFadeRectangle;
	sf::Time mDuration, mElapsedTime;
	float mAlpha;
	bool mFaded;
};

