#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "..\Interface\LoadingScreen.h"

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
	void update(sf::Time gameTime);
	void render();
	void processEvents();
	sf::RenderWindow mWindow;
	sf::Image icon;
};

