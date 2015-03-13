#include "Level_Tavern_Inside.h"
#include "..\Logics\AudioPlayer.h"
#include <iostream>

Level_Tavern_Inside::Level_Tavern_Inside(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Tavern_Inside;
}

void Level_Tavern_Inside::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Tavern_Inside_Music, true, 20);
}

void Level_Tavern_Inside::update(sf::Time &frametime)
{
	/*if (KeyboardState::isPressed(sf::Keyboard::Num1))
		mPlayer->addItemToInventory("cross");
	else if (KeyboardState::isPressed(sf::Keyboard::Num2))
		mPlayer->addItemToInventory("ropePiece");*/
	if (Act1Events::hasBeenTriggered(Act1Event::TavernInside_GetAxeHead) && !Act1Events::hasBeenHandled(Act1Event::TavernInside_GetAxeHead))
	{
		if (DialogHandler::getDialogue("Brandr_Tavern").getText() == "Not like I've got \nmuch of a choice.")
		{
			mPlayer->addItemToInventory("axeHead");
			Act1Events::handleEvent(Act1Event::TavernInside_GetAxeHead);
		}
	}

	if (Act1Events::hasBeenTriggered(Act1Event::TavernInside_GiveAxeToBrandr) && !Act1Events::hasBeenHandled(Act1Event::TavernInside_GiveAxeToBrandr))
	{
		if (true && !mFade1)
		{
			FadeI.fadeOut(frametime);
			if (FadeI.getFaded())
			{
				mPlayer->removeItemFromInventory("axe");
				mNpcs.clear();
				mFade1 = true;
			}

		}
		else if (mFade1 && !mFade2)
		{
			FadeI.fadeIn(frametime);
			if (FadeI.getFaded())
			{
				mFade2 = true;
				Act1Events::handleEvent(Act1Event::TavernInside_GiveAxeToBrandr);
			}
		}
	}
	
	Level::update(frametime);
	changeLevel();
}

void Level_Tavern_Inside::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Tavern_Inside::load()
{
	RMI.loadResource(Footsteps::Hardwood);
	mPortals[TavernInsideToTavernOutside] = &PortalLoader::getPortal(TavernInsideToTavernOutside);
	mPortals[TavernInsideToTavernOutside]->setWorking(true);

	if (!Act1Events::hasBeenHandled(Act1Event::TavernInside_GiveAxeToBrandr))
	{
		mNpcs["Brandr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Brandr")));
		mNpcs["Alfr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Alfr")));
		mNpcs["Dagny"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Dagny")));
		mNpcs["Finnr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Finnr")));
		mNpcs["Yngvarr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Yngvarr")));

		mNpcs["Brandr"]->setscale(sf::Vector2f(0.8, 0.8));
		mNpcs["Brandr"]->setPosition(sf::Vector2f(605, 930));
		mNpcs["Brandr"]->setIndex(22);
		mNpcs["Brandr"]->setFlip(true);
		mNpcs["Brandr"]->setDialogue("Brandr_Tavern");

		mNpcs["Alfr"]->setscale(sf::Vector2f(0.85f, 0.85f));
		mNpcs["Alfr"]->setPosition(sf::Vector2f(1830, 1030));
		mNpcs["Alfr"]->setIndex(22);
		mNpcs["Alfr"]->setDialogue("Alfr_Tavern");

		mNpcs["Dagny"]->setscale(sf::Vector2f(1, 1));
		mNpcs["Dagny"]->setPosition(sf::Vector2f(1390, 880));
		mNpcs["Dagny"]->setIndex(10);
		mNpcs["Dagny"]->setFlip(true);
		mNpcs["Dagny"]->setDialogue("Dagny_Tavern");

		mNpcs["Finnr"]->setscale(sf::Vector2f(0.7, 0.7));
		mNpcs["Finnr"]->setPosition(sf::Vector2f(960, 785));
		mNpcs["Finnr"]->setIndex(4);
		mNpcs["Finnr"]->setFlip(true);
		mNpcs["Finnr"]->setDialogue("Finnr_Tavern");

		mNpcs["Yngvarr"]->setscale(sf::Vector2f(0.75f, 0.75f));
		mNpcs["Yngvarr"]->setPosition(sf::Vector2f(1615, 800));
		mNpcs["Yngvarr"]->setIndex(9);
		mNpcs["Yngvarr"]->setDialogue("Yngvarr_Tavern");
	}
	Level::load();

	// Add collision from every NPC to the map
	mTileMap.addCollision(mNpcs["Brandr"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Alfr"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Dagny"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Finnr"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Yngvarr"]->getCollisionRect());

	// Add Index from every NPC to the map
	mTileMap.setIndexOnMap(mNpcs["Brandr"]->getIndexRect(), mNpcs["Brandr"]->getIndex() - 2);
	mTileMap.setIndexOnMap(mNpcs["Alfr"]->getIndexRect(), mNpcs["Alfr"]->getIndex() - 2);
	//mTileMap.setIndexOnMap(mNpcs["Dagny"]->getIndexRect(), mNpcs["Dagny"]->getIndex() - 2); // NOT NEEDED ON THIS LEVEL
	mTileMap.setIndexOnMap(mNpcs["Finnr"]->getIndexRect(), mNpcs["Finnr"]->getIndex() - 2);
	mTileMap.setIndexOnMap(mNpcs["Yngvarr"]->getIndexRect(), mNpcs["Yngvarr"]->getIndex() - 2);

	mCurrentFootsteps = Footsteps::Hardwood;
}

void Level_Tavern_Inside::unload()
{
	RMI.unloadResource(Footsteps::Hardwood);
	Level::unload();
}

void Level_Tavern_Inside::changeLevel()
{
	if (mPortals[TavernInsideToTavernOutside]->getActivated() && mPortals[TavernInsideToTavernOutside]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Tavern_Outside);
		AudioPlayer::stopHDDSound(HDDSound::Tavern_Inside_Music);
		mRestartSounds = true;
	}
}

void Level_Tavern_Inside::checkInteractEvents()
{
	if (mDroppedItemID == "axe" && mCurrentNPCID == "Brandr" && !Act1Events::hasBeenTriggered(Act1Event::TavernInside_GiveAxeToBrandr))
		Act1Events::triggerEvent(Act1Event::TavernInside_GiveAxeToBrandr);
}
void Level_Tavern_Inside::checkEvents()
{
	if (DialogHandler::getDialogue("Brandr_Tavern").getActiveConversation() && !Act1Events::hasBeenTriggered(Act1Event::TavernInside_GetAxeHead))
		Act1Events::triggerEvent(Act1Event::TavernInside_GetAxeHead);
}