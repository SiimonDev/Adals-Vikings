#include "Level_Forest_Road.h"
#include "..\Logics\AudioPlayer.h"
#include <iostream>

Level_Forest_Road::Level_Forest_Road(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Forest_Road;
}

void Level_Forest_Road::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Forest_Road_Ambient, true, mAmbientSoundLevel);
	AudioPlayer::playHDDSound(HDDSound::Forest_Music, true, mMusicSoundLevel);
}

void Level_Forest_Road::update(sf::Time &frametime)
{
	if (Act1Events::hasBeenTriggered(Act1Event::ForestRoadConver) && !Act1Events::hasBeenHandled(Act1Event::ForestRoadConver))
	{
		if (!DialogHandler::getDialogue("Ulfr_ForestRoad").getActiveConversation() && !DialogHandler::getDialogue("Ulfr_ForestRoad").getHasStopped())
			DialogHandler::startDialogue("Ulfr_ForestRoad");

		if (DialogHandler::getDialogue("Ulfr_ForestRoad").getHasStopped())
			Act1Events::handleEvent(Act1Event::ForestRoadConver);
	}
	Level::update(frametime);
	changeLevel();
}

void Level_Forest_Road::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Forest_Road::load()
{
	RMI.loadResource(Footsteps::Dirt);
	mPortals[ForestRoadToCamp] = &PortalLoader::getPortal(ForestRoadToCamp);
	mPortals[ForestRoadToForestCamp] = &PortalLoader::getPortal(ForestRoadToForestCamp);
	mPortals[ForestRoadToCamp]->setWorking(true);
	mPortals[ForestRoadToForestCamp]->setWorking(true);

	Level::load();

	mCurrentFootsteps = Footsteps::Dirt;
}

void Level_Forest_Road::unload()
{
	RMI.unloadResource(Footsteps::Dirt);
	mPortals.erase(ForestRoadToCamp);
	Level::unload();
}

void Level_Forest_Road::changeLevel()
{
	if (mPortals[ForestRoadToCamp]->getActivated() && mPortals[ForestRoadToCamp]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Camp_Clearing);
		AudioPlayer::stopHDDSound(HDDSound::Forest_Road_Ambient);
		AudioPlayer::stopHDDSound(HDDSound::Forest_Music);
		mRestartSounds = true;
	}
	else if (mPortals[ForestRoadToForestCamp]->getActivated() && mPortals[ForestRoadToForestCamp]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Forest_Camp);
		AudioPlayer::stopHDDSound(HDDSound::Forest_Road_Ambient);
		mRestartSounds = true;
	}
}

void Level_Forest_Road::checkInteractEvents()
{

}
void Level_Forest_Road::checkEvents()
{
	if (Act1Events::hasBeenTriggered(Act1Event::ForestCamp_NeedFireQuest) && !Act1Events::hasBeenTriggered(Act1Event::ForestRoadConver))
		Act1Events::triggerEvent(Act1Event::ForestRoadConver);
}