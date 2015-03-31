#include "Level_Cliffs_Down.h"
#include "..\Logics\AudioPlayer.h"
#include <iostream>

static Animation mWaveAnimation;
static Animation mWaveAnimationIdle;

Level_Cliffs_Down::Level_Cliffs_Down(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
	, mCannotGo(false)
{
	mBackgroundID = LevelFolder::Cliffs_Down;
}

void Level_Cliffs_Down::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Cliffs_Ambient, true, mAmbientSoundLevel);
	AudioPlayer::playHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music, true, mMusicSoundLevel);
}

void Level_Cliffs_Down::update(sf::Time &frametime)
{
	if (!mCannotGo)
	{
		if (Act1Events::hasBeenHandled(Act1Event::TooDarkToGo))
		{
			mPortals[CliffsToCaverns]->setWorking(false);
			mPortals[CliffsToCaverns]->setCannotDialogue("It's too dark to go in there, I need to find something to make it brighter.");
			mCannotGo = true;
		}
	}

	if (mWaveAnimation.getCurrentFrame() == 1)
		AudioPlayer::playHDDSound(HDDSound::Cliffs_Wave, false, 20);

	mWaveAnimation.animate(frametime);
	mWaveAnimationIdle.animate(frametime);
	Level::update(frametime);
	changeLevel(frametime);
}
void Level_Cliffs_Down::render(IndexRenderer &iRenderer)
{
	if (mWaveAnimation.getCurrentFrame() == 0)
		mWaveAnimationIdle.render(iRenderer);
	else
		mWaveAnimation.render(iRenderer);
	Level::render(iRenderer);
}

void Level_Cliffs_Down::load()
{
	
	mPortals[CliffsBottomToCliffsTop] = &PortalLoader::getPortal(CliffsBottomToCliffsTop);
	if (!Act1Events::hasBeenHandled(Act1Event::MinedSomeGold))
	{
		mPortals[CliffsToCaverns] = &PortalLoader::getPortal(CliffsToCaverns);
		mPortals[CliffsToCaverns]->setWorking(true);
	}
	else
	{
		mPortals[CliffsToCRuins] = &PortalLoader::getPortal(CliffsToCRuins);
		mPortals[CliffsToCRuins]->setWorking(true);
	}
	mPortals[CliffsBottomToCliffsTop]->setWorking(true);

	Level::load();

	RMI.loadResource(Texture::WaveAnimationCliffs);
	mWaveAnimation.load(RMI.getResource(Texture::WaveAnimationCliffs), sf::Vector2i(5, 10), sf::seconds(8), sf::seconds(7), true);
	mWaveAnimation.setIndex(4);
	mWaveAnimation.setProportions(sf::Vector2f(1940, 1120));
	mWaveAnimation.getSprite().setOrigin(mWaveAnimation.getSprite().getTextureRect().width, mWaveAnimation.getSprite().getTextureRect().height);
	mWaveAnimation.setPadding(2);
	mWaveAnimation.setPosition(sf::Vector2f(1920 + 20, 1080 + 20));

	RMI.loadResource(Texture::WaveAnimationCliffsIdle);
	mWaveAnimationIdle.load(RMI.getResource(Texture::WaveAnimationCliffsIdle), sf::Vector2i(5, 1), sf::seconds(1), sf::seconds(0), true);
	mWaveAnimationIdle.setIndex(4);
	mWaveAnimationIdle.setProportions(sf::Vector2f(1940, 1120));
	mWaveAnimationIdle.getSprite().setOrigin(mWaveAnimation.getSprite().getTextureRect().width, mWaveAnimation.getSprite().getTextureRect().height);
	mWaveAnimationIdle.setPadding(2);
	mWaveAnimationIdle.setPosition(sf::Vector2f(1920 + 20, 1080 + 20));

	if (Act1Events::hasBeenHandled(Act1Event::TooDarkToGo))
	{
		mPortals[CliffsToCaverns]->setWorking(false);
		mPortals[CliffsToCaverns]->setCannotDialogue("It's too dark to go in there, I need to find something to make it brighter.");
	}
	if (Act1Events::hasBeenHandled(Act1Event::GotCandleLight))
	{
		mPortals[CliffsToCaverns]->setWorking(true);
	}
}
void Level_Cliffs_Down::unload()
{
	RMI.unloadResource(Texture::WaveAnimationCliffs);
	RMI.unloadResource(Texture::WaveAnimationCliffsIdle);
	Level::unload();
}

void Level_Cliffs_Down::changeLevel(sf::Time &frametime)
{
	if (mPortals[CliffsBottomToCliffsTop]->getActivated() && mPortals[CliffsBottomToCliffsTop]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Cliffs_Up);
	}
	if (!Act1Events::hasBeenHandled(Act1Event::MinedSomeGold))
	{

		if (mPortals[CliffsToCaverns]->getActivated() && mPortals[CliffsToCaverns]->getWorking())
		{
			LVLMI.changeLevel(LevelFolder::Cavern_Right);
			AudioPlayer::stopHDDSound(HDDSound::Cliffs_Ambient);
			AudioPlayer::stopHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music);
			mRestartSounds = true;
		}
	}
	else
	{
		if (mPortals[CliffsToCRuins]->getActivated() && mPortals[CliffsToCRuins]->getWorking())
		{
			LVLMI.changeLevel(LevelFolder::Cavern_Ruins_Right);
			AudioPlayer::stopHDDSound(HDDSound::Cliffs_Ambient);
			AudioPlayer::stopHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music);
			mRestartSounds = true;
		}
	}
}

void Level_Cliffs_Down::checkInteractEvents()
{

}
void Level_Cliffs_Down::checkEvents()
{
}
