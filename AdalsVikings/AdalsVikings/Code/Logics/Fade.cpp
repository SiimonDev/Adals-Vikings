#include "Fade.h"
#include <iostream>

Fade::Fade()
: mDuration(sf::Time::Zero)
, mElapsedTime(sf::Time::Zero)
, mFaded(false)
{
	mFadeRectangle.setSize(sf::Vector2f(1920, 1080));
	mAlpha = 0;
}

Fade &Fade::getInstance()
{
	static Fade* instance;

	if (instance == NULL)
		instance = new Fade();

	return *instance;
}
void Fade::initialize()
{
	mFadeRectangle.setSize(sf::Vector2f(1920, 1080));
	mAlpha = 0;
}

void Fade::update(sf::Time &frameTime)
{

}

void Fade::render(IndexRenderer &iRenderer)
{
	mFadeRectangle.setFillColor(sf::Color(0, 0, 0, mAlpha));
	iRenderer.addRectangle(mFadeRectangle, 9999999);
}

void Fade::fadeIn(sf::Time frameTime)
{
	sf::Time timePerFrame = mDuration / float(255);
	mElapsedTime += frameTime;
	if (mElapsedTime >= timePerFrame && mAlpha >= 0)
	{
		mAlpha -= mElapsedTime.asSeconds();
		mElapsedTime -= timePerFrame;
	}
}

void Fade::fadeOut(sf::Time frameTime)
{
	sf::Time timePerFrame = mDuration / float(255);
	mElapsedTime += frameTime;
	if (mElapsedTime >= timePerFrame && mAlpha <= 255)
	{
		mAlpha += mElapsedTime.asSeconds();
		mElapsedTime -= timePerFrame;
	}
}

void Fade::setFadeDuration(sf::Time duration)
{
	mDuration = duration;
}

bool & Fade::getFaded()
{
	if (mAlpha <= 0 || mAlpha >= 255)
	{
		mFaded = true;
	}
	else
	{
		mFaded = false;
	}
	return mFaded;
}

void Fade::setAlpha(float alpha)
{
	mAlpha = alpha;
}
