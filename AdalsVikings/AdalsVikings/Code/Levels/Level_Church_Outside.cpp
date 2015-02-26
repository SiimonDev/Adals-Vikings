#include "Level_Church_Outside.h"
#include <iostream>

Level_Church_Outside::Level_Church_Outside(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Church_Outside;
}

void Level_Church_Outside::update(sf::Time &frametime)
{
	changeLevel();
	Level::update(frametime);
}

void Level_Church_Outside::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Church_Outside::load()
{
	Level::load();
	mPlayer.setPosition(sf::Vector2f(410, 1070));
}

void Level_Church_Outside::unload()
{
	Level::unload();
}

void Level_Church_Outside::changeLevel()
{
}

void Level_Church_Outside::checkInteractEvents()
{

}

void Level_Church_Outside::checkEvents()
{

}