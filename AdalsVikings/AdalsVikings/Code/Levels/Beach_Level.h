#pragma once
#include "Level.h"
#include "..\Logics\Animation.h"

class Beach_level : public Level
{
public:
	Beach_level(Player &player, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void changeLevel();
	void checkInteractEvents();

private:

	Animation mWaveAnimation;
};