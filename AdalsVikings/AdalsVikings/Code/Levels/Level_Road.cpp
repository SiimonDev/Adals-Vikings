#include "Level_Road.h"
#include "..\Logics\AudioPlayer.h"
#include "Level_Beach.h"
#include <iostream>

Level_Road::Level_Road(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Road;
}

void Level_Road::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Road_Ambient, true, 20);
	AudioPlayer::playHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music, true, 20);
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

	if (Act1Events::hasBeenTriggered(Act1Event::AfterCampRoad_Conversation) && !Act1Events::hasBeenHandled(Act1Event::AfterCampRoad_Conversation))
	{
		if (!mHasSpawned)
		{
			mPlayer->setPosition(sf::Vector2f(710, 635));
			mPlayer->setFlip(true);
			mPlayer->UpdateAnimationStyle();
			mNpcs["Leifr"]->setPosition(sf::Vector2f(545, 700));
			mNpcs["Valdis"]->setPosition(sf::Vector2f(665, 715));
			mNpcs["Alfr"]->setPosition(sf::Vector2f(895, 705));
			mNpcs["Finnr"]->setPosition(sf::Vector2f(970, 710));

			mNpcs["Leifr"]->setFlip(true);
			mNpcs["Valdis"]->setFlip(true);
			mNpcs["Alfr"]->setFlip(false);
			mNpcs["Finnr"]->setFlip(false);

			mNpcs["Leifr"]->updateAnimationStyle();
			mNpcs["Valdis"]->updateAnimationStyle();
			mNpcs["Alfr"]->updateAnimationStyle();
			mNpcs["Finnr"]->updateAnimationStyle();

			mHasSpawned = true;
		}
		if (!mFade3)
		{
			FadeI.fadeIn(frametime);
			if (FadeI.getFaded())
			{
				DialogHandler::getDialogue("All_Road").startDialogue();
				mFade3 = true;
			}
		}
		if (DialogHandler::getDialogue("All_Road").getHasStopped() && !mFade4)
		{
			FadeI.fadeOut(frametime);
			if (FadeI.getFaded())
			{
				mNpcs.clear();
				mFade4 = true;
			}
		}
		if (mFade4 && !mFade5)
		{
			FadeI.fadeIn(frametime);
			if (FadeI.getFaded())
			{
				mFade5 = true;
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
	if (Act1Events::hasBeenHandled(Act1Event::ForestCamp_BeerDeer))
	{
		mNpcs["Leifr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Leifr")));
		mNpcs["Valdis"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Valdis")));
		mNpcs["Alfr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Alfr")));
		mNpcs["Finnr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Finnr")));

		mNpcs["Leifr"]->setScale(sf::Vector2f(0.25, 0.25));
		mNpcs["Valdis"]->setScale(sf::Vector2f(0.35, 0.35));
		mNpcs["Alfr"]->setScale(sf::Vector2f(0.35, 0.35));
		mNpcs["Finnr"]->setScale(sf::Vector2f(0.35, 0.35));

		mNpcs["Leifr"]->setPosition(sf::Vector2f(2000, 500));
		mNpcs["Valdis"]->setPosition(sf::Vector2f(2000, 500));
		mNpcs["Alfr"]->setPosition(sf::Vector2f(2000, 500));
		mNpcs["Finnr"]->setPosition(sf::Vector2f(2000, 500));

		mNpcs["Leifr"]->setDialogue("All_Road");
		mNpcs["Valdis"]->setDialogue("All_Road");
		mNpcs["Alfr"]->setDialogue("All_Road");
		mNpcs["Finnr"]->setDialogue("All_Road");

	}
	
	mPortals[RoadToCamp] = &PortalLoader::getPortal(RoadToCamp);

	mPortals[RoadToBeach] = &PortalLoader::getPortal(RoadToBeach);
	mPortals[RoadToOutside_Chuch] = &PortalLoader::getPortal(RoadToOutside_Chuch);
	mPortals[RoadToFarm] = &PortalLoader::getPortal(RoadToFarm);
	mPortals[RoadToGates] = &PortalLoader::getPortal(RoadToGates);

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

			mNpcs["Mailman"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Mailman")));
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
		if (Act1Events::hasBeenHandled(Act1Event::ForestCamp_BeerDeer))
		{
			mPortals[RoadToBeach]->setWorking(true);
			mPortals[RoadToFarm]->setWorking(true);
			mPortals[RoadToOutside_Chuch]->setWorking(true);
			mPortals[RoadToCamp]->setWorking(false);
			mPortals[RoadToCamp]->setCannotDialogue("If I go back there Brandr will kill me...");
			mPortals[RoadToGates]->setWorking(true);
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
		AudioPlayer::stopHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music);
		mRestartSounds = true;
	}
	else if (mPortals[RoadToFarm]->getActivated() && mPortals[RoadToFarm]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Farm_1);
		AudioPlayer::stopHDDSound(HDDSound::Road_Ambient);
		AudioPlayer::stopHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music);
		mRestartSounds = true;
	}
	if (mPortals[RoadToCamp]->getActivated() && mPortals[RoadToCamp]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Camp_Clearing);
		AudioPlayer::stopHDDSound(HDDSound::Road_Ambient);
		AudioPlayer::stopHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music);
		mRestartSounds = true;
	}
	if (mPortals[RoadToGates]->getActivated() && mPortals[RoadToGates]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::City_Gates);
		AudioPlayer::stopHDDSound(HDDSound::Road_Ambient);
		AudioPlayer::stopHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music);
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

	if (!Act1Events::hasBeenTriggered(Act1Event::AfterCampRoad_Conversation) && Act1Events::hasBeenHandled(Act1Event::CampFinished_Conversation))
	{
		Act1Events::triggerEvent(Act1Event::AfterCampRoad_Conversation);
	}
}