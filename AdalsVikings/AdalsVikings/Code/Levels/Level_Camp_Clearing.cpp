#include "Level_Camp_Clearing.h"
#include <iostream>

Level_Camp_Clearing::Level_Camp_Clearing(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Camp_Clearing;
}

void Level_Camp_Clearing::update(sf::Time &frametime)
{
	if (Act1Events::hasBeenTriggered(Act1Event::CampClearing_TalkedToAll) && !Act1Events::hasBeenHandled(Act1Event::CampClearing_TalkedToAll))
	{
		mPortals[CampToRoad]->setWorking(true);
		mPortals[CampToForestRoad]->setWorking(true);
	}
	changeLevel();
	Level::update(frametime);
}

void Level_Camp_Clearing::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Camp_Clearing::load()
{
	mNpcs["Leifr"] = NpcPtr(new Npc(NpcHandler::getNpc("Leifr")));
	mNpcs["Brynja"] = NpcPtr(new Npc(NpcHandler::getNpc("Brynja")));
	mNpcs["Valdis"] = NpcPtr(new Npc(NpcHandler::getNpc("Valdis")));

	mNpcs["Leifr"]->setscale(sf::Vector2f(0.42, 0.42));
	mNpcs["Brynja"]->setscale(sf::Vector2f(0.42, 0.42));
	mNpcs["Valdis"]->setscale(sf::Vector2f(0.4, 0.4));

	mNpcs["Valdis"]->setDialogue("Valdis_ClearingCamp");
	mNpcs["Brynja"]->setDialogue("Brynja_ClearingCamp");
	mNpcs["Leifr"]->setDialogue("Leifr_ClearingCamp");

	mPortals[CampToRoad] = &PortalLoader::getPortal(CampToRoad);
	mPortals[CampToForestRoad] = &PortalLoader::getPortal(CampToForestRoad);

	mPortals[CampToRoad]->setCannotDialogue("I should speak to the others first. They might need help with something, and I don't want to come off as an asshole.");
	mPortals[CampToForestRoad]->setCannotDialogue("I should speak to the others first. They might need help with something, and I don't want to come off as an asshole.");
	Level::load();
}

void Level_Camp_Clearing::unload()
{
	Level::unload();
}

void Level_Camp_Clearing::changeLevel()
{
	if (mPortals[CampToRoad]->getActivated() && mPortals[CampToRoad]->getWorking())
		LVLMI.changeLevel(LevelFolder::Road);
	else if (mPortals[CampToForestRoad]->getActivated() && mPortals[CampToForestRoad]->getWorking())
		LVLMI.changeLevel(LevelFolder::Forest_Road);
}

void Level_Camp_Clearing::checkInteractEvents()
{

}
void Level_Camp_Clearing::checkEvents()
{
	if (DialogHandler::getDialogue("Brynja_ClearingCamp").getActiveConversation())
		Act1Events::triggerEvent(Act1Event::CampClearing_Brynja);
	if (Act1Events::hasBeenTriggered(Act1Event::CampClearing_Brynja) && !Act1Events::hasBeenHandled(Act1Event::CampClearing_Brynja))
		if (DialogHandler::getDialogue("Brynja_ClearingCamp").getHasStopped())
			Act1Events::handleEvent(Act1Event::CampClearing_Brynja);

	if (DialogHandler::getDialogue("Valdis_ClearingCamp").getActiveConversation())
		Act1Events::triggerEvent(Act1Event::CampClearing_Valdis);
	if (Act1Events::hasBeenTriggered(Act1Event::CampClearing_Valdis) && !Act1Events::hasBeenHandled(Act1Event::CampClearing_Valdis))
		if (DialogHandler::getDialogue("Valdis_ClearingCamp").getHasStopped())
			Act1Events::handleEvent(Act1Event::CampClearing_Valdis);

	if (DialogHandler::getDialogue("Leifr_ClearingCamp").getActiveConversation())
		Act1Events::triggerEvent(Act1Event::CampClearing_Leifr);
	if (Act1Events::hasBeenTriggered(Act1Event::CampClearing_Leifr) && !Act1Events::hasBeenHandled(Act1Event::CampClearing_Leifr))
		if (DialogHandler::getDialogue("Leifr_ClearingCamp").getHasStopped())
			Act1Events::handleEvent(Act1Event::CampClearing_Leifr);

	if (Act1Events::hasBeenHandled(Act1Event::CampClearing_Leifr) && Act1Events::hasBeenHandled(Act1Event::CampClearing_Valdis) &&
		Act1Events::hasBeenHandled(Act1Event::CampClearing_Brynja) && !Act1Events::hasBeenTriggered(Act1Event::CampClearing_TalkedToAll))
	{
		Act1Events::triggerEvent(Act1Event::CampClearing_TalkedToAll);
	}

}
