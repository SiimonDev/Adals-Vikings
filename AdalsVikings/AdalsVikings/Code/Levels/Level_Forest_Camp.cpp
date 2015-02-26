#include "Level_Forest_Camp.h"
#include <iostream>

Level_Forest_Camp::Level_Forest_Camp(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Forest_Camp;
}

void Level_Forest_Camp::update(sf::Time &frametime)
{
	changeLevel();
	Level::update(frametime);
}

void Level_Forest_Camp::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Forest_Camp::load()
{
	
	Level::load();
	mPlayer.setPosition(sf::Vector2f(410, 1070));
}

void Level_Forest_Camp::unload()
{
	Level::unload();
}

void Level_Forest_Camp::changeLevel()
{
}

void Level_Forest_Camp::checkInteractEvents()
{

}
void Level_Forest_Camp::checkEvents()
{

}
