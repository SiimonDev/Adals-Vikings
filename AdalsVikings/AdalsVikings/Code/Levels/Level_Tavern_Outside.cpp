#include "Level_Tavern_Outside.h"
#include "..\Logics\AudioPlayer.h"
#include <iostream>

Level_Tavern_Outside::Level_Tavern_Outside(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Tavern_Outside;
}

void Level_Tavern_Outside::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Tavern_Outside_Ambient, true, 20);
}

void Level_Tavern_Outside::update(sf::Time &frametime)
{
	Level::update(frametime);
	changeLevel();
}

void Level_Tavern_Outside::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Tavern_Outside::load()
{
	RMI.loadResource(Footsteps::Dirt);
	mPortals[TavernOutsideToBeach] = &PortalLoader::getPortal(TavernOutsideToBeach);
	mPortals[TavernOutsideToTavernInside] = &PortalLoader::getPortal(TavernOutsideToTavernInside);
	mPortals[TavernOutsideToTavernInside]->setWorking(true);
	mPortals[TavernOutsideToBeach]->setWorking(true);
	Level::load();
	mCurrentFootsteps = Footsteps::Dirt;
}

void Level_Tavern_Outside::unload()
{
	RMI.unloadResource(Footsteps::Dirt);
	Level::unload();
}

void Level_Tavern_Outside::changeLevel()
{
	if (mPortals[TavernOutsideToBeach]->getActivated() && mPortals[TavernOutsideToBeach]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Beach);
		AudioPlayer::stopHDDSound(HDDSound::Tavern_Outside_Ambient);
		mRestartSounds = true;
	}
	else if (mPortals[TavernOutsideToTavernInside]->getActivated() && mPortals[TavernOutsideToTavernInside]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Tavern_Inside);
		AudioPlayer::stopHDDSound(HDDSound::Tavern_Outside_Ambient);
		mRestartSounds = true;
	}
}

void Level_Tavern_Outside::checkInteractEvents()
{

}

void Level_Tavern_Outside::checkEvents()
{

}