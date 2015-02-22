#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	void loadGame();
	void loadMenu();
	void resize(int width, int height);
	void update(sf::Time gameTime);
	void render();
	void processEvents();
	sf::RenderWindow mWindow;
};

