#include "Level_Camp.h"
#include <iostream>

Level_Camp::Level_Camp(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Camp;
}

void Level_Camp::update(sf::Time &frametime)
{
	changeLevel();
	Level::update(frametime);
}

void Level_Camp::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Camp::load()
{
	Level::load();
	mPlayer.setPosition(sf::Vector2f(410, 1070));
}

void Level_Camp::unload()
{
	Level::unload();
}

void Level_Camp::changeLevel()
{
}

void Level_Camp::checkInteractEvents()
{

}
void Level_Camp::checkEvents()
{

}
