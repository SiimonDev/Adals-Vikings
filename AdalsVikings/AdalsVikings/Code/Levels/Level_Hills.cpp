#include "Level_Hills.h"
#include <iostream>

Level_Hills::Level_Hills(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Hills;
}

void Level_Hills::restartSounds()
{

}

void Level_Hills::update(sf::Time &frametime)
{
	Level::update(frametime);
	changeLevel();
}

void Level_Hills::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Hills::load()
{
	Level::load();
}

void Level_Hills::unload()
{
	Level::unload();
}

void Level_Hills::changeLevel()
{
}

void Level_Hills::checkInteractEvents()
{

}
void Level_Hills::checkEvents()
{

}
