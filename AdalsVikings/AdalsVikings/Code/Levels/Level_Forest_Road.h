#pragma once
#include "Level.h"

class Level_Forest_Road : public Level
{
public:
	//General Functions
	Level_Forest_Road(Player &player, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void changeLevel();
	void checkInteractEvents();
	void checkEvents();
	void setNearbyLevels();
};