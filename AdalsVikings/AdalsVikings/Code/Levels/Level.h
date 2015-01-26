#pragma once
#include <SFML\Graphics.hpp>
#include "..\Logics\LevelManager.h"
class Level
{
public:
	Level();
	virtual ~Level();

	virtual void update(sf::Time &frametime) = 0;
	virtual void render(sf::RenderWindow &window) = 0;
	virtual void load() = 0;
	virtual void unload() = 0;
};

