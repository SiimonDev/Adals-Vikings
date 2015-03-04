#include "Level_Tavern_Outside.h"
#include <iostream>

Level_Tavern_Outside::Level_Tavern_Outside(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Tavern_Outside;
}

void Level_Tavern_Outside::update(sf::Time &frametime)
{
	changeLevel();
	Level::update(frametime);
}

void Level_Tavern_Outside::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Tavern_Outside::load()
{
	mPortals[TavernOutsideToBeach] = &PortalLoader::getPortal(TavernOutsideToBeach);
	mPortals[TavernOutsideToTavernInside] = &PortalLoader::getPortal(TavernOutsideToTavernInside);
	mPortals[TavernOutsideToTavernInside]->setWorking(true);
	mPortals[TavernOutsideToBeach]->setWorking(true);
	Level::load();
}

void Level_Tavern_Outside::unload()
{
	Level::unload();
}

void Level_Tavern_Outside::changeLevel()
{
	if (mPortals[TavernOutsideToBeach]->getActivated() && mPortals[TavernOutsideToBeach]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Beach);
	}
	else if (mPortals[TavernOutsideToTavernInside]->getActivated() && mPortals[TavernOutsideToTavernInside]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Tavern_Inside);
	}
}

void Level_Tavern_Outside::checkInteractEvents()
{

}

void Level_Tavern_Outside::checkEvents()
{

}