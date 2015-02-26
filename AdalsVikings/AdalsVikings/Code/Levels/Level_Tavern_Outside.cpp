#include "Level_Tavern_Outside.h"
#include <iostream>

Level_Tavern_Outside::Level_Tavern_Outside(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Tavern_Outside;
}

void Level_Tavern_Outside::update(sf::Time &frametime)
{
	changeLevel();
	Level::update(frametime);
}

void Level_Tavern_Outside::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Tavern_Outside::load()
{
	Level::load();
	mPlayer.setPosition(sf::Vector2f(410, 1070));
}

void Level_Tavern_Outside::unload()
{
	Level::unload();
}

void Level_Tavern_Outside::changeLevel()
{
}

void Level_Tavern_Outside::checkInteractEvents()
{

}

void Level_Tavern_Outside::checkEvents()
{

}