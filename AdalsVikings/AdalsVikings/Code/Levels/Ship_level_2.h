#pragma once
#include "Level.h"
#include "..\Logics\Fade.h"
class Ship_level_2 : public Level
{
public:
	Ship_level_2(Player &player, ActionWheel &ActionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void checkInteractEvents();
	void checkEvents();

	void changeLevel(sf::Time &frameTime);
	void runCutscene(sf::Time &frameTime);


private:
	void pickUpBucket();

	sf::View mCutsceneView;
	sf::RectangleShape mFadeRectangle;
	bool mGameStart, mDone, mStartedGiveDialogue, mBrandrMapFade;
	sf::Sprite spritilus;
	sf::Texture mTexture;
	float mZoom, mAlpha, mEnd;
};

