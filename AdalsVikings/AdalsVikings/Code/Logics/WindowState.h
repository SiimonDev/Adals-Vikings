#pragma once
#include <SFML\Graphics.hpp>

#define CurrentWindow WindowState::getInstance().getWindow()
#define WinState WindowState::getInstance()

class WindowState
{
public:
	static WindowState &getInstance();

	void initialize(sf::RenderWindow &window);

	sf::RenderWindow &getWindow();

private:
	WindowState();
	WindowState(const WindowState&);
	void operator=(const WindowState&);

	sf::RenderWindow* mWindow;
};