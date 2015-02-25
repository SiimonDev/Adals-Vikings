#include "Template_Level.h"
#include <iostream>

Template_Level::Template_Level(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Church;
}

void Template_Level::update(sf::Time &frametime)
{
	changeLevel();
	Level::update(frametime);
}

void Template_Level::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Template_Level::load()
{
	Level::load();
	mPlayer.setPosition(sf::Vector2f(410, 1070));
}

void Template_Level::unload()
{
	Level::unload();
}

void Template_Level::changeLevel()
{
}

void Template_Level::checkInteractEvents()
{

}
void Template_Level::checkEvents()
{

}
