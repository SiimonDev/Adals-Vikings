#pragma once
#include "Level.h"

class Level_Farm_2 : public Level
{
public:
	//General Functions
	Level_Farm_2(Player &player, HUD &hud, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void changeLevel();
	void checkInteractEvents();
	void checkEvents();
	void restartSounds();
};