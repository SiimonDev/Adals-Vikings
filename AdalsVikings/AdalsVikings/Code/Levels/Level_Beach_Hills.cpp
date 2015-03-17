#include "Level_Beach_Hills.h"
#include <iostream>

Level_Beach_Hills::Level_Beach_Hills(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Beach_Hills;
}

void Level_Beach_Hills::restartSounds()
{

}

void Level_Beach_Hills::update(sf::Time &frametime)
{
	Level::update(frametime);
	changeLevel();
}

void Level_Beach_Hills::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Beach_Hills::load()
{

	mPortals[HillBeachToBeach] = &PortalLoader::getPortal(HillBeachToBeach);
	mPortals[HillBeachToBeach]->setWorking(true);
	Level::load();
}

void Level_Beach_Hills::unload()
{
	Level::unload();
}

void Level_Beach_Hills::changeLevel()
{
	if (mPortals[HillBeachToBeach]->getActivated() && mPortals[HillBeachToBeach]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Beach);
	}
}

void Level_Beach_Hills::checkInteractEvents()
{

}
void Level_Beach_Hills::checkEvents()
{

}
