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
	mPortals[ChurchToOutside_Church] = &PortalLoader::getPortal(ChurchToOutside_Church);
	mPortals[ChurchToOutside_Church]->setWorking(true);

	mNpcs["Beor"] = NpcPtr(new Npc(NpcHandler::getNpc("Beor")));
	mNpcs["Beor"]->setDialogue("Beor_ChurchInside");

	Level::load();
}

void Level_Church_Inside::unload()
{
	Level::unload();
}

void Level_Church_Inside::changeLevel()
{
	if (mPortals[ChurchToOutside_Church]->getActivated() && mPortals[ChurchToOutside_Church]->getWorking() && !Act1Events::hasBeenTriggered(Act1Event::ChurchInside_GoBackDialogue) && DialogHandler::getDialogue("Beor_ChurchInside").getHasStopped())
	{
		Act1Events::triggerEvent(Act1Event::ChurchInside_GoBackDialogue);
		LVLMI.changeLevel(LevelFolder::Church_Outside);
	}
	else if (mPortals[ChurchToOutside_Church]->getActivated() && mPortals[ChurchToOutside_Church]->getWorking())
		LVLMI.changeLevel(LevelFolder::Church_Outside);
}

void Level_Church_Inside::checkInteractEvents()
{

}

void Level_Church_Inside::checkEvents()
{

}

//void Level_Church_Inside::setNearbyLevels()
//{
//	for (std::map<LevelFolder::ID, LevelPtr>::iterator it = LVLMI.getCurrentLevels().begin(); it != LVLMI.getCurrentLevels().end(); ++it)
//	{
//		if (it->first == LevelFolder::Church_Outside)
//			it->second->setIsNearbyLevel(true);
//		else
//			it->second->setIsNearbyLevel(false);
//	}
//}