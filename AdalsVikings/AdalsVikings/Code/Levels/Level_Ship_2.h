#pragma once
#include "Level.h"
#include "..\Logics\Fade.h"
class Level_Ship_2 : public Level
{
public:
	Level_Ship_2(Player &player, HUD &hud, ActionWheel &ActionWheel);

	void restartSounds();
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
	bool mShowIntroScreen, mDone, mStartedGiveDialogue, mBrandrMapFade;
	sf::Sprite spritilus;
	sf::Texture mTexture;
	float mZoom, mAlpha, mEnd;

	Animation mWaveAnimation;
	Animation mSeaAnimation;
};