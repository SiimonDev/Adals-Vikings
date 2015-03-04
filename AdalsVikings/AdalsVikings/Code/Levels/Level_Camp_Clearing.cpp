#include "Level_Camp_Clearing.h"
#include <iostream>

Level_Camp_Clearing::Level_Camp_Clearing(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Camp_Clearing;
}

void Level_Camp_Clearing::update(sf::Time &frametime)
{
	if (Act1Events::hasBeenTriggered(Act1Event::CampClearing_Leifr) && !Act1Events::hasBeenHandled(Act1Event::CampClearing_Leifr))
	{
		if (!DialogHandler::getDialogue("Leifr_ClearingCamp").getActiveConversation() && !DialogHandler::getDialogue("Leifr_ClearingCamp").getHasStopped())
			DialogHandler::getDialogue("Leifr_ClearingCamp").startDialogue();
		else if (DialogHandler::getDialogue("Leifr_ClearingCamp").getHasStopped())
		{
			FadeI.fadeOut(frametime);

			if (FadeI.getFaded())
			{

			}
		}
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

	/*------------------- Leifr ----------------*/
	mNpcs["Leifr"]->setscale(sf::Vector2f(0.4, 0.4));
	mNpcs["Leifr"]->setPosition(sf::Vector2f(1035, 729));
	mNpcs["Leifr"]->setInteractionPosition(sf::Vector2f(1160, 724));
	mNpcs["Leifr"]->setDialogue("Leifr_ClearingCamp");

	/*------------------- Brynja ----------------*/
	mNpcs["Brynja"]->setscale(sf::Vector2f(0.4, 0.4));
	mNpcs["Brynja"]->setPosition(sf::Vector2f(1500, 850));
	mNpcs["Brynja"]->setInteractionPosition(sf::Vector2f(1385, 825));
	mNpcs["Brynja"]->setDialogue("Brynja_ClearingCamp");

	/*------------------- Valdis ----------------*/
	mNpcs["Valdis"]->setscale(sf::Vector2f(0.4, 0.4));
	mNpcs["Valdis"]->setPosition(sf::Vector2f(645, 860));
	mNpcs["Valdis"]->setInteractionPosition(sf::Vector2f(750, 860));
	mNpcs["Valdis"]->setFlip(true);
	mNpcs["Valdis"]->setDialogue("Valdis_ClearingCamp");

	mPortals[CampToRoad] = &PortalLoader::getPortal(CampToRoad);
	mPortals[CampToForestRoad] = &PortalLoader::getPortal(CampToForestRoad);

	if (!Act1Events::hasBeenHandled(Act1Event::CampClearing_Brynja))
		mPortals[CampToRoad]->setCannotDialogue("I should speak to the others first. They might need help with something, and I don't want to come off as an asshole.");
	else if (Act1Events::hasBeenHandled(Act1Event::CampClearing_Brynja))
		mPortals[CampToRoad]->setWorking(true);
	if (!Act1Events::hasBeenHandled(Act1Event::CampClearing_Valdis))
		mPortals[CampToForestRoad]->setCannotDialogue("I should speak to the others first. They might need help with something, and I don't want to come off as an asshole.");
	else if (Act1Events::hasBeenHandled(Act1Event::CampClearing_Valdis))
		mPortals[CampToForestRoad]->setWorking(true);

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
		{
		Act1Events::handleEvent(Act1Event::CampClearing_Brynja);
		mPortals[CampToRoad]->setWorking(true);
		}

	if (DialogHandler::getDialogue("Valdis_ClearingCamp").getActiveConversation())
		Act1Events::triggerEvent(Act1Event::CampClearing_Valdis);
	if (Act1Events::hasBeenTriggered(Act1Event::CampClearing_Valdis) && !Act1Events::hasBeenHandled(Act1Event::CampClearing_Valdis))
		if (DialogHandler::getDialogue("Valdis_ClearingCamp").getHasStopped())
		{
			mPortals[CampToForestRoad]->setWorking(true);
			Act1Events::handleEvent(Act1Event::CampClearing_Valdis);
		}

	if (Act1Events::hasBeenHandled(Act1Event::CampClearing_Leifr) && Act1Events::hasBeenHandled(Act1Event::CampClearing_Valdis) &&
		Act1Events::hasBeenHandled(Act1Event::CampClearing_Brynja) && !Act1Events::hasBeenTriggered(Act1Event::CampClearing_TalkedToAll))
	{
		Act1Events::triggerEvent(Act1Event::CampClearing_TalkedToAll);
	}

	if (!Act1Events::hasBeenTriggered(Act1Event::GotBeerDeerPelt) && mPlayer.hasItemInInventory("BeerDeer"))
		Act1Events::triggerEvent(Act1Event::GotBeerDeerPelt);

	if (!Act1Events::hasBeenTriggered(Act1Event::CampClearing_Leifr) && Act1Events::hasBeenTriggered(Act1Event::GotBeerDeerPelt))
		Act1Events::triggerEvent(Act1Event::CampClearing_Leifr);

}
