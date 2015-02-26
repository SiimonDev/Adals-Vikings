#pragma once
#include "Level.h"

class Level_Tavern_Outside : public Level
{
public:
	//General Functions
	Level_Tavern_Outside(Player &player, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void changeLevel();
	void checkInteractEvents();
	void checkEvents();
};