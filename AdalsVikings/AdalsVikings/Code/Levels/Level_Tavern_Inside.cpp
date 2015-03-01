#include "Level_Tavern_Inside.h"
#include <iostream>

Level_Tavern_Inside::Level_Tavern_Inside(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Tavern_Inside;
}

void Level_Tavern_Inside::update(sf::Time &frametime)
{
	changeLevel();
	Level::update(frametime);
}

void Level_Tavern_Inside::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Tavern_Inside::load()
{
	Level::load();
}

void Level_Tavern_Inside::unload()
{
	Level::unload();
}

void Level_Tavern_Inside::changeLevel()
{
}

void Level_Tavern_Inside::checkInteractEvents()
{

}
void Level_Tavern_Inside::checkEvents()
{

}

void Level_Tavern_Inside::setNearbyLevels()
{
	for (std::map<LevelFolder::ID, LevelPtr>::iterator it = LVLMI.getCurrentLevels().begin(); it != LVLMI.getCurrentLevels().end(); ++it)
	{
		if (it->first == LevelFolder::Tavern_Outside)
			it->second->setIsNearbyLevel(true);
		else
			it->second->setIsNearbyLevel(false);
	}
}
