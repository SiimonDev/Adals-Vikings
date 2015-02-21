#pragma once
#include "Button.h"	

class ActionWheel
{
public:
	ActionWheel();

	bool isButtonSelected();
	bool isTalkSelected();
	bool isPickUpSelected();
	bool isLookSelected();
	void setfalse();

	sf::Vector2f getPosition();

	void load();
	void unload();
	void update();
	void render(IndexRenderer &iRenderer);

private:
	Button button1;
	Button button2;
	Button button3;

	sf::Vector2f button1Position;
	sf::Vector2f button2Position;
	sf::Vector2f button3Position;
	sf::Vector2f mPosition;

	int mIndex;

	bool mIsActive;
	bool mIsReleased;

	bool mButtonSelected;
	bool mTalkSelected;
	bool mPickUpSelected;
	bool mLookSelected;
};