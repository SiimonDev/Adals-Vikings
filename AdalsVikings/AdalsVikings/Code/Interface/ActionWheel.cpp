#include "ActionWheel.h"
#include <iostream>


ActionWheel::ActionWheel()
{
	button1Position = sf::Vector2f(0, -80);
	button2Position = sf::Vector2f(80, 80);
	button3Position = sf::Vector2f(-80, 80);

	mIndex = 9999999;
}

bool ActionWheel::isButtonSelected() { return mButtonSelected; };
bool ActionWheel::isTalkSelected() { return mTalkSelected; };
bool ActionWheel::isPickUpSelected() { return mPickUpSelected; };
bool ActionWheel::isLookSelected() { return mLookSelected; };

sf::Vector2f ActionWheel::getPosition(){ return mPosition; }

void ActionWheel::load()
{
	RMI.load(Fonts::ActionWheelDescription, "assets/fonts/font1.ttf");
	RMI.load(Textures::LookButton, "assets/images/interface/buttons/interface_look.png");
	RMI.load(Textures::TakeButton, "assets/images/interface/buttons/interface_take.png");
	RMI.load(Textures::TalkButton, "assets/images/interface/buttons/interface_talk.png");

	button1 = Button(Textures::TalkButton, Fonts::ActionWheelDescription, sf::Vector2f(), " Talk");
	button1.setScale(sf::Vector2f(0.6f, 0.6f));
	button1.setOrigin(ButtonOrigin::Center);
	button1.setDescriptionStyle(sf::Text::Bold);
	button1.setIndex(mIndex);

	button2 = Button(Textures::TakeButton, Fonts::ActionWheelDescription, sf::Vector2f(), " Pick Up");
	button2.setScale(sf::Vector2f(0.6f, 0.6f));
	button2.setOrigin(ButtonOrigin::Center);
	button2.setDescriptionStyle(sf::Text::Bold);
	button2.setIndex(mIndex);

	button3 = Button(Textures::LookButton, Fonts::ActionWheelDescription, sf::Vector2f(), " Look");
	button3.setScale(sf::Vector2f(0.6f, 0.6f));
	button3.setOrigin(ButtonOrigin::Center);
	button3.setDescriptionStyle(sf::Text::Bold);
	button3.setIndex(mIndex);
}

void ActionWheel::unload()
{
	RMI.unload(Textures::LookButton);
	RMI.unload(Textures::TakeButton);
	RMI.unload(Textures::TalkButton);
	RMI.unload(Fonts::ActionWheelDescription);
}

void ActionWheel::update()
{
	mIsReleased = false;
	mTalkSelected = false;
	mPickUpSelected = false;
	mLookSelected = false;
	mButtonSelected = false;

	if (MouseState::isPressed(sf::Mouse::Left, 0.5))
		mIsActive = true;
	else
		mIsReleased = true;

	if (mIsActive)
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
		mIsActive = false;
}

void ActionWheel::render(IndexRenderer &iRenderer)
{
	if (mIsActive)
	{
		button1.render(iRenderer);
		button2.render(iRenderer);
		button3.render(iRenderer);
	}
}
void ActionWheel::setfalse()
{
	mTalkSelected = false;
	mButtonSelected = false;
	mPickUpSelected = false;
	mLookSelected = false;

}
