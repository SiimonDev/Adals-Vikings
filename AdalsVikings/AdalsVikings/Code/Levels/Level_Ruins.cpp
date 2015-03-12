#include "Level_Ruins.h"
#include <iostream>

Level_Ruins::Level_Ruins(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Ruins;
}

void Level_Ruins::restartSounds()
{

}

void Level_Ruins::update(sf::Time &frametime)
{
	Level::update(frametime);
	changeLevel();
}

void Level_Ruins::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Ruins::load()
{
	Level::load();
}

void Level_Ruins::unload()
{
	Level::unload();
}

void Level_Ruins::changeLevel()
{
}

void Level_Ruins::checkInteractEvents()
{

}
void Level_Ruins::checkEvents()
{

}
