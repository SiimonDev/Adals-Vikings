#include "Level_Cliffs_Up.h"
#include <iostream>

Level_Cliffs_Up::Level_Cliffs_Up(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Cliffs_Up;
}

void Level_Cliffs_Up::restartSounds()
{

}

void Level_Cliffs_Up::update(sf::Time &frametime)
{
	if (Act1Events::hasBeenTriggered(Act1Event::CliffsMonologue) && !Act1Events::hasBeenHandled(Act1Event::CliffsMonologue))
	{
		if (!DialogHandler::getDialogue("Ulfr_Cliffs").getActiveConversation() && !DialogHandler::getDialogue("Ulfr_Cliffs").getHasStopped())
			DialogHandler::getDialogue("Ulfr_Cliffs").startDialogue();

		if (DialogHandler::getDialogue("Ulfr_Cliffs").getHasStopped())
			Act1Events::handleEvent(Act1Event::CliffsMonologue);
	}

	Level::update(frametime);
	changeLevel(frametime);
}

void Level_Cliffs_Up::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Cliffs_Up::load()
{
	mPortals[CliffsToGates] = &PortalLoader::getPortal(CliffsToGates);
	mPortals[CliffsTopToCliffsBottom] = &PortalLoader::getPortal(CliffsTopToCliffsBottom);
	mPortals[CliffsToRuins] = &PortalLoader::getPortal(CliffsToRuins);
	mPortals[CliffsToRuins]->setWorking(true);
	mPortals[CliffsToGates]->setWorking(true);
	mPortals[CliffsTopToCliffsBottom]->setWorking(true);

	Level::load();
}

void Level_Cliffs_Up::unload()
{
	Level::unload();
}

void Level_Cliffs_Up::changeLevel(sf::Time &frametime)
{
	if (mPortals[CliffsToGates]->getActivated() && mPortals[CliffsToGates]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::City_Gates);
	}
	if (mPortals[CliffsTopToCliffsBottom]->getActivated() && mPortals[CliffsTopToCliffsBottom]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Cliffs_Down);
	}
	if (mPortals[CliffsToRuins]->getActivated() && mPortals[CliffsToRuins]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Ruins);
	}
}

void Level_Cliffs_Up::checkInteractEvents()
{

}
void Level_Cliffs_Up::checkEvents()
{

}
