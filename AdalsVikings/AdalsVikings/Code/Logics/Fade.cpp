#include "Fade.h"
#include <iostream>
#include <memory>

Fade::Fade()
: mDuration(sf::seconds(1))
, mWaitDuration(sf::seconds(2))
, mElapsedTime(sf::Time::Zero)
, mFaded(false)
, mWaiting(false)
, mFinishedWaiting(false)
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
	iRenderer.addShape(mFadeRectangle, 9999999);
}

void Fade::fadeIn(sf::Time frameTime)
{

	if (mAlpha >= 255)
	{
		mElapsedTime = mDuration;
		mFaded = false;
	}
	if (mAlpha > 0)
	{
		mElapsedTime -= frameTime;
		mAlpha = 255 * (mElapsedTime.asSeconds() / mDuration.asSeconds());
	}
	if (mAlpha <= 0 && !mFaded)
	{
		mAlpha = 0;
		mElapsedTime = sf::Time::Zero;
	}
}

void Fade::fadeOut(sf::Time frameTime)
{
	if (mAlpha <= 0)
	{
		mElapsedTime = sf::Time::Zero;
		mFaded = false;
	}
	if (mAlpha < 255)
	{
		mElapsedTime += frameTime;
		mAlpha = 255 * (mElapsedTime.asSeconds() / mDuration.asSeconds());
	}
	if (mAlpha >= 255 && !mFaded)
	{
		mAlpha = 255;
		mElapsedTime = sf::Time::Zero;
	}
}

void Fade::setFadeDuration(sf::Time duration)
{
	mDuration = duration;
}
void Fade::setWaitDuration(sf::Time duration)
{
	mWaitDuration = duration;

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
bool &Fade::getWait()
{

	return mWaiting;

}
bool & Fade::getFinishedWaiting()
{
	return mFinishedWaiting;
}
void Fade::setAlpha(float alpha)
{
	mAlpha = alpha;
}

void Fade::wait(sf::Time frameTime)
{
	if (!mWaiting)
	{
		mElapsedTime = mWaitDuration;
		mWaiting = true;
		mFinishedWaiting = false;
	}

	if (mElapsedTime.asSeconds() > 0)
		mElapsedTime -= frameTime;
	if (mElapsedTime.asSeconds() <= 0)
	{
		mElapsedTime = sf::Time::Zero;
		mFinishedWaiting = true;
		mWaiting = false;
	}
}
