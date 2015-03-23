#include "Level_Cavern_Ruins_Right.h"
#include "..\Logics\AudioPlayer.h"
#include <iostream>

Level_Cavern_Ruins_Right::Level_Cavern_Ruins_Right(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Cavern_Ruins_Right;
}

void Level_Cavern_Ruins_Right::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Forest_Music, true, mMusicSoundLevel);
	AudioPlayer::playHDDSound(HDDSound::Cavern_Ambient, true, mAmbientSoundLevel);
}

void Level_Cavern_Ruins_Right::update(sf::Time &frametime)
{
	if (Act1Events::hasBeenTriggered(Act1Event::MinedSomeGold) && !Act1Events::hasBeenHandled(Act1Event::MinedSomeGold))
	{
		if (!mFade1)
		{
			FadeI.fadeIn(frametime);
			if (FadeI.getFaded())
			{
				mFade1 = true;
			}
		}
		if (mFade1 && !DialogHandler::getDialogue("Destroyed_Cavern").getActiveConversation() && !DialogHandler::getDialogue("Destroyed_Cavern").getHasStopped())
			DialogHandler::startDialogue("Destroyed_Cavern");

		if (DialogHandler::getDialogue("Destroyed_Cavern").getHasStopped())
		{
			Act1Events::handleEvent(Act1Event::MinedSomeGold);
		}
	}

	Level::update(frametime);
	changeLevel();
}

void Level_Cavern_Ruins_Right::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Cavern_Ruins_Right::load()
{

	mPortals[CRuinsToCLiffs] = &PortalLoader::getPortal(CRuinsToCLiffs);
	mPortals[CRuinsRightToCRuinsLeft] = &PortalLoader::getPortal(CRuinsRightToCRuinsLeft);
	mPortals[CRuinsRightToCRuinsLeft]->setWorking(true);
	mPortals[CRuinsToCLiffs]->setWorking(true);
	Level::load();
}

void Level_Cavern_Ruins_Right::unload()
{
	Level::unload();
}

void Level_Cavern_Ruins_Right::changeLevel()
{
	if (mPortals[CRuinsToCLiffs]->getActivated() && mPortals[CRuinsToCLiffs]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Cliffs_Down);
		AudioPlayer::stopHDDSound(HDDSound::Forest_Music);
		AudioPlayer::stopHDDSound(HDDSound::Cavern_Ambient);
		mRestartSounds = true;
	}
	if (mPortals[CRuinsRightToCRuinsLeft]->getActivated() && mPortals[CRuinsRightToCRuinsLeft]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Cavern_Ruins_Left);
	}
}

void Level_Cavern_Ruins_Right::checkInteractEvents()
{

}
void Level_Cavern_Ruins_Right::checkEvents()
{

}
