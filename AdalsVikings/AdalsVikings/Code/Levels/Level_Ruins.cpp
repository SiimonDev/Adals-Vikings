#include "Level_Ruins.h"
#include "..\Logics\AudioPlayer.h"
#include <iostream>

Level_Ruins::Level_Ruins(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Ruins;
}

void Level_Ruins::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Ruins_Ambient, true, mAmbientSoundLevel);
	AudioPlayer::playHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music, true, mMusicSoundLevel);
}

void Level_Ruins::update(sf::Time &frametime)
{
	if (Act1Events::hasBeenTriggered(Act1Event::Ruins_Introduction) && !Act1Events::hasBeenHandled(Act1Event::Ruins_Introduction))
	{
		if (!DialogHandler::getDialogue("AethelBerth_Ruins").getActiveConversation() && !DialogHandler::getDialogue("AethelBerth_Ruins").getHasStopped())
			DialogHandler::startDialogue("AethelBerth_Ruins");

		if (DialogHandler::getDialogue("AethelBerth_Ruins").getHasStopped())
			Act1Events::handleEvent(Act1Event::Ruins_Introduction);
	}

	if (Act1Events::hasBeenTriggered(Act1Event::Ruins_RockSlide) && !Act1Events::hasBeenHandled(Act1Event::Ruins_RockSlide))
	{
		if (!mFade1)
		{
			mPlayer->UpdateAnimationStyle();
			FadeI.fadeOut(frametime);
			if (FadeI.getFaded())
			{
				mFade1 = true;
			}
		}
		if (mFade1 && !mfade2)
		{
			FadeI.fadeIn(frametime);
			if (FadeI.getFaded())
			{
				mfade2 = true;
			}
		}
		if (mfade2 && !DialogHandler::getDialogue("Biker_Ruins").getActiveConversation() && !DialogHandler::getDialogue("Biker_Ruins").getHasStopped())
		{
			DialogHandler::startDialogue("Biker_Ruins");
		}
		if (DialogHandler::getDialogue("Biker_Ruins").getHasStopped())
		{
			Act1Events::handleEvent(Act1Event::Ruins_RockSlide);
		}
	}
	Level::update(frametime);
	changeLevel();
}

void Level_Ruins::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Ruins::load()
{
	mPortals[RuinsToCliffs] = &PortalLoader::getPortal(RuinsToCliffs);
	mPortals[RuinsToCliffs]->setWorking(true);

	mNpcs["Aethelberth"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Aethelberth")));
	mNpcs["Cerdic"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Cerdic")));
	mNpcs["Leofstan"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Leofstan")));
	mNpcs["Osgar"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Osgar")));

	mNpcs["Aethelberth"]->setDialogue("AethelBerth_Ruins");
	mNpcs["Cerdic"]->setDialogue("Cerdic_Ruins");
	mNpcs["Leofstan"]->setDialogue("Osgar_Ruins");
	mNpcs["Osgar"]->setDialogue("Leostand_Ruins");

	Level::load();
}

void Level_Ruins::unload()
{
	Level::unload();
}

void Level_Ruins::changeLevel()
{
	if (mPortals[RuinsToCliffs]->getActivated() && mPortals[RuinsToCliffs]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Cliffs_Up);
		AudioPlayer::stopHDDSound(HDDSound::Ruins_Ambient);
		AudioPlayer::stopHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music);
		mRestartSounds = true;
	}
}

void Level_Ruins::checkInteractEvents()
{

}
void Level_Ruins::checkEvents()
{
	if (!Act1Events::hasBeenTriggered(Act1Event::Ruins_Introduction) && mPlayer->getPosition().x < 900)
	{
		Act1Events::triggerEvent(Act1Event::Ruins_Introduction);
	}
	if (!Act1Events::hasBeenTriggered(Act1Event::Ruins_RockSlide) && Act1Events::hasBeenHandled(Act1Event::Ruins_Introduction) && mPlayer->getPosition().x > 1500)
	{
		Act1Events::triggerEvent(Act1Event::Ruins_RockSlide);
	}
}
