#include "Level_Church_Outside.h"
#include "..\Logics\AudioPlayer.h"
#include <iostream>

Level_Church_Outside::Level_Church_Outside(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Church_Outside;
}

void Level_Church_Outside::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Church_Outside_Ambient, true, 100);
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

	if (Act1Events::hasBeenTriggered(Act1Event::ChurchInside_GoBackDialogue) && !Act1Events::hasBeenHandled(Act1Event::ChurchInside_GoBackDialogue))
	{
		if (!DialogHandler::getDialogue("GoBack_ChurchInside").getActiveConversation() && !DialogHandler::getDialogue("GoBack_ChurchInside").getHasStopped())
			DialogHandler::getDialogue("GoBack_ChurchInside").startDialogue();
		else if (DialogHandler::getDialogue("GoBack_ChurchInside").getHasStopped())
		{
			Act1Events::handleEvent(Act1Event::ChurchInside_GoBackDialogue);
		}
	}
	
	Level::update(frametime);
	changeLevel();
}

void Level_Church_Outside::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Church_Outside::load()
{
	RMI.loadResource(Footsteps::Dirt);
	mNpcs["Princess"] = NpcPtr(new Npc(NpcHandler::getNpc("Princess")));
	mNpcs["Princess"]->setDialogue("Princess_ChurchOutside");
	mPortals[Outside_ChurchToRoad] = &PortalLoader::getPortal(Outside_ChurchToRoad);
	mPortals[Outside_ChurchToChurch] = &PortalLoader::getPortal(Outside_ChurchToChurch);

	mPortals[Outside_ChurchToRoad]->setWorking(true);
	mPortals[Outside_ChurchToChurch]->setWorking(true);
	Level::load();
	mCurrentFootsteps = Footsteps::Dirt;
}

void Level_Church_Outside::unload()
{
	AudioPlayer::stopHDDSound(HDDSound::Church_Outside_Ambient);
	RMI.unloadResource(Footsteps::Dirt);
	Level::unload();
}

void Level_Church_Outside::changeLevel()
{
	if (mPortals[Outside_ChurchToRoad]->getActivated() && mPortals[Outside_ChurchToRoad]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Road);
		AudioPlayer::stopHDDSound(HDDSound::Church_Outside_Ambient);
		mRestartSounds = true;
	}
	else if (mPortals[Outside_ChurchToChurch]->getActivated() && mPortals[Outside_ChurchToChurch]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Church_Inside);
		AudioPlayer::stopHDDSound(HDDSound::Church_Outside_Ambient);
		mRestartSounds = true;
	}
}

void Level_Church_Outside::checkInteractEvents()
{

}

void Level_Church_Outside::checkEvents()
{
	if (DialogHandler::getDialogue("Princess_ChurchOutside").getActiveConversation() && !Act1Events::hasBeenTriggered(Act1Event::ChurchOutside_TalkToPrincess))
		Act1Events::triggerEvent(Act1Event::ChurchOutside_TalkToPrincess);
}