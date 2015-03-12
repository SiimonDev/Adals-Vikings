#include "Level_Cavern_Right.h"
#include <iostream>

Level_Cavern_Right::Level_Cavern_Right(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Cavern_Right;
}

void Level_Cavern_Right::restartSounds()
{

}

void Level_Cavern_Right::update(sf::Time &frametime)
{
	Level::update(frametime);
	changeLevel();
}

void Level_Cavern_Right::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Cavern_Right::load()
{
	Level::load();
}

void Level_Cavern_Right::unload()
{
	Level::unload();
}

void Level_Cavern_Right::changeLevel()
{
}

void Level_Cavern_Right::checkInteractEvents()
{

}
void Level_Cavern_Right::checkEvents()
{

}
