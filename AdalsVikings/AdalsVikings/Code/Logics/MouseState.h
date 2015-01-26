#pragma once
#include <SFML\Graphics.hpp>

class MouseState
{
public:
	static MouseState &getInstance();

	void initialize(sf::RenderWindow &window);
	sf::Vector2i getMousePosition();
private:
	MouseState();
	MouseState(const MouseState&);
	void operator=(const MouseState&);
};
