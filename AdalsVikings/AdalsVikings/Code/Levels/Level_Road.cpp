#include "Level_Road.h"
#include "..\Logics\AudioPlayer.h"
#include "Level_Beach.h"
#include <iostream>

Level_Road::Level_Road(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Road;
}

void Level_Road::update(sf::Time &frametime)
{
	if (Act1Events::hasBeenTriggered(Act1Event::Road_StartMailmanConv) && !Act1Events::hasBeenHandled(Act1Event::Road_StartMailmanConv))
	{
		if (!DialogHandler::getDialogue("Mailman_Road").getActiveConversation() && !DialogHandler::getDialogue("Mailman_Road").getHasStopped())
		{
			mNpcs["Mailman"]->setIndex(21);
			DialogHandler::startDialogue("Mailman_Road");
		}
		else if (DialogHandler::getDialogue("Mailman_Road").getHasStopped())
			Act1Events::handleEvent(Act1Event::Road_StartMailmanConv);
	}

	if (Act1Events::hasBeenTriggered(Act1Event::Road_GiveMailmanPaper) && !Act1Events::hasBeenHandled(Act1Event::Road_GiveMailmanPaper))
	{
		if (!DialogHandler::getDialogue("GiveScroll_Road").getActiveConversation() && !DialogHandler::getDialogue("GiveScroll_Road").getHasStopped())
		{
			mPlayer.removeItemFromInventory("scroll");
			DialogHandler::startDialogue("GiveScroll_Road");
		}
		else if (DialogHandler::getDialogue("GiveScroll_Road").getHasStopped() && !mFade1)
		{
			FadeI.fadeOut(frametime);
			if (FadeI.getFaded())
			{
				mPortals[RoadToOutside_Chuch]->setWorking(true);
				mPortals[RoadToForestRoad]->setCannotDialogue("I can see brynja over there... I would rather not talk to her right now");
				mNpcs.erase("Mailman");
				mFade1 = true;
			}
		}
		else if (!mFade2 && mFade1)
		{
			FadeI.fadeIn(frametime);
			if (FadeI.getFaded())
				mFade1 = true;
		}
	}

	changeLevel();
	Level::update(frametime);
}

void Level_Road::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Road::load()
{
	mPortals[RoadToBeach] = &PortalLoader::getPortal(RoadToBeach);
	mPortals[RoadToOutside_Chuch] = &PortalLoader::getPortal(RoadToOutside_Chuch);
	mPortals[RoadToForestRoad] = &PortalLoader::getPortal(RoadToForestRoad);
	mPortals[RoadToCamp] = &PortalLoader::getPortal(RoadToCamp);

	mPortals[RoadToBeach]->setWorking(true);
	mPortals[RoadToCamp]->setWorking(true);

	if (!Act1Events::hasBeenHandled(Act1Event::Enter_Road))
	{
		mPortals[RoadToOutside_Chuch]->setCannotDialogue("I Should probably help find that scroll first...");
		mPortals[RoadToForestRoad]->setCannotDialogue("I Should probably help find that scroll first...");

		mNpcs["Mailman"] = NpcPtr(new Npc(NpcHandler::getNpc("Mailman")));
		mNpcs["Mailman"]->setDialogue("Mailman_Road");
	}
	else if (Act1Events::hasBeenHandled(Act1Event::Road_GiveMailmanPaper))
	{
		mPortals[RoadToOutside_Chuch]->setWorking(true);
		mPortals[RoadToForestRoad]->setCannotDialogue("I can see brynja over there... I would rather not talk to her right now");
	}

	Level::load();
}

void Level_Road::unload()
{
	Level::unload();
}

void Level_Road::changeLevel()
{
	if (mPortals[RoadToBeach]->getActivated() && mPortals[RoadToBeach]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Beach);
	}
	else if (mPortals[RoadToOutside_Chuch]->getActivated() && mPortals[RoadToOutside_Chuch]->getWorking())
		LVLMI.changeLevel(LevelFolder::Church_Outside);
	else if (mPortals[RoadToForestRoad]->getActivated() && mPortals[RoadToForestRoad]->getWorking())
		LVLMI.changeLevel(LevelFolder::Forest_Road);
	if (mPortals[RoadToCamp]->getActivated() && mPortals[RoadToCamp]->getWorking())
		LVLMI.changeLevel(LevelFolder::Camp_Clearing);
}
void Level_Road::checkInteractEvents()
{
	if (mDroppedItemID == "scroll" && mCurrentNPCID == "Mailman" && !Act1Events::hasBeenTriggered(Act1Event::Road_GiveMailmanPaper))
		Act1Events::triggerEvent(Act1Event::Road_GiveMailmanPaper);
}
void Level_Road::checkEvents()
{
	if (Act1Events::hasBeenTriggered(Act1Event::Enter_Road) && !Act1Events::hasBeenHandled(Act1Event::Enter_Road) && mPlayer.getPosition().y <= 970)
	{
		Act1Events::handleEvent(Act1Event::Enter_Road);
		Act1Events::triggerEvent(Act1Event::Road_StartMailmanConv);
	}
}

//void Level_Road::setNearbyLevels()
//{
//	for (std::map<LevelFolder::ID, LevelPtr>::iterator it = LVLMI.getCurrentLevels().begin(); it != LVLMI.getCurrentLevels().end(); ++it)
//	{
//		if (it->first == LevelFolder::Forest_Road || it->first == LevelFolder::Church_Outside || it->first == LevelFolder::Beach)
//			it->second->setIsNearbyLevel(true);
//		else
//			it->second->setIsNearbyLevel(false);
//	}
//}
