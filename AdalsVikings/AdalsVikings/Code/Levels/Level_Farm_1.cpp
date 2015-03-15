#include "Level_Farm_1.h"
#include <iostream>

Level_Farm_1::Level_Farm_1(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Farm_1;
}

void Level_Farm_1::restartSounds()
{

}

void Level_Farm_1::update(sf::Time &frametime)
{
	Level::update(frametime);
	changeLevel();
}

void Level_Farm_1::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Farm_1::load()
{
	mPortals[FarmToRoad] = &PortalLoader::getPortal(FarmToRoad);
	mPortals[Farm1ToFarm2] = &PortalLoader::getPortal(Farm1ToFarm2);
	mPortals[FarmToHills] = &PortalLoader::getPortal(FarmToHills);
	mPortals[FarmToHills]->setWorking(true);
	mPortals[Farm1ToFarm2]->setWorking(true);
	mPortals[FarmToRoad]->setWorking(true);
	Level::load();
}

void Level_Farm_1::unload()
{
	Level::unload();
}

void Level_Farm_1::changeLevel()
{
	if (mPortals[FarmToRoad]->getActivated() && mPortals[FarmToRoad]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Road);
	}
	if (mPortals[Farm1ToFarm2]->getActivated() && mPortals[Farm1ToFarm2]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Farm_2);
	}
	if (mPortals[FarmToHills]->getActivated() && mPortals[FarmToHills]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Hills);
	}
}

void Level_Farm_1::checkInteractEvents()
{

}
void Level_Farm_1::checkEvents()
{

}