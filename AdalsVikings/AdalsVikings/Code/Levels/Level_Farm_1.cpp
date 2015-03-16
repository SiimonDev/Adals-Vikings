#include "Level_Farm_1.h"
#include <iostream>

Level_Farm_1::Level_Farm_1(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Farm_1;
}

void Level_Farm_1::restartSounds()
{

}

void Level_Farm_1::update(sf::Time &frametime)
{
	if (KeyboardState::isPressed(sf::Keyboard::Num3))
	{
		mPlayer->addItemToInventory("mead");
		mPlayer->addItemToInventory("flowers");
		mPlayer->addItemToInventory("meat");
	}
	if (Act1Events::hasBeenTriggered(Act1Event::GivenMeadToValdis) && !Act1Events::hasBeenHandled(Act1Event::GivenMeadToValdis))
	{
		mPlayer->removeItemFromInventory("mead");
		if (!Act1Events::hasBeenHandled(Act1Event::GivenFlowerToValdis))
		{
			if (!DialogHandler::getDialogue("Mead_Farm").getActiveConversation() && !DialogHandler::getDialogue("Mead_Farm").getHasStopped())
				DialogHandler::getDialogue("Mead_Farm").startDialogue();

			if (DialogHandler::getDialogue("Mead_Farm").getHasStopped())
				Act1Events::handleEvent(Act1Event::GivenMeadToValdis);
		}
		else if (Act1Events::hasBeenHandled(Act1Event::GivenFlowerToValdis))
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
					mPlayer->addItemToInventory("sleepingAgent");
					Act1Events::hasBeenHandled(Act1Event::GivenMeadToValdis);
				}
			}
		}
	}
	if (Act1Events::hasBeenTriggered(Act1Event::GivenFlowerToValdis) && !Act1Events::hasBeenHandled(Act1Event::GivenFlowerToValdis))
	{
		mPlayer->removeItemFromInventory("flowers");
		if (!Act1Events::hasBeenHandled(Act1Event::GivenMeadToValdis))
		{
			if (!DialogHandler::getDialogue("Flower_Farm").getActiveConversation() && !DialogHandler::getDialogue("Flower_Farm").getHasStopped())
				DialogHandler::getDialogue("Flower_Farm").startDialogue();

			if (DialogHandler::getDialogue("Flower_Farm").getHasStopped())
				Act1Events::handleEvent(Act1Event::GivenFlowerToValdis);
		}
		else if (Act1Events::hasBeenHandled(Act1Event::GivenMeadToValdis))
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
					mPlayer->addItemToInventory("sleepingAgent");
					Act1Events::hasBeenHandled(Act1Event::GivenFlowerToValdis);
				}
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
	mNpcs["Valdis"]->setScale(sf::Vector2f(1, 1));

	Level::load();
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