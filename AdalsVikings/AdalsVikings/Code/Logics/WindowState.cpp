#include "WindowState.h"

WindowState::WindowState()
{
}

WindowState &WindowState::getInstance()
{
	static WindowState* instance;

	if (instance == NULL)
		instance = new WindowState();

	return *instance;
}

void WindowState::initialize(sf::RenderWindow &window)
{
	mWindow = &window;
}

sf::RenderWindow &WindowState::getWindow()
{
	return *mWindow;
}