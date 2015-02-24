#include "Fade.h"
#include <iostream>
#include <memory>

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
	static std::unique_ptr<Fade> instance;

	if (instance == NULL)
		instance = std::unique_ptr<Fade>(new Fade());

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

	if (mAlpha >= 0)
	{
		std::cout << "FADING" << mAlpha << std::endl;
		mAlpha -= mDuration.asSeconds();
	}
}

void Fade::fadeOut(sf::Time frameTime)
{
	if (mAlpha <= 255)
	{
		std::cout << "FADING" << mAlpha << std::endl;
		mAlpha += mDuration.asSeconds();
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
