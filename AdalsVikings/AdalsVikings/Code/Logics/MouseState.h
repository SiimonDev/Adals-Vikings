#pragma once
#include <SFML\Graphics.hpp>

class MouseState
{
public:
	static void initialize(sf::RenderWindow &window);
	static sf::Vector2i getMousePosition();
	bool isDown(sf::Mouse::Button button, double seconds);
	bool isDown(sf::Mouse::Button button);
	bool isClicked(sf::Mouse::Button button);
	bool isReleased(sf::Mouse::Button button, double seconds);
	bool isReleased(sf::Mouse::Button button);

private:
	bool oldIsButtonHeld = false;
	bool oldIsButtonPressed = false;

	sf::Clock holdClock;
	sf::Clock releaseClock;

	double holdTimePassed;
	double releaseTimePassed;
};
