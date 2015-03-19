#include "Level_Cavern_Right.h"
#include "..\Logics\AudioPlayer.h"
#include <iostream>

Level_Cavern_Right::Level_Cavern_Right(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Cavern_Right;

	mDarkness.setSize(sf::Vector2f(1920, 1080));
	mDarkness.setFillColor(sf::Color(0, 0, 0, 200));
}

void Level_Cavern_Right::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Forest_Music, true, 20);
	AudioPlayer::playHDDSound(HDDSound::Cavern_Ambient, true, 20);
}

void Level_Cavern_Right::update(sf::Time &frametime)
{
	if (Act1Events::hasBeenTriggered(Act1Event::SweetGold) && !Act1Events::hasBeenHandled(Act1Event::SweetGold))
	{
		if (!DialogHandler::getDialogue("SweetGold_Cavern").getActiveConversation() && !DialogHandler::getDialogue("SweetGold_Cavern").getHasStopped())
			DialogHandler::startDialogue("SweetGold_Cavern");

		if (DialogHandler::getDialogue("SweetGold_Cavern").getHasStopped())
		{
			mPortals[CavernsToCliffs]->setWorking(false);
			mPortals[CavernsToCliffs]->setCannotDialogue("No, that gold solves everything! I need to mine it before I go!");
		}
	}
	if (Act1Events::hasBeenTriggered(Act1Event::MinedSomeGold) && !Act1Events::hasBeenHandled(Act1Event::MinedSomeGold))
	{
		if (!DialogHandler::getDialogue("Mining_Cavern").getActiveConversation() && !DialogHandler::getDialogue("Mining_Cavern").getHasStopped())
			DialogHandler::startDialogue("Mining_Cavern");

		if (DialogHandler::getDialogue("Mining_Cavern").getHasStopped())
		{
			if (!mFade1)
			{
				FadeI.fadeOut(frametime);
				
				if (FadeI.getFaded())
				{
					if (!FadeI.getWait())
					{
						AudioPlayer::playHDDSound(HDDSound::Cavern_Collapse, false);
						FadeI.setWaitDuration(sf::seconds(10));
					}
					FadeI.wait(frametime);
					if (FadeI.getFinishedWaiting())
					{
						LVLMI.changeLevel(LevelFolder::Cavern_Ruins_Right);
						mPlayer->setPosition(sf::Vector2f(1390, 645));
						mFade1 = true;
					}
				}
			}
		}
	}
	if (Act1Events::hasBeenHandled(Act1Event::GivenSkullToMiner))
	{
		for (int i = 0; i < mObjects.size(); i++)
		{
			if (mObjects[i]->getObjID() == "minecart")
			{
				PathFinder::getCurrentTileMap().removeCollision(mObjects[i]->getCollisionRect());
				delete mObjects[i];
				mObjects.erase(mObjects.begin() + i);
			}
		}
	}
	if (Act1Events::hasBeenTriggered(Act1Event::TooDarkToGo) && !Act1Events::hasBeenHandled(Act1Event::TooDarkToGo))
	{
		if (!DialogHandler::getDialogue("Ulfr_Cavern").getActiveConversation() && !DialogHandler::getDialogue("Ulfr_Cavern").getHasStopped())
			DialogHandler::getDialogue("Ulfr_Cavern").startDialogue();
		if (DialogHandler::getDialogue("Ulfr_Cavern").getHasStopped())
		{
			Act1Events::handleEvent(Act1Event::TooDarkToGo);
			LVLMI.changeLevel(LevelFolder::Cliffs_Down);
			mPlayer->setPosition(sf::Vector2f(165, 410));
		}
	}


	if (!Act1Events::hasBeenHandled(Act1Event::GivenSkullToMiner))
	{
		if (mObjects[mObjIndex]->getObjID() == "gold" && mObjects[mObjIndex]->getIsWorking())
		{
			mObjects[mObjIndex]->enableObject(false);
		}

	}
	else if (Act1Events::hasBeenHandled(Act1Event::GivenSkullToMiner))
	{
		if (mObjects[mObjIndex]->getObjID() == "gold" && !mObjects[mObjIndex]->getIsWorking())
		{
			mObjects[mObjIndex]->enableObject(true);
		}
	}

	Level::update(frametime);
	changeLevel();
}

void Level_Cavern_Right::render(IndexRenderer &iRenderer)
{
	if (!Act1Events::hasBeenHandled(Act1Event::GotCandleLight))
		iRenderer.addShape(mDarkness, 999);
	Level::render(iRenderer);
}

void Level_Cavern_Right::load()
{
	mPortals[CavernsToCliffs] = &PortalLoader::getPortal(CavernsToCliffs);
	mPortals[CavernsRightToLeft] = &PortalLoader::getPortal(CavernsRightToLeft);
	mPortals[CavernToCavernRuinsRight] = &PortalLoader::getPortal(CavernToCavernRuinsRight);
	mPortals[CavernsRightToLeft]->setWorking(true);
	mPortals[CavernsToCliffs]->setWorking(true);

	Level::load();
}

void Level_Cavern_Right::unload()
{
	Level::unload();
}

void Level_Cavern_Right::changeLevel()
{
	if (mPortals[CavernsToCliffs]->getActivated() && mPortals[CavernsToCliffs]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Cliffs_Down);
		AudioPlayer::stopHDDSound(HDDSound::Forest_Music);
		AudioPlayer::stopHDDSound(HDDSound::Cavern_Ambient);
		mRestartSounds = true;
	}
	if (mPortals[CavernsRightToLeft]->getActivated() && mPortals[CavernsRightToLeft]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Cavern_Left);
	}
}

void Level_Cavern_Right::checkInteractEvents()
{
	if (mDroppedItemID == "pickaxe" && mObjects[mObjIndex]->getObjID() == "gold" && !Act1Events::hasBeenTriggered(Act1Event::MinedSomeGold))
		Act1Events::triggerEvent(Act1Event::MinedSomeGold);
}
void Level_Cavern_Right::checkEvents()
{
	if (!Act1Events::hasBeenHandled(Act1Event::GotCandleLight) && !Act1Events::hasBeenTriggered(Act1Event::TooDarkToGo))
	{
		Act1Events::triggerEvent(Act1Event::TooDarkToGo);
	}

	if (!Act1Events::hasBeenTriggered(Act1Event::SweetGold) && mObjects[mObjIndex]->getObjID() == "gold" && mObjects[mObjIndex]->getIsWorking())
		Act1Events::triggerEvent(Act1Event::SweetGold);
}
