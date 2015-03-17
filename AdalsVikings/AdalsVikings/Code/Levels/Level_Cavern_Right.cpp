#include "Level_Cavern_Right.h"
#include <iostream>

Level_Cavern_Right::Level_Cavern_Right(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Cavern_Right;

	mDarkness.setSize(sf::Vector2f(1920, 1080));
	mDarkness.setFillColor(sf::Color(0, 0, 0, 200));
}

void Level_Cavern_Right::restartSounds()
{

}

void Level_Cavern_Right::update(sf::Time &frametime)
{
	if (Act1Events::hasBeenTriggered(Act1Event::MinedSomeGold) && !Act1Events::hasBeenHandled(Act1Event::MinedSomeGold))
	{
	}
	if (Act1Events::hasBeenHandled(Act1Event::GivenSkullToMiner))
	{
		for (int i = 0; i < mObjects.size(); i++)
		{
			if (mObjects[i]->getObjID() == "mineCart")
			{
				PathFinder::getCurrentTileMap().removeCollision(mObjects[i]->getCollisionRect());
				delete mObjects[i];
				mObjects.erase(mObjects.begin() + i);
			}
		}
	}
	if (Act1Events::hasBeenHandled(Act1Event::GivenSkullToMiner) && !mPlayer->hasItemInInventory("helmet") && !mPlayer->hasItemInInventory("skullHelmet"))
		mPlayer->addItemToInventory("helmet");
	if (Act1Events::hasBeenTriggered(Act1Event::TooDarkToGo) && !Act1Events::hasBeenHandled(Act1Event::TooDarkToGo))
	{
		if (!DialogHandler::getDialogue("Ulfr_Cavern").getActiveConversation() && !DialogHandler::getDialogue("Ulfr_Cavern").getHasStopped())
			DialogHandler::getDialogue("Ulfr_Cavern").startDialogue();
		if (DialogHandler::getDialogue("Ulfr_Cavern").getHasStopped())
		{
			Act1Events::handleEvent(Act1Event::TooDarkToGo);
			LVLMI.changeLevel(LevelFolder::Cliffs_Down);
		}
	}
	Level::update(frametime);
	changeLevel();
}

void Level_Cavern_Right::render(IndexRenderer &iRenderer)
{
	if (!Act1Events::hasBeenHandled(Act1Event::GotCandleLight))
		iRenderer.addShape(mDarkness, 999);
	Level::render(iRenderer);
}

void Level_Cavern_Right::load()
{
	mPortals[CavernsToCliffs] = &PortalLoader::getPortal(CavernsToCliffs);
	mPortals[CavernsRightToLeft] = &PortalLoader::getPortal(CavernsRightToLeft);
	mPortals[CavernsRightToLeft]->setWorking(true);
	mPortals[CavernsToCliffs]->setWorking(true);

	Level::load();
}

void Level_Cavern_Right::unload()
{
	Level::unload();
}

void Level_Cavern_Right::changeLevel()
{
	if (mPortals[CavernsToCliffs]->getActivated() && mPortals[CavernsToCliffs]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Cliffs_Down);
	}
	if (mPortals[CavernsRightToLeft]->getActivated() && mPortals[CavernsRightToLeft]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Cavern_Left);
	}
}

void Level_Cavern_Right::checkInteractEvents()
{
	if (mDroppedItemID == "pickAxe" && mObjects[mObjIndex]->getObjID() == "gold" && !Act1Events::hasBeenTriggered(Act1Event::MinedSomeGold))
		Act1Events::triggerEvent(Act1Event::MinedSomeGold);
}
void Level_Cavern_Right::checkEvents()
{
	if (!Act1Events::hasBeenHandled(Act1Event::GotCandleLight) && !Act1Events::hasBeenTriggered(Act1Event::TooDarkToGo))
	{
		Act1Events::triggerEvent(Act1Event::TooDarkToGo);
	}
}
