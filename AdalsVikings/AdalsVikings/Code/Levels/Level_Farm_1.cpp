#include "Level_Farm_1.h"
#include <iostream>

Level_Farm_1::Level_Farm_1(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Farm_1;
}

void Level_Farm_1::restartSounds()
{

}

void Level_Farm_1::update(sf::Time &frametime)
{
	Level::update(frametime);
	changeLevel();
}

void Level_Farm_1::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Farm_1::load()
{
	Level::load();
}

void Level_Farm_1::unload()
{
	Level::unload();
}

void Level_Farm_1::changeLevel()
{
}

void Level_Farm_1::checkInteractEvents()
{

}
void Level_Farm_1::checkEvents()
{

}