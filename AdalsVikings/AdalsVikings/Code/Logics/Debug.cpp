#include "Debug.h"
#include "KeyboardState.h"
#include "ResourceManager.h"

Debug::Debug()
{
}

Debug &Debug::getInstance()
{
	static Debug instance;
	return instance;
}

void Debug::update(sf::Time frameTime)
{
	if (KeyboardState::isPressed(sf::Keyboard::F1))
		mDebugMode = !mDebugMode;
}

bool Debug::debugMode()
{
	return mDebugMode;
}