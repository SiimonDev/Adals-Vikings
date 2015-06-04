#pragma once
#include "Level.h"

class Level_Cavern_Ruins_Right : public Level
{
public:
	//General Functions
	Level_Cavern_Ruins_Right(Player &player, HUD &hud, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void changeLevel();
	void checkInteractEvents();
	void checkEvents();
	void restartSounds();

private:
	bool mFade1;
};