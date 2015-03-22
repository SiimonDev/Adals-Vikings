#include "Level_Hills.h"
#include "..\Logics\AudioPlayer.h"
#include <iostream>

Level_Hills::Level_Hills(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Hills;
}

void Level_Hills::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Hills_Ambient, true, 20);
	AudioPlayer::playHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music, true, 20);
}

void Level_Hills::update(sf::Time &frametime)
{
	if (Act1Events::hasBeenTriggered(Act1Event::GivenSleepingMeatToWolf) && !Act1Events::hasBeenHandled(Act1Event::GivenSleepingMeatToWolf))
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
				mFade2 = true;
				DialogHandler::startDialogue("Ulfr_Hills");
			}
		}
		if (DialogHandler::getDialogue("Ulfr_Hills").getHasStopped())
		{
			DialogHandler::getDialogue("Miner_Cavern").enableOption(3);
			Act1Events::handleEvent(Act1Event::GivenSleepingMeatToWolf);
		}
	}
	Level::update(frametime);
	changeLevel();
}

void Level_Hills::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Hills::load()
{
	mPortals[HillsToFarm] = &PortalLoader::getPortal(HillsToFarm);
	mPortals[HillsToFarm]->setWorking(true);

	mNpcs["Finnr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Finnr")));
	mNpcs["Finnr"]->setPosition(sf::Vector2f(800, 830));
	mNpcs["Finnr"]->setInteractionPosition(sf::Vector2f(720, 825));
	mNpcs["Finnr"]->setScale(sf::Vector2f(0.45, 0.45));
	mNpcs["Finnr"]->setDialogue("Finnr_Hills");

	Level::load();

	mTileMap.addCollision(mNpcs["Finnr"]->getCollisionRect());
	mTileMap.setIndexOnMap(mNpcs["Finnr"]->getIndexRect(), mNpcs["Finnr"]->getIndex() - 1);
}

void Level_Hills::unload()
{
	Level::unload();
}

void Level_Hills::changeLevel()
{
	if (mPortals[HillsToFarm]->getActivated() && mPortals[HillsToFarm]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Farm_1);
		AudioPlayer::stopHDDSound(HDDSound::Hills_Ambient);
		AudioPlayer::stopHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music);
		mRestartSounds = true;
	}
}

void Level_Hills::checkInteractEvents()
{
	if (mDroppedItemID == "sleepingMeat" && mObjects[mObjIndex]->getObjID() == "ShackEntrance" && !Act1Events::hasBeenTriggered(Act1Event::GivenSleepingMeatToWolf))
		Act1Events::triggerEvent(Act1Event::GivenSleepingMeatToWolf);
}
void Level_Hills::checkEvents()
{

}
