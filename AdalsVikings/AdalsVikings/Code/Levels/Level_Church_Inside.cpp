#include "Level_Church_Inside.h"
#include <iostream>

Level_Church_Inside::Level_Church_Inside(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Church_Inside;
}

void Level_Church_Inside::update(sf::Time &frametime)
{
	changeLevel();
	Level::update(frametime);
}

void Level_Church_Inside::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Church_Inside::load()
{
	Level::load();
}

void Level_Church_Inside::unload()
{
	Level::unload();
}

void Level_Church_Inside::changeLevel()
{
}

void Level_Church_Inside::checkInteractEvents()
{

}

void Level_Church_Inside::checkEvents()
{

}

void Level_Church_Inside::setNearbyLevels()
{
	for (std::map<LevelFolder::ID, LevelPtr>::iterator it = LVLMI.getCurrentLevels().begin(); it != LVLMI.getCurrentLevels().end(); ++it)
	{
		if (it->first == LevelFolder::Church_Outside)
			it->second->setIsNearbyLevel(true);
		else
			it->second->setIsNearbyLevel(false);
	}
}
