#pragma once
#include "Level.h"
class Ship_level_1 : public Level
{
public:
	Ship_level_1(Player &player, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void checkInteractEvents();
	void checkEvents();

	void changeLevel(sf::Time &frameTime);

private:
	bool mGameStart;
	bool mOldBucketAdded;
	bool mStartBrynja, mBrynjaFade1, mBrynjaFade2, mBrynjaConv;
};

