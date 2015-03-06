#include "Level_Church_Inside.h"
#include "..\Logics\AudioPlayer.h"
#include <iostream>

Level_Church_Inside::Level_Church_Inside(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Church_Inside;
}

void Level_Church_Inside::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Church_Inside_Ambient, true, 100);
}

void Level_Church_Inside::update(sf::Time &frametime)
{
	Level::update(frametime);
	changeLevel();
}

void Level_Church_Inside::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Church_Inside::load()
{
	RMI.loadResource(Footsteps::Church);
	mPortals[ChurchToOutside_Church] = &PortalLoader::getPortal(ChurchToOutside_Church);
	mPortals[ChurchToOutside_Church]->setWorking(true);

	mNpcs["Beor"] = NpcPtr(new Npc(NpcHandler::getNpc("Beor")));
	mNpcs["Beor"]->setDialogue("Beor_ChurchInside");

	Level::load();

	mCurrentFootsteps = Footsteps::Church;
}

void Level_Church_Inside::unload()
{
	RMI.unloadResource(Footsteps::Church);
	Level::unload();
}

void Level_Church_Inside::changeLevel()
{
	if (mPortals[ChurchToOutside_Church]->getActivated() && mPortals[ChurchToOutside_Church]->getWorking() && !Act1Events::hasBeenTriggered(Act1Event::ChurchInside_GoBackDialogue) && DialogHandler::getDialogue("Beor_ChurchInside").getHasStopped())
	{
		Act1Events::triggerEvent(Act1Event::ChurchInside_GoBackDialogue);
		LVLMI.changeLevel(LevelFolder::Church_Outside);
		AudioPlayer::stopHDDSound(HDDSound::Church_Inside_Ambient);
		mRestartSounds = true;
	}
	else if (mPortals[ChurchToOutside_Church]->getActivated() && mPortals[ChurchToOutside_Church]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Church_Outside);
		AudioPlayer::stopHDDSound(HDDSound::Church_Inside_Ambient);
		mRestartSounds = true;
	}
}

void Level_Church_Inside::checkInteractEvents()
{

}

void Level_Church_Inside::checkEvents()
{

}