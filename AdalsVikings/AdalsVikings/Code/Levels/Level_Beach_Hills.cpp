#include "Level_Beach_Hills.h"
#include "..\Logics\AudioPlayer.h"
#include "..\Logics\WindowState.h"
#include <iostream>

Level_Beach_Hills::Level_Beach_Hills(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel), mVideoPlayed(false)
{
	mBackgroundID = LevelFolder::Beach_Hills;
}

void Level_Beach_Hills::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Beach_Ambient, true, mAmbientSoundLevel);
	AudioPlayer::playHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music, true, mMusicSoundLevel);
}

void Level_Beach_Hills::update(sf::Time &frametime)
{
	if (!Act1Events::hasBeenHandled(Act1Event::BeachHillVideo))
	{
		mUpHillVideo.openFromFile("assets/video/up_hill_x264_720p.avi", "assets/video/Up_hill_sound.ogg");
		mUpHillVideo.setSize(1920, 1080);
		mUpHillVideo.play();
		Act1Events::handleEvent(Act1Event::BeachHillVideo);
	}
	else if (mUpHillVideo.getStatus() != sf::VideoFile::Playing || !mUpHillVideo.isLoaded())
	{
		Level::update(frametime);
		changeLevel();
	}
	else
		mUpHillVideo.update(frametime);
}

void Level_Beach_Hills::render(IndexRenderer &iRenderer)
{
	if ((mUpHillVideo.getStatus() != sf::VideoFile::Playing || !mUpHillVideo.isLoaded()) && !mVideoPlayed)
		Level::render(iRenderer);
	else
		mUpHillVideo.render(CurrentWindow);
}

void Level_Beach_Hills::load()
{
	mPortals[HillBeachToBeach] = &PortalLoader::getPortal(HillBeachToBeach);
	mPortals[HillBeachToBeach]->setWorking(true);
	Level::load();
}

void Level_Beach_Hills::unload()
{
	Level::unload();
}

void Level_Beach_Hills::changeLevel()
{
	if (mPortals[HillBeachToBeach]->getActivated() && mPortals[HillBeachToBeach]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Beach);
		AudioPlayer::stopHDDSound(HDDSound::Beach_Ambient);
		mRestartSounds = true;
	}
}

void Level_Beach_Hills::checkInteractEvents()
{

}
void Level_Beach_Hills::checkEvents()
{

}
