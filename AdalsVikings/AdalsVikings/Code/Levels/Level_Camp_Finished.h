#pragma once
#include "Level.h"

class Level_Camp_Finished : public Level
{
public:
	//General Functions
	Level_Camp_Finished(Player &player, HUD &hud, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void changeLevel();
	void checkInteractEvents();
	void checkEvents();

private:

	bool mFade1, mFade2;

	Animation mCampFire;
};