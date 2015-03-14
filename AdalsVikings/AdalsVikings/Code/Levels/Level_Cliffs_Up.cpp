#include "Level_Cliffs_Up.h"
#include <iostream>

Level_Cliffs_Up::Level_Cliffs_Up(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Cliffs_Up;
}

void Level_Cliffs_Up::restartSounds()
{

}

void Level_Cliffs_Up::update(sf::Time &frametime)
{


	Level::update(frametime);
	changeLevel();
}

void Level_Cliffs_Up::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Cliffs_Up::load()
{
	mPortals[CliffsToGates] = &PortalLoader::getPortal(CliffsToGates);
	mPortals[CliffsToGates]->setWorking(true);
	Level::load();
}

void Level_Cliffs_Up::unload()
{
	Level::unload();
}

void Level_Cliffs_Up::changeLevel()
{
	if (mPortals[CliffsToGates]->getActivated() && mPortals[CliffsToGates]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::City_Gates);
	}
}

void Level_Cliffs_Up::checkInteractEvents()
{

}
void Level_Cliffs_Up::checkEvents()
{

}
