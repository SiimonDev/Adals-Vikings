#pragma once
#include "Button.h"	


class ActionWheel
{
public:
	ActionWheel();
	~ActionWheel();

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

	MouseState mouseState;

	bool mIsActive;
};

