#include "KeyboardState.h"

#define keyboardSize int(101)

static bool hasFocus;
static std::map<int, bool> keyStates;
static std::map<int, bool> oldKeyStates;
static std::map<int, double> timeDown;

void KeyboardState::initialize()
{
	for (int i = 0; i <= keyboardSize; i++)
	{
		keyStates.insert(std::make_pair(i, false));
		oldKeyStates.insert(std::make_pair(i, false));
		timeDown.insert(std::make_pair(i, 0));
	}
	hasFocus = true;
}

void KeyboardState::update(sf::Time frameTime)
{	
	for (int i = 0; i <= keyboardSize; i++)
	{
		oldKeyStates[i] = keyStates[i];

		if (oldKeyStates[i])
			timeDown[i] += frameTime.asSeconds();
		else
			timeDown[i] = 0;
	}
	for (int i = 0; i <= keyboardSize; i++)
		keyStates.at(i) = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i));
}

void KeyboardState::checkEvents(sf::Event::EventType event)
{
	if (event == sf::Event::LostFocus)
		hasFocus = false;
	else if (event == sf::Event::GainedFocus)
		hasFocus = true;
}

bool KeyboardState::isPressed(sf::Keyboard::Key key)
{
	if (hasFocus)
	{
		return (keyStates[key] && !oldKeyStates[key]);
	}
	return false;
}

bool KeyboardState::isReleased(sf::Keyboard::Key key)
{
	if (hasFocus)
	{
		return (!keyStates[key] && oldKeyStates[key]);
	}
	return false;
}

bool KeyboardState::isReleased(sf::Keyboard::Key key, double seconds)
{
	if (hasFocus)
	{
		if (!keyStates[key] && oldKeyStates[key])
		{
			if (timeDown.at(key) <= seconds)
				return true;
		}
	}
	return false;
}

bool KeyboardState::isDown(sf::Keyboard::Key key, double seconds)
{
	if (hasFocus)
	{
		if (keyStates[key])
		{
			if (timeDown.at(key) >= seconds)
				return true;
		}
	}
	return false;
}