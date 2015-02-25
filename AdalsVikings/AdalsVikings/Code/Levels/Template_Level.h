#pragma once
#include "Level.h"

class Template_Level : public Level
{
public:
	//General Functions
	Template_Level(Player &player, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void changeLevel();
	void checkInteractEvents();
	void checkEvents();
};