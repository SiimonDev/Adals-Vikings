#include "Ship_level_2.h"
#include "..\Interface\LoadingScreen.h"
#include "..\Logics\KeyboardState.h"
#include "..\Logics\WindowState.h"
#include "..\Logics\BoatEvents.h"
#include <iostream>

Ship_level_2::Ship_level_2(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
	, mGameStart(false)
	, mDone(false)
	, mEnd(false)
	, mStartedGiveDialogue(false)
	, mBrandrMapFade(false)
	, mZoom(1.f)
	, mAlpha(0)
{
	mFolderPath = "Assets/MapFiles/Ship2/";
	mFadeRectangle.setSize(sf::Vector2f(1920, 1080));
	mFadeRectangle.setFillColor(sf::Color(0, 0, 0, mAlpha));
	mLevelID = TextureFolder::ShipLevel2;
}

void Ship_level_2::update(sf::Time &frametime)
{
	if (KeyboardState::isPressed(sf::Keyboard::F))
	{
		mPlayer.addItemToInventory("map");
	}
	if (BoatEvents::hasBeenTriggered(BoatEvent::PickedUpBucket) && !BoatEvents::hasBeenHandled(BoatEvent::PickedUpBucket))
	{
		DialogHandler::getDialogue("Dagny").disableOption(2);
		BoatEvents::handleEvent(BoatEvent::PickedUpBucket);
	}
	if (DialogHandler::getDialogue("Brandr").getHasStopped() && !BoatEvents::hasBeenHandled(BoatEvent::TalkedToBrandr))
	{
		DialogHandler::getDialogue("Brandr").enableOption(2);
		DialogHandler::getDialogue("Dagny").enableOption(1);
		DialogHandler::getDialogue("Finnr").enableOption(1);
		DialogHandler::getDialogue("Leifr").enableOption(1);
		DialogHandler::getDialogue("Alfr").enableOption(2);
		DialogHandler::getDialogue("Valdis").enableOption(2);
		BoatEvents::handleEvent(BoatEvent::TalkedToBrandr);
	}
	if (!BoatEvents::hasBeenHandled(BoatEvent::GivenMapToBrandr) && BoatEvents::hasBeenTriggered(BoatEvent::GivenMapToBrandr))
	{
		mPlayer.removeItemFromInventory("map");
		if (!mStartedGiveDialogue)
		{
			DialogHandler::getDialogue("GivenMapToBrandr").startDialogue();
			mStartedGiveDialogue = true;
		}
		if (DialogHandler::getDialogue("GivenMapToBrandr").getHasStopped())
		{
			FadeI.fadeOut(frametime);
			if (FadeI.getFaded())
			{
				BoatEvents::handleEvent(BoatEvent::GivenMapToBrandr);
			}
		}
	}
	runCutscene(frametime);
	changeLevel(frametime);
	Level::update(frametime);
}

void Ship_level_2::render(IndexRenderer &iRenderer)
{
	if (!BoatEvents::hasBeenHandled(BoatEvent::StartDialogue))
	{
		CurrentWindow.setView(mCutsceneView);
	}
	else
	{
		CurrentWindow.setView(sf::View(sf::FloatRect(0, 0, 1920, 1080)));
	}
	Level::render(iRenderer);
}

void Ship_level_2::load()
{

	DialogHandler::load("assets/mapfiles/Ship2/Dialogues.txt");
	mPortals[Portal2] = LPortalPtr(new Portal(PortalLoader::getPortal(Portal2)));

	mNpcs["Dagny"] = LNpcPtr(new Npc(NpcHandler::getNpc("Dagny")));
	mNpcs["Dagny"]->setIndex(11);

	mNpcs["Brandr"] = LNpcPtr(new Npc(NpcHandler::getNpc("Brandr")));
	mNpcs["Brandr"]->setIndex(13);

	mNpcs["Yngvarr"] = LNpcPtr(new Npc(NpcHandler::getNpc("Yngvarr")));
	mNpcs["Yngvarr"]->setIndex(13);

	if (!BoatEvents::hasBeenTriggered(BoatEvent::StartDialogue))
	{
		mCutsceneView.setCenter(1920 / 2 - 100, 1080 / 2);
		mCutsceneView.setSize(1920, 1080);
		mCutsceneView.zoom(0.4);
		mNpcs["Brandr"]->setRightWay(false);
		mNpcs["Yngvarr"]->setRightWay(true);
	}
	else
	{
		mNpcs["Brandr"]->setRightWay(true);
		mNpcs["Yngvarr"]->setRightWay(false);
	}
	Level::load();

	mTileMap.addCollision(mNpcs["Dagny"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Brandr"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Yngvarr"]->getCollisionRect());
}

void Ship_level_2::unload()
{
	Level::unload();
}

void Ship_level_2::changeLevel(sf::Time &frameTime)
{
	if (mPortals[Portal2]->getActivated())
	{
		LVLMI.changeLevel(Ship_1);
	}
	else if (BoatEvents::hasBeenHandled(BoatEvent::GivenMapToBrandr) && BoatEvents::hasBeenTriggered(BoatEvent::GivenMapToBrandr))
	{
		LSI.startLoading(LoadTask::LoadAct1);
	}
	else if (BoatEvents::hasBeenHandled(BoatEvent::StartDialogue) && BoatEvents::hasBeenTriggered(BoatEvent::StartDialogue) && !BoatEvents::hasBeenHandled(BoatEvent::UlfrStartDialogue))
		LVLMI.changeLevel(Ship_1);
}

void Ship_level_2::runCutscene(sf::Time &frameTime)
{
	if (!BoatEvents::hasBeenHandled(BoatEvent::StartDialogue) && BoatEvents::hasBeenTriggered(BoatEvent::StartDialogue))
	{
		if (!mDone)
		{
			FadeI.setAlpha(1);
			DialogHandler::getDialogue("Intro").startDialogue();
			mDone = true;
		}
		if (DialogHandler::getDialogue("Intro").getHasStopped())
		{
			FadeI.fadeOut(frameTime);
			if (FadeI.getFaded())
			{
				FadeI.setAlpha(254);
				BoatEvents::handleEvent(BoatEvent::StartDialogue);
			}
		}
	}
}

void Ship_level_2::checkInteractEvents()
{
	if (mDroppedItemID == "map" && mCurrentNPCID == "Brandr" && !BoatEvents::hasBeenTriggered(BoatEvent::GivenMapToBrandr))
		BoatEvents::triggerEvent(BoatEvent::GivenMapToBrandr);

}

void Ship_level_2::checkEvents()
{
	if (!BoatEvents::hasBeenTriggered(BoatEvent::StartDialogue))
		BoatEvents::triggerEvent(BoatEvent::StartDialogue);

}