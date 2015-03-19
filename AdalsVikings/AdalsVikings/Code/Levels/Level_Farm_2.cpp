#include "Level_Farm_2.h"
#include "..\Logics\AudioPlayer.h"
#include <iostream>

Level_Farm_2::Level_Farm_2(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Farm_2;
}

void Level_Farm_2::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Road_Ambient, true, 20);
	AudioPlayer::playHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music, true, 20);
}

void Level_Farm_2::update(sf::Time &frametime)
{
	if (Act1Events::hasBeenTriggered(Act1Event::TalkedToJacob) && !Act1Events::hasBeenHandled(Act1Event::TalkedToJacob))
	{
		DialogHandler::getDialogue("Parrik_Farm").enableOption(2);
		Act1Events::handleEvent(Act1Event::TalkedToJacob);
	}
	if (Act1Events::hasBeenTriggered(Act1Event::TalkedToParrik) && !Act1Events::hasBeenHandled(Act1Event::TalkedToParrik))
	{
		DialogHandler::getDialogue("Jacob_Farm").enableOption(3);
		Act1Events::handleEvent(Act1Event::TalkedToParrik);
	}
	if (Act1Events::hasBeenTriggered(Act1Event::SolvedConflict) && !Act1Events::hasBeenHandled(Act1Event::SolvedConflict))
	{
		if (DialogHandler::getDialogue("Jacob_Farm").getHasStopped())
		{
			mNpcs.erase("Jacob");
			mNpcs.erase("Parrik");
			Act1Events::handleEvent(Act1Event::SolvedConflict);
		}
	}

	Level::update(frametime);
	changeLevel();
}

void Level_Farm_2::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Farm_2::load()
{
	mPortals[Farm2ToFarm1] = &PortalLoader::getPortal(Farm2ToFarm1);
	mPortals[Farm2ToFarm1]->setWorking(true);


	mNpcs["Jacob"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Jacob")));
	mNpcs["Parrik"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Parrik")));

	mNpcs["Jacob"]->setDialogue("Jacob_Farm");
	mNpcs["Parrik"]->setDialogue("Parrik_Farm");

	Level::load();
}

void Level_Farm_2::unload()
{
	Level::unload();
}

void Level_Farm_2::changeLevel()
{
	if (mPortals[Farm2ToFarm1]->getActivated() && mPortals[Farm2ToFarm1]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Farm_1);
	}
}

void Level_Farm_2::checkInteractEvents()
{


}
void Level_Farm_2::checkEvents()
{
	if (!Act1Events::hasBeenTriggered(Act1Event::TalkedToJacob) && DialogHandler::getDialogue("Jacob_Farm").getIsOptionDisabled(2) && DialogHandler::getDialogue("Jacob_Farm").getHasStopped())
		Act1Events::triggerEvent(Act1Event::TalkedToJacob);

	if (!Act1Events::hasBeenTriggered(Act1Event::TalkedToParrik) && Act1Events::hasBeenHandled(Act1Event::TalkedToJacob) && DialogHandler::getDialogue("Parrik_Farm").getIsOptionDisabled(2) && DialogHandler::getDialogue("Parrik_Farm").getHasStopped())
		Act1Events::triggerEvent(Act1Event::TalkedToParrik);

	if (!Act1Events::hasBeenTriggered(Act1Event::SolvedConflict) && Act1Events::hasBeenHandled(Act1Event::TalkedToParrik) && DialogHandler::getDialogue("Jacob_Farm").getIsOptionDisabled(3) && DialogHandler::getDialogue("Jacob_Farm").getHasStopped())
		Act1Events::triggerEvent(Act1Event::SolvedConflict);

}
