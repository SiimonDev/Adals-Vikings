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

void Debug::initialize(Player &player)
{
	mPlayer = &player;
}

void Debug::update(sf::Time frameTime)
{
	if (KeyboardState::isPressed(sf::Keyboard::F1))
		mDebugMode = !mDebugMode;

	/*if (KeyboardState::isPressed(sf::Keyboard::Num1))
		mPlayer->addItemToInventory("bucket");
		else if (KeyboardState::isPressed(sf::Keyboard::Num2))
		mPlayer->addItemToInventory("bucketBroken");
		else if (KeyboardState::isPressed(sf::Keyboard::Num3))
		mPlayer->addItemToInventory("rope");*/
}

bool Debug::debugMode()
{
	return mDebugMode;
}