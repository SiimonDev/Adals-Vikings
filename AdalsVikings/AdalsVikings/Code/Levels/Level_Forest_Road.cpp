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
	RMI.loadResource(Footsteps::Dirt);
	mPortals[ForestRoadToCamp] = &PortalLoader::getPortal(ForestRoadToCamp);
	mPortals[ForestRoadToForestCamp] = &PortalLoader::getPortal(ForestRoadToForestCamp);
	mPortals[ForestRoadToCamp]->setWorking(true);
	mPortals[ForestRoadToForestCamp]->setWorking(true);

	Level::load();

	mCurrentFootsteps = Footsteps::Dirt;
}

void Level_Forest_Road::unload()
{
	RMI.unloadResource(Footsteps::Dirt);
	mPortals.erase(ForestRoadToCamp);
	Level::unload();
}

void Level_Forest_Road::changeLevel()
{
	if (mPortals[ForestRoadToCamp]->getActivated() && mPortals[ForestRoadToCamp]->getWorking())
		LVLMI.changeLevel(LevelFolder::Camp_Clearing);
	else if (mPortals[ForestRoadToForestCamp]->getActivated() && mPortals[ForestRoadToForestCamp]->getWorking())
		LVLMI.changeLevel(LevelFolder::Forest_Camp);
}

void Level_Forest_Road::checkInteractEvents()
{

}
void Level_Forest_Road::checkEvents()
{

}