#include "ActionWheel.h"
#include <iostream>


ActionWheel::ActionWheel()
{
	button1Position = sf::Vector2f(0, -60);
	button2Position = sf::Vector2f(60, 60);
	button3Position = sf::Vector2f(-60, 60);

	mIndex = 9999999;
}

bool ActionWheel::isButtonSelected()
{
	if (mIsActive)
		return mButtonSelected;
	else
		return false;
}
bool ActionWheel::isTalkSelected()
{
	if (mIsActive)
		return mTalkSelected;
	else
		return false;
}
bool ActionWheel::isPickUpSelected()
{
	if (mIsActive)
		return mPickUpSelected;
	else
		return false;
}
bool ActionWheel::isLookSelected()
{
	if (mIsActive)
		return mLookSelected;
	else
		return false;
}
bool ActionWheel::isPressed()
{
	return mIsPressed;
}
bool ActionWheel::isActive()
{
	return mIsActive;
}
void ActionWheel::setActive(bool active)
{
	mIsActive = active;
}

sf::Vector2f ActionWheel::getPosition(){ return mPosition; }

void ActionWheel::load()
{
	RMI.loadResource(Font::Font1);
	RMI.loadResource(Texture::LookButton);
	RMI.loadResource(Texture::TakeButton);
	RMI.loadResource(Texture::TalkButton);

	button1 = Button(Texture::TalkButton, Font::Font1, sf::Vector2f(), " Talk");
	button1.setScale(sf::Vector2f(0.6f, 0.6f));
	button1.setOrigin(ButtonOrigin::Center);
	button1.setDescriptionStyle(sf::Text::Bold);
	button1.setIndex(mIndex);

	button2 = Button(Texture::TakeButton, Font::Font1, sf::Vector2f(), " Pick Up");
	button2.setScale(sf::Vector2f(0.6f, 0.6f));
	button2.setOrigin(ButtonOrigin::Center);
	button2.setDescriptionStyle(sf::Text::Bold);
	button2.setIndex(mIndex);

	button3 = Button(Texture::LookButton, Font::Font1, sf::Vector2f(), " Look");
	button3.setScale(sf::Vector2f(0.6f, 0.6f));
	button3.setOrigin(ButtonOrigin::Center);
	button3.setDescriptionStyle(sf::Text::Bold);
	button3.setIndex(mIndex);
}

void ActionWheel::unload()
{
	RMI.unloadResource(Texture::LookButton);
	RMI.unloadResource(Texture::TakeButton);
	RMI.unloadResource(Texture::TalkButton);
	RMI.unloadResource(Font::Font1);
}

void ActionWheel::update()
{
	mIsReleased = false;
	mTalkSelected = false;
	mPickUpSelected = false;
	mLookSelected = false;
	mButtonSelected = false;

	if (MouseState::isPressed(sf::Mouse::Left, 0.3))
		mIsPressed = true;
	else
		mIsReleased = true;

	if (mIsActive && mIsPressed)
	{
		button1.update();
		button2.update();
		button3.update();
		button1.setPosition(mPosition + button1Position);
		button2.setPosition(mPosition + button2Position);
		button3.setPosition(mPosition + button3Position);

		if (button1.isReleased())
		{
			mTalkSelected = true;
			mButtonSelected = true;
		}
		else if (button2.isReleased())
		{
			mPickUpSelected = true;
			mButtonSelected = true;
		}
		else if (button3.isReleased())
		{
			mLookSelected = true;
			mButtonSelected = true;
		}
	}
	else
	{
		mPosition = sf::Vector2f(MouseState::getMousePosition());
	}

	if (mIsReleased)
		mIsPressed = false;
}

void ActionWheel::render(IndexRenderer &iRenderer)
{
	if (mIsActive && mIsPressed)
	{
		button1.render(iRenderer);
		button2.render(iRenderer);
		button3.render(iRenderer);
	}
}