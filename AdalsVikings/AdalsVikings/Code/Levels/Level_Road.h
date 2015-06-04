#pragma once
#include "Level.h"

class Level_Road : public Level
{
public:
	//General Functions
	Level_Road(Player &player, HUD &hud, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void changeLevel();
	void checkInteractEvents();
	void checkEvents();
	void restartSounds();

private:
	bool mFade1, mFade2, mFade3, mFade4, mFade5, mHasSpawned;
};

