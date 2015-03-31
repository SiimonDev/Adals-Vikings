#include "Level_Cliffs_Up.h"
#include "..\Logics\AudioPlayer.h"
#include <iostream>

Level_Cliffs_Up::Level_Cliffs_Up(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Cliffs_Up;
}

void Level_Cliffs_Up::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Cliffs_Ambient, true, mAmbientSoundLevel);
	AudioPlayer::playHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music, true, mMusicSoundLevel);

}

void Level_Cliffs_Up::update(sf::Time &frametime)
{
	if (Act1Events::hasBeenTriggered(Act1Event::CliffsMonologue) && !Act1Events::hasBeenHandled(Act1Event::CliffsMonologue))
	{
		if (!DialogHandler::getDialogue("Ulfr_Cliffs").getActiveConversation() && !DialogHandler::getDialogue("Ulfr_Cliffs").getHasStopped())
			DialogHandler::startDialogue("Ulfr_Cliffs");

		if (DialogHandler::getDialogue("Ulfr_Cliffs").getHasStopped())
			Act1Events::handleEvent(Act1Event::CliffsMonologue);
	}

	Level::update(frametime);
	changeLevel(frametime);
}

void Level_Cliffs_Up::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Cliffs_Up::load()
{
	mPortals[CliffsToGates] = &PortalLoader::getPortal(CliffsToGates);
	mPortals[CliffsTopToCliffsBottom] = &PortalLoader::getPortal(CliffsTopToCliffsBottom);
	mPortals[CliffsToRuins] = &PortalLoader::getPortal(CliffsToRuins);
	mPortals[CliffsToRuins]->setWorking(true);
	mPortals[CliffsToGates]->setWorking(true);
	mPortals[CliffsTopToCliffsBottom]->setWorking(true);

	if (Act1Events::hasBeenHandled(Act1Event::MinedSomeGold))
	{
		mPortals[CliffsToRuins]->setCannotDialogue("Uhh... it looks rather... collapsed");
		mPortals[CliffsToRuins]->setWorking(false);
	}

	Level::load();
}

void Level_Cliffs_Up::unload()
{
	Level::unload();
}

void Level_Cliffs_Up::changeLevel(sf::Time &frametime)
{
	if (mPortals[CliffsToGates]->getActivated() && mPortals[CliffsToGates]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::City_Gates);
		AudioPlayer::stopHDDSound(HDDSound::Cliffs_Ambient);
		AudioPlayer::stopHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music);
		mRestartSounds = true;
	}
	if (mPortals[CliffsTopToCliffsBottom]->getActivated() && mPortals[CliffsTopToCliffsBottom]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Cliffs_Down);
	}
	if (mPortals[CliffsToRuins]->getActivated() && mPortals[CliffsToRuins]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Ruins);
		AudioPlayer::stopHDDSound(HDDSound::Cliffs_Ambient);
		AudioPlayer::stopHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music);
		mRestartSounds = true;
	}
}

void Level_Cliffs_Up::checkInteractEvents()
{

}
void Level_Cliffs_Up::checkEvents()
{

}
