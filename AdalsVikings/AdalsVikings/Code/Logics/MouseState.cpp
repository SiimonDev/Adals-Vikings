#include "MouseState.h"
#include <iostream>

static sf::RenderWindow *mWindow;
static double virtualWidth;
static double virtualHeight;

static sf::Vector2f scale;

void MouseState::initialize(sf::RenderWindow &window)
{
	mWindow = &window;
}

sf::Vector2i MouseState::getMousePosition()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*mWindow);

	virtualWidth = mWindow->getView().getSize().x;
	virtualHeight = mWindow->getView().getSize().y;

	scale.x = virtualWidth / mWindow->getSize().x;
	scale.y = virtualHeight / mWindow->getSize().y;

	return sf::Vector2i(mousePos.x * scale.x, mousePos.y * scale.y);
}

bool MouseState::isDown(sf::Mouse::Button button)
{
	return sf::Mouse::isButtonPressed(button);
}

bool MouseState::isDown(sf::Mouse::Button button, double seconds)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		holdTimePassed += holdClock.restart().asSeconds();
		if (holdTimePassed >= seconds)
		{
			holdTimePassed = 0;
			return true;
		}
	}
	else
	{
		holdTimePassed = 0;
	}
	return false;
}

bool MouseState::isClicked(sf::Mouse::Button button)
{
	if (sf::Mouse::isButtonPressed(button) && oldIsButtonPressed == false)
	{
		oldIsButtonPressed = true;
		return true;
	}
	else if (!sf::Mouse::isButtonPressed(button))
	{
		oldIsButtonPressed = false;
	}
	return false;
}

bool MouseState::isReleased(sf::Mouse::Button button, double seconds)
{
	bool retur = false;
	if (!sf::Mouse::isButtonPressed(button) && oldIsButtonHeld == true)
	{	
		releaseTimePassed += releaseClock.restart().asSeconds();

		if (releaseTimePassed >= seconds)
			retur = false;
		else
			retur = true;

		releaseTimePassed = 0;
		oldIsButtonHeld = false;
	}
	else if (sf::Mouse::isButtonPressed(button))
	{
		oldIsButtonHeld = true;
	}
	else
	{
		releaseTimePassed = 0;
	}

	return retur;
}

bool MouseState::isReleased(sf::Mouse::Button button)
{
	if (!sf::Mouse::isButtonPressed(button) && oldIsButtonHeld == true)
	{
		oldIsButtonHeld = false;
		return true;
	}
	else if (sf::Mouse::isButtonPressed(button))
	{
		oldIsButtonHeld = true;
	}
	return false;
}