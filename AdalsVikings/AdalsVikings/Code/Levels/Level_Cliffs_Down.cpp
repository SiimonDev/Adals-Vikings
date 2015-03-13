#include "Level_Cliffs_Down.h"
#include <iostream>

Level_Cliffs_Down::Level_Cliffs_Down(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Cliffs_Down;
}

void Level_Cliffs_Down::restartSounds()
{

}

void Level_Cliffs_Down::update(sf::Time &frametime)
{
	Level::update(frametime);
	changeLevel();
}

void Level_Cliffs_Down::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Cliffs_Down::load()
{
	Level::load();
}

void Level_Cliffs_Down::unload()
{
	Level::unload();
}

void Level_Cliffs_Down::changeLevel()
{
}

void Level_Cliffs_Down::checkInteractEvents()
{

}
void Level_Cliffs_Down::checkEvents()
{

}
