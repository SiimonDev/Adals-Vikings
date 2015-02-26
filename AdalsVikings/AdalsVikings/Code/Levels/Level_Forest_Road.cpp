#include "Level_Forest_Road.h"
#include <iostream>

Level_Forest_Road::Level_Forest_Road(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Forest_Road;
}

void Level_Forest_Road::update(sf::Time &frametime)
{
	changeLevel();
	Level::update(frametime);
}

void Level_Forest_Road::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Forest_Road::load()
{
	mPortals[ForestCampToRoad] = &PortalLoader::getPortal(ForestCampToRoad);
	mPortals[ForestCampToRoad]->setWorking(true);

	Level::load();
	mPlayer.setPosition(sf::Vector2f(410, 1070));
}

void Level_Forest_Road::unload()
{
	Level::unload();
}

void Level_Forest_Road::changeLevel()
{
	if (mPortals[ForestCampToRoad]->getActivated() && mPortals[ForestCampToRoad]->getWorking())
		LVLMI.changeLevel(LevelFolder::Road);
}

void Level_Forest_Road::checkInteractEvents()
{

}
void Level_Forest_Road::checkEvents()
{

}