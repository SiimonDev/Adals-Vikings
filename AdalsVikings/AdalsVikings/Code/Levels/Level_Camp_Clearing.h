#pragma once
#include "Level.h"

class Level_Camp_Clearing : public Level
{
public:
	//General Functions
	Level_Camp_Clearing(Player &player, HUD &hud, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void changeLevel();
	void checkInteractEvents();
	void checkEvents();
	void restartSounds();

private:

	bool mFade1, mFade2, mSetLeifrDialogue;

	Animation mCampFire;
};