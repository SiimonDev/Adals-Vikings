#include "Level_Camp_Finished.h"
#include <iostream>

Level_Camp_Finished::Level_Camp_Finished(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Camp_Finished;
}

void Level_Camp_Finished::update(sf::Time &frametime)
{
	changeLevel();
	Level::update(frametime);
}

void Level_Camp_Finished::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Camp_Finished::load()
{
	Level::load();
	mPlayer.setPosition(sf::Vector2f(410, 1070));
}

void Level_Camp_Finished::unload()
{
	Level::unload();
}

void Level_Camp_Finished::changeLevel()
{
}

void Level_Camp_Finished::checkInteractEvents()
{

}
void Level_Camp_Finished::checkEvents()
{

}
