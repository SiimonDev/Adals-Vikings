#pragma once
#include "Level.h"

class Level_Cavern_Left : public Level
{
public:
	//General Functions
	Level_Cavern_Left(Player &player, HUD &hud, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void changeLevel();
	void checkInteractEvents();
	void checkEvents();
	void restartSounds();

private:

	bool mFade1, mFade2;
};