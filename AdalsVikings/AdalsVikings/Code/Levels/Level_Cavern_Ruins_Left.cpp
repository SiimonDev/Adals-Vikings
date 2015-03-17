#include "Level_Cavern_Ruins_Left.h"
#include <iostream>

Level_Cavern_Ruins_Left::Level_Cavern_Ruins_Left(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Cavern_Ruins_Left;
}

void Level_Cavern_Ruins_Left::restartSounds()
{

}

void Level_Cavern_Ruins_Left::update(sf::Time &frametime)
{
	Level::update(frametime);
	changeLevel();
}

void Level_Cavern_Ruins_Left::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Cavern_Ruins_Left::load()
{
	mPortals[CRuinsLeftToCRuinsRight] = &PortalLoader::getPortal(CRuinsLeftToCRuinsRight);
	mPortals[CRuinsLeftToCRuinsRight]->setWorking(true);
	Level::load();
}

void Level_Cavern_Ruins_Left::unload()
{
	Level::unload();
}

void Level_Cavern_Ruins_Left::changeLevel()
{
	if (mPortals[CRuinsLeftToCRuinsRight]->getActivated() && mPortals[CRuinsLeftToCRuinsRight]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Cavern_Ruins_Right);
	}
}

void Level_Cavern_Ruins_Left::checkInteractEvents()
{

}
void Level_Cavern_Ruins_Left::checkEvents()
{

}
