#pragma once
#include "Level.h"

class Level_Camp : public Level
{
public:
	//General Functions
	Level_Camp(Player &player, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void changeLevel();
	void checkInteractEvents();
	void checkEvents();
};