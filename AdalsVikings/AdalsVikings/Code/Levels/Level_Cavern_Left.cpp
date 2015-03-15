#include "Level_Cavern_Left.h"
#include <iostream>

Level_Cavern_Left::Level_Cavern_Left(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Cavern_Left;
}

void Level_Cavern_Left::restartSounds()
{

}

void Level_Cavern_Left::update(sf::Time &frametime)
{
	if (Act1Events::hasBeenTriggered(Act1Event::GivenSkullToMiner) && !Act1Events::hasBeenHandled(Act1Event::GivenSkullToMiner))
	{
		if (!DialogHandler::getDialogue("Skull_Cavern").getActiveConversation() && !DialogHandler::getDialogue("Skull_Cavern").getHasStopped())
			DialogHandler::getDialogue("Skull_Cavern").startDialogue();

		if (DialogHandler::getDialogue("Skull_Cavern").getHasStopped())
		{
			if (!mFade1)
			{
				FadeI.fadeOut(frametime);

				if (FadeI.getFaded())
				{
					mNpcs.clear();
					mFade1 = true;
				}
			}
			if (mFade1 && !mFade2)
			{
				FadeI.fadeIn(frametime);

				if (FadeI.getFaded())
				{
					DialogHandler::getDialogue("UlfrAngry_Cavern").startDialogue();
					mFade2 = true;
				}
			}
		}
		if (DialogHandler::getDialogue("UlfrAngry_Cavern").getHasStopped())
		{
			Act1Events::handleEvent(Act1Event::GivenSkullToMiner);
		}
	}
	Level::update(frametime);
	changeLevel();
}

void Level_Cavern_Left::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Cavern_Left::load()
{
	mPortals[CavernsLeftToRight] = &PortalLoader::getPortal(CavernsLeftToRight);
	mPortals[CavernsLeftToRight]->setWorking(true);

	mNpcs["Miner"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Miner")));

	mNpcs["Miner"]->setDialogue("Miner_Cavern");

	Level::load();
}

void Level_Cavern_Left::unload()
{
	Level::unload();
}

void Level_Cavern_Left::changeLevel()
{
	if (mPortals[CavernsLeftToRight]->getActivated() && mPortals[CavernsLeftToRight]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Cavern_Right);
	}
}

void Level_Cavern_Left::checkInteractEvents()
{
	if (mDroppedItemID == "skull" && mCurrentNPCID == "Miner" && !Act1Events::hasBeenTriggered(Act1Event::GivenSkullToMiner) && Act1Events::hasBeenHandled(Act1Event::GivenSleepingMeatToWolf) && DialogHandler::getDialogue("Miner_Cavern").getIsOptionDisabled(3))
		Act1Events::triggerEvent(Act1Event::GivenSkullToMiner);

}
void Level_Cavern_Left::checkEvents()
{

}
