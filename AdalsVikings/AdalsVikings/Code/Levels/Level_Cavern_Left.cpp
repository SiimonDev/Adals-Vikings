#include "Level_Cavern_Left.h"
#include <iostream>

Level_Cavern_Left::Level_Cavern_Left(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Cavern_Left;
}

void Level_Cavern_Left::restartSounds()
{

}

void Level_Cavern_Left::update(sf::Time &frametime)
{
	Level::update(frametime);
	changeLevel();
}

void Level_Cavern_Left::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Cavern_Left::load()
{
	Level::load();
}

void Level_Cavern_Left::unload()
{
	Level::unload();
}

void Level_Cavern_Left::changeLevel()
{
}

void Level_Cavern_Left::checkInteractEvents()
{

}
void Level_Cavern_Left::checkEvents()
{

}
