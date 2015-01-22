#pragma once
#include <SFML\Graphics.hpp>
#include "ResourceManager.h"
class Level
{
public:
	Level();
	virtual ~Level();

	virtual void update(sf::Time &frametime) = 0;
	virtual void render(sf::RenderWindow &win) = 0;

};

