#include "Church_Level.h"
#include <iostream>

Church_Level::Church_Level(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Church;
}

void Church_Level::update(sf::Time &frametime)
{
	changeLevel();
	Level::update(frametime);
}

void Church_Level::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Church_Level::load()
{
	Level::load();
	mPlayer.setPosition(sf::Vector2f(410, 1070));
}

void Church_Level::unload()
{
	Level::unload();
}

void Church_Level::changeLevel()
{
}

void Church_Level::checkInteractEvents()
{

}

void Church_Level::checkEvents()
{

}