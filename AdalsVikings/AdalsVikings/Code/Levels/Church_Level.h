#pragma once
#include "Level.h"

class Church_Level : public Level
{
public:
	//General Functions
	Church_Level(Player &player, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void changeLevel();
	void checkInteractEvents();
	void checkEvents();
};