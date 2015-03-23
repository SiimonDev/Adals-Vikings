#include "Level_City_Gates.h"
#include "..\Logics\AudioPlayer.h"
#include "..\Interface\LoadingScreen.h"
#include "..\Interface\VideoHandler.h"
#include <iostream>

Level_City_Gates::Level_City_Gates(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::City_Gates;
}

void Level_City_Gates::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::City_Gates_Ambient, true, mAmbientSoundLevel);
	AudioPlayer::playHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music, true, mMusicSoundLevel);
}

void Level_City_Gates::update(sf::Time &frametime)
{
	if (Act1Events::hasBeenTriggered(Act1Event::TalkedToGuard) && !Act1Events::hasBeenHandled(Act1Event::TalkedToGuard))
	{
		if (DialogHandler::getDialogue("Ulfr_Gates").getHasStopped())
		{
			mPortals[GatesToCliffs]->setWorking(true);
			Act1Events::handleEvent(Act1Event::TalkedToGuard);
		}
	}
	if (Act1Events::hasBeenTriggered(Act1Event::GivenSkullHelmetToGuard) && !Act1Events::hasBeenHandled(Act1Event::GivenSkullHelmetToGuard))
	{
		if (!DialogHandler::getDialogue("Guard2_Gates").getActiveConversation() && !DialogHandler::getDialogue("Guard2_Gates").getHasStopped())
		{
			DialogHandler::startDialogue("Guard2_Gates");
		}
		if (DialogHandler::getDialogue("Guard2_Gates").getHasStopped())
		{
			if (!mFade1)
			{
				FadeI.fadeOut(frametime);

				if (FadeI.getFaded())
				{
					mFade1 = true;
					Act1Events::handleEvent(Act1Event::GivenSkullHelmetToGuard);
					LSI.startLoading(LoadTask::LoadMainMenu, &VideoHandlerI.getCredits());
				}
			}
		}
	}
	Level::update(frametime);
	changeLevel();
}

void Level_City_Gates::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_City_Gates::load()
{
	mPortals[GatesToRoad] = &PortalLoader::getPortal(GatesToRoad);
	mPortals[GatesToCliffs] = &PortalLoader::getPortal(GatesToCliffs);
	mPortals[GatesToRoad]->setWorking(true);

	mNpcs["Guard"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Guard")));
	mNpcs["Leifr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Leifr")));

	mNpcs["Leifr"]->setDialogue("Leifr_Gates");
	mNpcs["Leifr"]->setPosition(sf::Vector2f(285, 800));
	mNpcs["Leifr"]->setScale(sf::Vector2f(0.6f, 0.6f));
	mNpcs["Leifr"]->setInteractionPosition(sf::Vector2f(420, 800));
	mNpcs["Leifr"]->setIndex(2);
	mNpcs["Leifr"]->setFlip(true);
	mNpcs["Guard"]->setDialogue("Guard1_Gates");

	if (!Act1Events::hasBeenHandled(Act1Event::TalkedToGuard))
		mPortals[GatesToCliffs]->setCannotDialogue("I should talk to that guard first. Should be pretty easy to smooth talk my way into the city.");
	else
		mPortals[GatesToCliffs]->setWorking(true);

	Level::load();

	mTileMap.addCollision(mNpcs["Guard"]->getCollisionRect());
	mTileMap.setIndexOnMap(mNpcs["Guard"]->getIndexRect(), mNpcs["Guard"]->getIndex() - 1);
}

void Level_City_Gates::unload()
{
	Level::unload();
}

void Level_City_Gates::changeLevel()
{
	if (mPortals[GatesToRoad]->getActivated() && mPortals[GatesToRoad]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Road);
		AudioPlayer::stopHDDSound(HDDSound::City_Gates_Ambient);
		AudioPlayer::stopHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music);
		mRestartSounds = true;
	}
	if (mPortals[GatesToCliffs]->getActivated() && mPortals[GatesToCliffs]->getWorking())
	{
		if (!Act1Events::hasBeenTriggered(Act1Event::CliffsMonologue))
			Act1Events::triggerEvent(Act1Event::CliffsMonologue);
		LVLMI.changeLevel(LevelFolder::Cliffs_Up);
		AudioPlayer::stopHDDSound(HDDSound::City_Gates_Ambient);
		AudioPlayer::stopHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music);
		mRestartSounds = true;
	}
}

void Level_City_Gates::checkInteractEvents()
{
	if (mDroppedItemID == "skullHelmet" && mCurrentNPCID == "Guard" && !Act1Events::hasBeenTriggered(Act1Event::GivenSkullHelmetToGuard))
		Act1Events::triggerEvent(Act1Event::GivenSkullHelmetToGuard);
}
void Level_City_Gates::checkEvents()
{
	if (!Act1Events::hasBeenTriggered(Act1Event::TalkedToGuard) && DialogHandler::getDialogue("Guard1_Gates").getIsOptionDisabled(3) && DialogHandler::getDialogue("Guard1_Gates").getHasStopped())
	{
		DialogHandler::startDialogue("Ulfr_Gates");
		Act1Events::triggerEvent(Act1Event::TalkedToGuard);
	}

}
