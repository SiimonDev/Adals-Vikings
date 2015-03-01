#pragma once
#include "Level.h"
class Level_Ship_1 : public Level
{
public:
	Level_Ship_1(Player &player, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void checkInteractEvents();
	void checkEvents();
	void setNearbyLevels();

	void changeLevel(sf::Time &frameTime);

private:
	bool mGameStart;
	bool mOldBucketAdded;
	bool mStartBrynja, mBrynjaFade1, mBrynjaFade2, mBrynjaConv;
	sf::Sprite mIntroScreen;
};

