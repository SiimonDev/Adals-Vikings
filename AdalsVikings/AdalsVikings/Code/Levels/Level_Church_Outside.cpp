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
	mPortals[Outside_ChurchToRoad] = &PortalLoader::getPortal(Outside_ChurchToRoad);
	mPortals[Outside_ChurchToRoad]->setWorking(true);
	Level::load();
	mPlayer.setPosition(sf::Vector2f(410, 1070));
}

void Level_Church_Outside::unload()
{
	Level::unload();
}

void Level_Church_Outside::changeLevel()
{
	if (mPortals[Outside_ChurchToRoad]->getActivated() && mPortals[Outside_ChurchToRoad]->getWorking())
		LVLMI.changeLevel(LevelFolder::Road);
}

void Level_Church_Outside::checkInteractEvents()
{

}

void Level_Church_Outside::checkEvents()
{

}