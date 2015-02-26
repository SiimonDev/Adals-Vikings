#include "Level_Church_Inside.h"
#include <iostream>

Level_Church_Inside::Level_Church_Inside(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Church_Inside;
}

void Level_Church_Inside::update(sf::Time &frametime)
{
	changeLevel();
	Level::update(frametime);
}

void Level_Church_Inside::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Church_Inside::load()
{
	Level::load();
	mPlayer.setPosition(sf::Vector2f(410, 1070));
}

void Level_Church_Inside::unload()
{
	Level::unload();
}

void Level_Church_Inside::changeLevel()
{
}

void Level_Church_Inside::checkInteractEvents()
{

}

void Level_Church_Inside::checkEvents()
{

}
