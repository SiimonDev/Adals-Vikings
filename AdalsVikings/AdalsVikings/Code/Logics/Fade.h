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
	void setWaitDuration(sf::Time duration);
	void setFadeDuration(sf::Time duration);
	void setAlpha(float alpha);
	void wait(sf::Time frameTime);

	bool &getFaded();
	bool &getWait();
	bool &getFinishedWaiting();

private:
	Fade();
	Fade(const Fade&);
	void operator=(const Fade&);
	sf::RectangleShape mFadeRectangle;
	sf::Time mDuration, mElapsedTime, mWaitDuration;
	float mAlpha;
	bool mFaded, mWaiting, mFinishedWaiting;
};

