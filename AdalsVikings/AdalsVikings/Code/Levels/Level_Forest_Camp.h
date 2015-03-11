#pragma once
#include "Level.h"

class Level_Forest_Camp : public Level
{
public:
	//General Functions
	Level_Forest_Camp(Player &player, HUD &hud, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void changeLevel();
	void checkInteractEvents();
	void checkEvents();
	void restartSounds();

private:
	sf::Sprite mDruids;
	Animation mFireAnimation;

	bool mFade1, mFade2, mFade3, mFade4, mFade5, mFade6, mDestinationReached, mSuperPath;
};