#include "Level_Road.h"
#include "..\Logics\AudioPlayer.h"
#include "Level_Beach.h"
#include <iostream>

Level_Road::Level_Road(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Road;
}

void Level_Road::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Road_Ambient, true, 20);
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
			mPlayer->removeItemFromInventory("scroll");
			DialogHandler::startDialogue("GiveScroll_Road");
		}
		else if (DialogHandler::getDialogue("GiveScroll_Road").getHasStopped() && !mFade1)
		{
			FadeI.fadeOut(frametime);
			if (FadeI.getFaded())
			{
				mPortals[RoadToOutside_Chuch]->setWorking(true);
				mPortals[RoadToCamp]->setCannotDialogue("I can see brynja over there... I would rather not talk to her before I've finished my mission.");
				mPortals[RoadToFarm]->setCannotDialogue("Uh, if I don't do as Brandr told me, he is literally  going to kill me.");
				mNpcs.erase("Mailman");
				mFade1 = true;
			}
		}
		else if (!mFade2 && mFade1)
		{
			FadeI.fadeIn(frametime);
			if (FadeI.getFaded())
			{
				Act1Events::handleEvent(Act1Event::Road_GiveMailmanPaper);
				mFade1 = true;
			}
		}
	}

	Level::update(frametime);
	changeLevel();
}

void Level_Road::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Road::load()
{
	mRestartSounds = true;
	RMI.loadResource(Footsteps::Dirt);
	mPortals[RoadToBeach] = &PortalLoader::getPortal(RoadToBeach);
	mPortals[RoadToOutside_Chuch] = &PortalLoader::getPortal(RoadToOutside_Chuch);
	mPortals[RoadToFarm] = &PortalLoader::getPortal(RoadToFarm);
	mPortals[RoadToCamp] = &PortalLoader::getPortal(RoadToCamp);

	mPortals[RoadToBeach]->setWorking(true);

	/* Debug */
	//mPortals[RoadToOutside_Chuch]->setWorking(true);
	//mPortals[RoadToCamp]->setWorking(true);
	/* ===== */

	if (!Act1Events::hasBeenHandled(Act1Event::Enter_Road))
	{
		mPortals[RoadToOutside_Chuch]->setCannotDialogue("I Should probably help find that scroll first...");
		mPortals[RoadToFarm]->setCannotDialogue("I Should probably help find that scroll first...");
		mPortals[RoadToCamp]->setCannotDialogue("I Should probably help find that scroll first...");

		mNpcs["Mailman"] = NpcPtr(new Npc(NpcHandler::getNpc("Mailman")));
		mNpcs["Mailman"]->setDialogue("Mailman_Road");
	}
	
	if (Act1Events::hasBeenHandled(Act1Event::Road_GiveMailmanPaper))
	{
		mPortals[RoadToOutside_Chuch]->setWorking(true);
		mPortals[RoadToCamp]->setCannotDialogue("I can see brynja over there... I would rather not talk to her before I've finished my mission.");
		mPortals[RoadToFarm]->setCannotDialogue("Uh, if I don't do as Brandr told me, he is literally  going to kill me.");
	}
	if (Act1Events::hasBeenTriggered(Act1Event::ChurchInside_GoBackDialogue))
	{
		mPortals[RoadToFarm]->setCannotDialogue("I should report to Brynja before I start exploring...");
		mPortals[RoadToCamp]->setWorking(true);
	}

	Level::load();
	mCurrentFootsteps = Footsteps::Dirt;
}

void Level_Road::unload()
{
	RMI.unloadResource(Footsteps::Dirt);
	Level::unload();
}

void Level_Road::changeLevel()
{
	if (mPortals[RoadToBeach]->getActivated() && mPortals[RoadToBeach]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Beach);
		AudioPlayer::stopHDDSound(HDDSound::Road_Ambient);
		mRestartSounds = true;
	}
	else if (mPortals[RoadToOutside_Chuch]->getActivated() && mPortals[RoadToOutside_Chuch]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Church_Outside);
		AudioPlayer::stopHDDSound(HDDSound::Road_Ambient);
		mRestartSounds = true;
	}
	else if (mPortals[RoadToFarm]->getActivated() && mPortals[RoadToFarm]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Forest_Road);
		AudioPlayer::stopHDDSound(HDDSound::Road_Ambient);
		mRestartSounds = true;
	}
	if (mPortals[RoadToCamp]->getActivated() && mPortals[RoadToCamp]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Camp_Clearing);
		AudioPlayer::stopHDDSound(HDDSound::Road_Ambient);
		mRestartSounds = true;
	}
}
void Level_Road::checkInteractEvents()
{
	if (mDroppedItemID == "scroll" && mCurrentNPCID == "Mailman" && !Act1Events::hasBeenTriggered(Act1Event::Road_GiveMailmanPaper))
		Act1Events::triggerEvent(Act1Event::Road_GiveMailmanPaper);
}
void Level_Road::checkEvents()
{
	if (Act1Events::hasBeenTriggered(Act1Event::Enter_Road) && !Act1Events::hasBeenHandled(Act1Event::Enter_Road) && mPlayer->getPosition().y <= 970)
	{
		Act1Events::handleEvent(Act1Event::Enter_Road);
		Act1Events::triggerEvent(Act1Event::Road_StartMailmanConv);
	}
}