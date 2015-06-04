#pragma once
#include <SFML\Graphics.hpp>

namespace CursorType
{
	enum ID
	{
		Default,
		Arrow,
		Interact
	};
}

class MouseState
{
public:
	static void initialize();
	static void update(sf::Time frameTime);
	static void render();
	static void checkEvents(sf::Event::EventType event);
	static void setIsWorking(bool value);

	static void setCursorType(CursorType::ID id, float rotation = 0);

	static sf::Vector2i getMousePosition();
	static bool isClicked(sf::Mouse::Button button);
	static bool isReleased(sf::Mouse::Button button);
	static bool isReleased(sf::Mouse::Button button, double seconds);
	static bool isPressed(sf::Mouse::Button button, double seconds = 0);

private:
	MouseState();
	MouseState(const MouseState&);
	void operator=(const MouseState&);
};