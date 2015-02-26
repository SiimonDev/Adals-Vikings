#include "Level_Tavern_Inside.h"
#include <iostream>

Level_Tavern_Inside::Level_Tavern_Inside(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Tavern_Inside;
}

void Level_Tavern_Inside::update(sf::Time &frametime)
{
	changeLevel();
	Level::update(frametime);
}

void Level_Tavern_Inside::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Tavern_Inside::load()
{
	Level::load();
	mPlayer.setPosition(sf::Vector2f(410, 1070));
}

void Level_Tavern_Inside::unload()
{
	Level::unload();
}

void Level_Tavern_Inside::changeLevel()
{
}

void Level_Tavern_Inside::checkInteractEvents()
{

}
void Level_Tavern_Inside::checkEvents()
{

}
