#include "Level_Cavern_Ruins_Right.h"
#include <iostream>

Level_Cavern_Ruins_Right::Level_Cavern_Ruins_Right(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Cavern_Ruins_Right;
}

void Level_Cavern_Ruins_Right::restartSounds()
{

}

void Level_Cavern_Ruins_Right::update(sf::Time &frametime)
{
	Level::update(frametime);
	changeLevel();
}

void Level_Cavern_Ruins_Right::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Cavern_Ruins_Right::load()
{
	Level::load();
}

void Level_Cavern_Ruins_Right::unload()
{
	Level::unload();
}

void Level_Cavern_Ruins_Right::changeLevel()
{
}

void Level_Cavern_Ruins_Right::checkInteractEvents()
{

}
void Level_Cavern_Ruins_Right::checkEvents()
{

}
