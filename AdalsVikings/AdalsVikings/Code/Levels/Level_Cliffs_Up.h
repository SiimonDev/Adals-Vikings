#pragma once
#include "Level.h"

class Level_Cliffs_Up : public Level
{
public:
	//General Functions
	Level_Cliffs_Up(Player &player, HUD &hud, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void changeLevel(sf::Time &frametime);
	void checkInteractEvents();
	void checkEvents();
	void restartSounds();
};