#include "Level_Road.h"
#include <iostream>

Level_Road::Level_Road(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Road;
}

void Level_Road::update(sf::Time &frametime)
{
	changeLevel();
	Level::update(frametime);
}

void Level_Road::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Road::load()
{
	mPortals[RoadToBeach] = &PortalLoader::getPortal(RoadToBeach);
	mPortals[RoadToOutside_Chuch] = &PortalLoader::getPortal(RoadToOutside_Chuch);
	mPortals[RoadToForestCamp] = &PortalLoader::getPortal(RoadToForestCamp);

	mPortals[RoadToForestCamp]->setWorking(true);
	mPortals[RoadToOutside_Chuch]->setWorking(true);
	mPortals[RoadToBeach]->setWorking(true);
	Level::load();

	mPlayer.setPosition(sf::Vector2f(410, 1070));
}

void Level_Road::unload()
{
	Level::unload();
}

void Level_Road::changeLevel()
{
	if (mPortals[RoadToBeach]->getActivated() && mPortals[RoadToBeach]->getWorking())
		LVLMI.changeLevel(LevelFolder::Beach);
	else if (mPortals[RoadToOutside_Chuch]->getActivated() && mPortals[RoadToOutside_Chuch]->getWorking())
		LVLMI.changeLevel(LevelFolder::Church_Outside);
	else if (mPortals[RoadToForestCamp]->getActivated() && mPortals[RoadToForestCamp]->getWorking())
		LVLMI.changeLevel(LevelFolder::Forest_Road);
}
void Level_Road::checkInteractEvents()
{

}
void Level_Road::checkEvents()
{
}
