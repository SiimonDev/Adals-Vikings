#include "Level_Forest_Camp.h"
#include <iostream>

Level_Forest_Camp::Level_Forest_Camp(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Forest_Camp;
}

void Level_Forest_Camp::update(sf::Time &frametime)
{
	changeLevel();
	Level::update(frametime);
}

void Level_Forest_Camp::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Forest_Camp::load()
{
	mPortals[ForestCampToForestRoad] = &PortalLoader::getPortal(ForestCampToForestRoad);
	mPortals[ForestCampToForestRoad]->setWorking(true);
	Level::load();
}

void Level_Forest_Camp::unload()
{
	Level::unload();
}

void Level_Forest_Camp::changeLevel()
{
	if (mPortals[ForestCampToForestRoad]->getActivated() && mPortals[ForestCampToForestRoad]->getWorking())
		LVLMI.changeLevel(LevelFolder::Forest_Road);
}

void Level_Forest_Camp::checkInteractEvents()
{

}
void Level_Forest_Camp::checkEvents()
{

}

//void Level_Forest_Camp::setNearbyLevels()
//{
//	for (std::map<LevelFolder::ID, LevelPtr>::iterator it = LVLMI.getCurrentLevels().begin(); it != LVLMI.getCurrentLevels().end(); ++it)
//	{
//		if (it->first == LevelFolder::Forest_Road)
//			it->second->setIsNearbyLevel(true);
//		else
//			it->second->setIsNearbyLevel(false);
//	}
//}
