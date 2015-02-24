#pragma once
#include "Level.h"
#include "..\Logics\Animation.h"

class Beach_level : public Level
{
public:
	Beach_level(Player &player, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void changeLevel();
	void checkInteractEvents();
	void introCutscene(sf::Time &frameTime);
	void talkToNpcs();
	void endingCutscene(sf::Time &frameTime);

private:

	Animation mWaveAnimation;
	bool mIntroFade1, mIntroFade2, mIntroFade3;
	bool mEndingFade1, mEndingFade2, mEndingFade3, mEndingFade4;
	sf::View mCutSceneView;
};