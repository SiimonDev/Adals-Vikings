#include "Level_Cliffs_Down.h"
#include <iostream>

Level_Cliffs_Down::Level_Cliffs_Down(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
	, mCannotGo(false)
{
	mBackgroundID = LevelFolder::Cliffs_Down;
}

void Level_Cliffs_Down::restartSounds()
{

}

void Level_Cliffs_Down::update(sf::Time &frametime)
{
	if (!Act1Events::hasBeenHandled(Act1Event::GotCandleLight))
		Act1Events::handleEvent(Act1Event::GotCandleLight);
	if (!Act1Events::hasBeenHandled(Act1Event::GivenSleepingMeatToWolf))
	{
		DialogHandler::getDialogue("Miner_Cavern").enableOption(3);
		Act1Events::handleEvent(Act1Event::GivenSleepingMeatToWolf);
	}
	if (!mCannotGo)
	{
		if (Act1Events::hasBeenHandled(Act1Event::TooDarkToGo))
		{
			mPortals[CliffsToCaverns]->setWorking(false);
			mPortals[CliffsToCaverns]->setCannotDialogue("It's too dark to go in there, I need to find something to make it brighter.");
			mCannotGo = true;
		}
	}
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
		}
	}
	else
	{
		if (mPortals[CliffsToCRuins]->getActivated() && mPortals[CliffsToCRuins]->getWorking())
		{
			LVLMI.changeLevel(LevelFolder::Cavern_Ruins_Right);
		}
	}
}

void Level_Cliffs_Down::checkInteractEvents()
{

}
void Level_Cliffs_Down::checkEvents()
{
}
