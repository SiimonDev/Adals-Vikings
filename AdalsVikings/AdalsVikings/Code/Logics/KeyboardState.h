#pragma once
#include <SFML\Graphics.hpp>

class KeyboardState
{
public:
	static void initialize();
	static void update(sf::Time frameTime);
	static void checkEvents(sf::Event::EventType event);

	static bool isPressed(sf::Keyboard::Key key);
	static bool isReleased(sf::Keyboard::Key key);
	static bool isReleased(sf::Keyboard::Key key, double seconds);
	static bool isDown(sf::Keyboard::Key key, double seconds = 0);
private:
	KeyboardState();
	KeyboardState(const KeyboardState&);
	void operator=(const KeyboardState&);
};