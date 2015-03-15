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
	if (Act1Events::hasBeenTriggered(Act1Event::TooDarkToGo) && !Act1Events::hasBeenHandled(Act1Event::TooDarkToGo))
	{
		if (!DialogHandler::getDialogue("Ulfr_Cavern").getActiveConversation() && !DialogHandler::getDialogue("Ulfr_Cavern").getHasStopped())
			DialogHandler::getDialogue("Ulfr_Cavern").startDialogue();
		if (DialogHandler::getDialogue("Ulfr_Cavern").getHasStopped())
		{
			LVLMI.changeLevel(LevelFolder::Cliffs_Down);
			Act1Events::hasBeenHandled(Act1Event::TooDarkToGo);
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

}
void Level_Cavern_Right::checkEvents()
{
	if (!Act1Events::hasBeenHandled(Act1Event::GotCandleLight) && !Act1Events::hasBeenTriggered(Act1Event::TooDarkToGo))
	{
		Act1Events::triggerEvent(Act1Event::TooDarkToGo);
	}
}
