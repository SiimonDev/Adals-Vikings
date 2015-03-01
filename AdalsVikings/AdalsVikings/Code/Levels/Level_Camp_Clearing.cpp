#include "Level_Camp_Clearing.h"
#include <iostream>

Level_Camp_Clearing::Level_Camp_Clearing(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Camp_Clearing;
}

void Level_Camp_Clearing::update(sf::Time &frametime)
{
	changeLevel();
	Level::update(frametime);
}

void Level_Camp_Clearing::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Camp_Clearing::load()
{
	Level::load();
}

void Level_Camp_Clearing::unload()
{
	Level::unload();
}

void Level_Camp_Clearing::changeLevel()
{
}

void Level_Camp_Clearing::checkInteractEvents()
{

}
void Level_Camp_Clearing::checkEvents()
{

}

void Level_Camp_Clearing::setNearbyLevels()
{

}
