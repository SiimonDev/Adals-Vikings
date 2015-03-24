#pragma once
#include "Level.h"

class Level_Hills : public Level
{
public:
	//General Functions
	Level_Hills(Player &player, HUD &hud, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void changeLevel();
	void checkInteractEvents();
	void checkEvents();
	void restartSounds();

private:
	bool mVideoPlayed;
	bool mFade1, mFade2;
};