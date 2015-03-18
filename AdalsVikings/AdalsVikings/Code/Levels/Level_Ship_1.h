#pragma once
#include "Level.h"

class Level_Ship_1 : public Level
{
public:
	Level_Ship_1(Player &player, HUD &hud, ActionWheel &actionWheel);

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
	bool mStartBrynja, mBrynjaFade1, mBrynjaFade2, mBrynjaConv, mBucketFade1, mBucketFade2;

	Animation mRopeAnimation;
	Animation mWaveAnimation;
	Animation mSeaAnimation;
};