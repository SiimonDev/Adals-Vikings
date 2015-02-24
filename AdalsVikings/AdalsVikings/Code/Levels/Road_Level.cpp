#include "Road_Level.h"
#include "..\Logics\ResourceManager.h"
#include "..\Logics\AudioPlayer.h"
#include "..\Interface\LoadingScreen.h"
#include "..\Logics\KeyboardState.h"
#include "..\Logics\WindowState.h"
#include <iostream>

Road_Level::Road_Level(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mFolderPath = "Assets/MapFiles/Road/";
	mLevelID = TextureFolder::RoadLevel;
}

void Road_Level::update(sf::Time &frametime)
{
	changeLevel();
	Level::update(frametime);
}

void Road_Level::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Road_Level::load()
{
	mPortals[RoadToBeach] = &PortalLoader::getPortal(RoadToBeach);
	Level::load();
}

void Road_Level::unload()
{
	Level::unload();
}

void Road_Level::changeLevel()
{
	if (mPortals[RoadToBeach]->getActivated())
	{
		LVLMI.changeLevel(Beach);
	}
}
void Road_Level::checkInteractEvents()
{

}
void Road_Level::checkEvents()
{

}
