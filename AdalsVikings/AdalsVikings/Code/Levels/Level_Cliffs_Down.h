#pragma once
#include "Level.h"

class Level_Cliffs_Down : public Level
{
public:
	//General Functions
	Level_Cliffs_Down(Player &player, HUD &hud, ActionWheel &actionWheel);

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	void changeLevel(sf::Time &frametime);
	void checkInteractEvents();
	void checkEvents();
	void restartSounds();

private:
	Animation mWaveAnimation;
	Animation mWaveAnimationIdle;
	bool mCannotGo;
};