#include "Level_Farm_1.h"
#include "..\Logics\AudioPlayer.h"
#include <iostream>

Level_Farm_1::Level_Farm_1(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Farm_1;
}

void Level_Farm_1::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Road_Ambient, true, mAmbientSoundLevel);
	AudioPlayer::playHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music, true, mMusicSoundLevel);
}

void Level_Farm_1::update(sf::Time &frametime)
{
	if (KeyboardState::isPressed(sf::Keyboard::Num1))
	{
		mPlayer->addItemToInventory("mead");
		mPlayer->addItemToInventory("flowers");
		mPlayer->addItemToInventory("meat");
	}
	if (Act1Events::hasBeenTriggered(Act1Event::GivenMeadToValdis) && !Act1Events::hasBeenHandled(Act1Event::GivenMeadToValdis))
	{
		if (mPlayer->hasItemInInventory("mead"))
		mPlayer->removeItemFromInventory("mead");
		if (!Act1Events::hasBeenHandled(Act1Event::GivenFlowerToValdis))
		{
			if (!DialogHandler::getDialogue("Mead_Farm").getActiveConversation() && !DialogHandler::getDialogue("Mead_Farm").getHasStopped())
				DialogHandler::startDialogue("Mead_Farm");

			if (DialogHandler::getDialogue("Mead_Farm").getHasStopped())
				Act1Events::handleEvent(Act1Event::GivenMeadToValdis);
		}
		else if (Act1Events::hasBeenHandled(Act1Event::GivenFlowerToValdis))
		{
			if (!DialogHandler::getDialogue("GotAll_Farm").getActiveConversation() && !DialogHandler::getDialogue("GotAll_Farm").getHasStopped())
				DialogHandler::startDialogue("GotAll_Farm");

			if (DialogHandler::getDialogue("GotAll_Farm").getHasStopped())
			{
				if (!mFade1)
				{
					FadeI.fadeOut(frametime);

					if (FadeI.getFaded())
					{
						mFade1 = true;
					}
				}
				if (mFade1 && !mFade2)
				{
					FadeI.fadeIn(frametime);

					if (FadeI.getFaded())
					{
						DialogHandler::startDialogue("MadePill_Farm");
						mFade2 = true;
					}
				}
			}
			if (DialogHandler::getDialogue("MadePill_Farm").getHasStopped())
			{
				mPlayer->addItemToInventory("sleepingPill");
				Act1Events::handleEvent(Act1Event::GivenMeadToValdis);
			}
		}

	}
	if (Act1Events::hasBeenTriggered(Act1Event::GivenFlowerToValdis) && !Act1Events::hasBeenHandled(Act1Event::GivenFlowerToValdis))
	{
		if (mPlayer->hasItemInInventory("flowers"))
			mPlayer->removeItemFromInventory("flowers");
		if (!Act1Events::hasBeenHandled(Act1Event::GivenMeadToValdis))
		{
			if (!DialogHandler::getDialogue("Flower_Farm").getActiveConversation() && !DialogHandler::getDialogue("Flower_Farm").getHasStopped())
				DialogHandler::startDialogue("Flower_Farm");

			if (DialogHandler::getDialogue("Flower_Farm").getHasStopped())
				Act1Events::handleEvent(Act1Event::GivenFlowerToValdis);
		}
		else if (Act1Events::hasBeenHandled(Act1Event::GivenMeadToValdis))
		{
			if (!DialogHandler::getDialogue("GotAll_Farm").getActiveConversation() && !DialogHandler::getDialogue("GotAll_Farm").getHasStopped())
				DialogHandler::startDialogue("GotAll_Farm");

			if (DialogHandler::getDialogue("GotAll_Farm").getHasStopped())
			{
				if (!mFade1)
				{
					FadeI.fadeOut(frametime);

					if (FadeI.getFaded())
					{
						mFade1 = true;
					}
				}
				if (mFade1 && !mFade2)
				{
					FadeI.fadeIn(frametime);

					if (FadeI.getFaded())
					{
						DialogHandler::startDialogue("MadePill_Farm");
						mFade2 = true;
					}
				}
			}
			if (DialogHandler::getDialogue("MadePill_Farm").getHasStopped())
			{
				mPlayer->addItemToInventory("sleepingPill");
				Act1Events::handleEvent(Act1Event::GivenFlowerToValdis);
			}
		}
	}
	Level::update(frametime);
	changeLevel();
}

void Level_Farm_1::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Farm_1::load()
{
	mPortals[FarmToRoad] = &PortalLoader::getPortal(FarmToRoad);
	mPortals[Farm1ToFarm2] = &PortalLoader::getPortal(Farm1ToFarm2);
	mPortals[FarmToHills] = &PortalLoader::getPortal(FarmToHills);
	mPortals[FarmToHills]->setWorking(true);
	mPortals[Farm1ToFarm2]->setWorking(true);
	mPortals[FarmToRoad]->setWorking(true);

	mNpcs["Valdis"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Valdis")));
	mNpcs["Valdis"]->setDialogue("Valdis_Farm");
	mNpcs["Valdis"]->setPosition(sf::Vector2f(840, 960));
	mNpcs["Valdis"]->setInteractionPosition(sf::Vector2f(585, 970));
	mNpcs["Valdis"]->setScale(sf::Vector2f(0.8, 0.8));

	Level::load();

	mTileMap.addCollision(mNpcs["Valdis"]->getCollisionRect());
	mTileMap.setIndexOnMap(mNpcs["Valdis"]->getIndexRect(), mNpcs["Valdis"]->getIndex() - 1);
}

void Level_Farm_1::unload()
{
	Level::unload();
}

void Level_Farm_1::changeLevel()
{
	if (mPortals[FarmToRoad]->getActivated() && mPortals[FarmToRoad]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Road);
	}
	if (mPortals[Farm1ToFarm2]->getActivated() && mPortals[Farm1ToFarm2]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Farm_2);
	}
	if (mPortals[FarmToHills]->getActivated() && mPortals[FarmToHills]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Hills);
		AudioPlayer::stopHDDSound(HDDSound::Road_Ambient);
		AudioPlayer::stopHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music);
		mRestartSounds = true;
	}
}

void Level_Farm_1::checkInteractEvents()
{
	if (mDroppedItemID == "mead" && mCurrentNPCID == "Valdis" && !Act1Events::hasBeenTriggered(Act1Event::GivenMeadToValdis))
		Act1Events::triggerEvent(Act1Event::GivenMeadToValdis);

	// Event for dropping the flute on Brynja
	if (mDroppedItemID == "flowers" && mCurrentNPCID == "Valdis" && !Act1Events::hasBeenTriggered(Act1Event::GivenFlowerToValdis))
		Act1Events::triggerEvent(Act1Event::GivenFlowerToValdis);
}
void Level_Farm_1::checkEvents()
{
}