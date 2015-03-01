#include "Level_Church_Outside.h"
#include <iostream>

Level_Church_Outside::Level_Church_Outside(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Church_Outside;
}

void Level_Church_Outside::update(sf::Time &frametime)
{
	if (Act1Events::hasBeenTriggered(Act1Event::ChurchOutside_TalkToPrincess) && !Act1Events::hasBeenHandled(Act1Event::ChurchOutside_TalkToPrincess))
	{
		if (DialogHandler::getDialogue("Princess_ChurchOutside").getHasStopped() && !mFade1)
		{
			FadeI.fadeOut(frametime);
			if (FadeI.getFaded())
			{
				mNpcs.erase("Princess");
				mFade1 = true;
			}
		}
		else if (!mFade2 && mFade1)
		{
			FadeI.fadeIn(frametime);
			if (FadeI.getFaded())
			{
				mFade2 = true;
				Act1Events::handleEvent(Act1Event::ChurchOutside_TalkToPrincess);
			}
		}
	}
	changeLevel();
	Level::update(frametime);
}

void Level_Church_Outside::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Church_Outside::load()
{
	mNpcs["Princess"] = NpcPtr(new Npc(NpcHandler::getNpc("Princess")));
	mNpcs["Princess"]->setDialogue("Princess_ChurchOutside");
	mPortals[Outside_ChurchToRoad] = &PortalLoader::getPortal(Outside_ChurchToRoad);
	mPortals[Outside_ChurchToChurch] = &PortalLoader::getPortal(Outside_ChurchToChurch);

	mPortals[Outside_ChurchToRoad]->setWorking(true);
	mPortals[Outside_ChurchToChurch]->setWorking(true);
	Level::load();
}

void Level_Church_Outside::unload()
{
	Level::unload();
}

void Level_Church_Outside::changeLevel()
{
	if (mPortals[Outside_ChurchToRoad]->getActivated() && mPortals[Outside_ChurchToRoad]->getWorking())
		LVLMI.changeLevel(LevelFolder::Road);
	else if (mPortals[Outside_ChurchToChurch]->getActivated() && mPortals[Outside_ChurchToChurch]->getWorking())
		LVLMI.changeLevel(LevelFolder::Church_Inside);
}

void Level_Church_Outside::checkInteractEvents()
{

}

void Level_Church_Outside::checkEvents()
{
	if (DialogHandler::getDialogue("Princess_ChurchOutside").getActiveConversation() && !Act1Events::hasBeenTriggered(Act1Event::ChurchOutside_TalkToPrincess))
		Act1Events::triggerEvent(Act1Event::ChurchOutside_TalkToPrincess);
}

void Level_Church_Outside::setNearbyLevels()
{
	for (std::map<LevelFolder::ID, LevelPtr>::iterator it = LVLMI.getCurrentLevels().begin(); it != LVLMI.getCurrentLevels().end(); ++it)
	{
		if (it->first == LevelFolder::Church_Inside || it->first == LevelFolder::Road)
			it->second->setIsNearbyLevel(true);
		else
			it->second->setIsNearbyLevel(false);
	}
}
