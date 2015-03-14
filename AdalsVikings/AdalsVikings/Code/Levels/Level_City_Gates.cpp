#include "Level_City_Gates.h"
#include <iostream>

Level_City_Gates::Level_City_Gates(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::City_Gates;
}

void Level_City_Gates::restartSounds()
{

}

void Level_City_Gates::update(sf::Time &frametime)
{
	Level::update(frametime);
	changeLevel();
}

void Level_City_Gates::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_City_Gates::load()
{
	mPortals[GatesToRoad] = &PortalLoader::getPortal(GatesToRoad);
	mPortals[GatesToCliffs] = &PortalLoader::getPortal(GatesToCliffs);
	mPortals[GatesToRoad]->setWorking(true);
	mPortals[GatesToCliffs]->setWorking(true);

	Level::load();
}

void Level_City_Gates::unload()
{
	Level::unload();
}

void Level_City_Gates::changeLevel()
{
	if (mPortals[GatesToRoad]->getActivated() && mPortals[GatesToRoad]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Road);
	}
	if (mPortals[GatesToCliffs]->getActivated() && mPortals[GatesToCliffs]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Cliffs_Up);
	}
}

void Level_City_Gates::checkInteractEvents()
{

}
void Level_City_Gates::checkEvents()
{

}
