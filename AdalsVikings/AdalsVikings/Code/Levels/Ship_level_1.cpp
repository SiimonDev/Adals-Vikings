#include "Ship_Level_1.h"
#include "..\Logics\ResourceManager.h"
#include "..\Logics\AudioPlayer.h"
#include "..\Logics\WindowState.h"
#include <iostream>

Ship_level_1::Ship_level_1(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
	, mGameStart(false)
	, mOldBucketAdded(false)
	, mBrynjaFade1(false)
	, mBrynjaFade2(false)
	, mStartBrynja(false)
	, mBrynjaConv(false)
{
	mBackgroundID = Backgrounds::ShipLevel1;
}

void Ship_level_1::update(sf::Time &frametime)
{
	if (BoatEvents::hasBeenTriggered(BoatEvent::UlfrStartDialogue) && !BoatEvents::hasBeenHandled(BoatEvent::UlfrStartDialogue))
	{
		if (!mGameStart)
		{
			FadeI.fadeIn(frametime);
			if (FadeI.getFaded())
			{
				DialogHandler::getDialogue("IntroUlfr").startDialogue();
				mGameStart = true;
				//FadeI.setAlpha(0);
			}
		}
		if (DialogHandler::getDialogue("IntroUlfr").getHasStopped())
		{
			BoatEvents::handleEvent(BoatEvent::UlfrStartDialogue);
		}
	}

	if (BoatEvents::hasBeenTriggered(BoatEvent::GivenBucketToLeifr) && !BoatEvents::hasBeenHandled(BoatEvent::GivenBucketToLeifr))
	{
		mPlayer.removeItemFromInventory("bucket");
		DialogHandler::startDialogue("BucketDialogue");

		BoatEvents::handleEvent(BoatEvent::GivenBucketToLeifr);
	}
	if (BoatEvents::hasBeenTriggered(BoatEvent::FluteFromAlfr) && !BoatEvents::hasBeenHandled(BoatEvent::FluteFromAlfr))
	{
		mPlayer.addItemToInventory("flute");

		BoatEvents::handleEvent(BoatEvent::FluteFromAlfr);
	}
	if (BoatEvents::hasBeenTriggered(BoatEvent::DroppedFluteOnBrynja) && !BoatEvents::hasBeenHandled(BoatEvent::DroppedFluteOnBrynja))
	{
		if (mStartBrynja == false)
		{
			//FadeI.setAlpha(0);
			DialogHandler::getDialogue("Leifr").disableOption(2);
			DialogHandler::getDialogue("Alfr").disableOption(3);
			mPlayer.removeItemFromInventory("flute");
			DialogHandler::startDialogue("BrynjaFlute");
			mStartBrynja = true;
		}

		if (DialogHandler::getDialogue("BrynjaFlute").getHasStopped() && !mBrynjaFade1)
		{
			FadeI.fadeOut(frametime);
			if (FadeI.getFaded())
			{
				RMI.unloadResource(Textures::BrynjaSleeping);
				mNpcs["Brynja"]->setIdleAnimation(Textures::BrynjaIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(5));
				mNpcs["Brynja"]->SetTalkAnimation(Textures::BrynjaTalk, sf::Vector2i(4, 1), sf::milliseconds(650), sf::Time::Zero);
				mNpcs["Brynja"]->setProportions(sf::Vector2f(290, 452));
				mNpcs["Brynja"]->setPosition(sf::Vector2f(1080, 708));
				mNpcs["Brynja"]->setInteractionPosition(sf::Vector2f(940, 710));
				mNpcs["Brynja"]->UpdateAnimationStyle();
				mNpcs["Brynja"]->setFlip(true);
				RMI.unloadResource(Textures::BrynjaSleeping);

				mBrynjaFade1 = true;
			}
		}
		else if (mBrynjaFade1 && !mBrynjaFade2)
		{
			FadeI.fadeIn(frametime);

			if (FadeI.getFaded())
			{
				//FadeI.setAlpha(0);
				mBrynjaFade2 = true;
			}
		}
		else if (mBrynjaFade2 && !mBrynjaConv)
		{
			DialogHandler::startDialogue("BrynjaConversation");
			mBrynjaConv = true;
		}

		if (DialogHandler::getDialogue("BrynjaConversation").getHasStopped() && mBrynjaConv)
		{
			mPlayer.addItemToInventory("fluteBroken");

			mPlayer.addItemToInventory("map");
			DialogHandler::getDialogue("Brandr").disableOption(2);
			BoatEvents::handleEvent(BoatEvent::GottenMap);
			BoatEvents::handleEvent(BoatEvent::DroppedFluteOnBrynja);
		}
	}
	if (DialogHandler::getDialogue("BucketDialogue").getHasStopped() && !mOldBucketAdded)
	{
		mPlayer.addItemToInventory("bucketBroken");
		mOldBucketAdded = true;
	}

	if (DialogHandler::getDialogue("Valdis").getIsOptionDisabled(2) && BoatEvents::hasBeenHandled(BoatEvent::TalkedToBrandr) && 
		!BoatEvents::hasBeenHandled(BoatEvent::TalkedToValdis) && DialogHandler::getDialogue("Valdis").getHasStopped())
	{
		DialogHandler::getDialogue("Finnr").enableOption(2);
		DialogHandler::getDialogue("Leifr").enableOption(2);
		DialogHandler::getDialogue("Alfr").enableOption(3);
		if (!mPlayer.hasItemInInventory("bucket"))
		{
			DialogHandler::getDialogue("Dagny").enableOption(2);
		}
		BoatEvents::handleEvent(BoatEvent::TalkedToValdis);
	}
	Level::update(frametime);
	changeLevel(frametime);
}

void Ship_level_1::render(IndexRenderer &iRenderer)
{
	CurrentWindow.setView(sf::View(sf::FloatRect(0, 0, 1920, 1080)));
	Level::render(iRenderer);
}

void Ship_level_1::load()
{
	mPortals[Ship1ToShip2] = &PortalLoader::getPortal(Ship1ToShip2); // This does not create a new portal it only references the one in PortalLoader

	mNpcs["Valdis"] = NpcPtr(new Npc(NpcHandler::getNpc("Valdis")));
	mNpcs["Valdis"]->setIndex(14);
	mNpcs["Leifr"] = NpcPtr(new Npc(NpcHandler::getNpc("Leifr")));
	mNpcs["Finnr"] = NpcPtr(new Npc(NpcHandler::getNpc("Finnr")));
	mNpcs["Brynja"] = NpcPtr(new Npc(NpcHandler::getNpc("Brynja")));
	mNpcs["Alfr"] = NpcPtr(new Npc(NpcHandler::getNpc("Alfr")));
	mNpcs["Alfr"]->setIndex(16);
	RMI.loadResource(Textures::LeifrSitIdle);
	RMI.loadResource(Textures::LeifrSitTalk);
	mNpcs["Leifr"]->setIdleAnimation(Textures::LeifrSitIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(5));
	mNpcs["Leifr"]->SetTalkAnimation(Textures::LeifrSitTalk, sf::Vector2i(2, 1), sf::milliseconds(350), sf::Time::Zero);
	if (!mStartBrynja)
	{
		RMI.loadResource(Textures::BrynjaIdle);
		RMI.loadResource(Textures::BrynjaTalk);
		RMI.loadResource(Textures::BrynjaSleeping);
		mNpcs["Brynja"]->setIdleAnimation(Textures::BrynjaSleeping, sf::Vector2i(3, 4), sf::milliseconds(1200), sf::milliseconds(2000));
		mNpcs["Brynja"]->SetTalkAnimation(Textures::BrynjaSleeping, sf::Vector2i(3, 4), sf::milliseconds(1400), sf::milliseconds(2000));

		mNpcs["Brynja"]->setPosition(sf::Vector2f(1080, 720));
		mNpcs["Brynja"]->setInteractionPosition(sf::Vector2f(900, 710));
		mNpcs["Brynja"]->setProportions(sf::Vector2f(504, 160));
		mNpcs["Brynja"]->setscale(sf::Vector2f(0.5f, 0.5f));
	}

	Level::load();

	RMI.loadResource(Sound::BoatAmbient);
	RMI.loadResource(Footsteps::Hardwood);
	mCurrentFootsteps = Footsteps::Hardwood;

	AudioPlayer::playSound(Sound::BoatAmbient, "boatAmbient", true);
	AudioPlayer::playMusic("assets/sounds/music/Boat_music.ogg", "boat1", true, 20);

	// Add Collision from every NPC to the map
	mTileMap.addCollision(mNpcs["Valdis"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Leifr"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Finnr"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Brynja"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Alfr"]->getCollisionRect());

	// Add Index from every NPC to the map
	mTileMap.setIndexOnMap(mNpcs["Valdis"]->getIndexRect(), mNpcs["Valdis"]->getIndex() - 1);
	mTileMap.setIndexOnMap(mNpcs["Leifr"]->getIndexRect(), mNpcs["Leifr"]->getIndex() - 1);
	mTileMap.setIndexOnMap(mNpcs["Finnr"]->getIndexRect(), mNpcs["Finnr"]->getIndex() - 1);
	mTileMap.setIndexOnMap(mNpcs["Brynja"]->getIndexRect(), mNpcs["Brynja"]->getIndex() - 1);
	mTileMap.setIndexOnMap(mNpcs["Alfr"]->getIndexRect(), mNpcs["Alfr"]->getIndex() - 1);

	mPlayer.setPosition(sf::Vector2f(1400, 750));
}

void Ship_level_1::unload()
{
	RMI.unloadResource(Textures::LeifrSitIdle);
	RMI.unloadResource(Textures::LeifrSitTalk);
	RMI.unloadResource(Sound::BoatAmbient);
	RMI.unloadResource(Footsteps::Hardwood);
	Level::unload();
}

void Ship_level_1::checkInteractEvents()
{
	// Event for dropping the bucket on Leifr
	if (mDroppedItemID == "bucket" && mCurrentNPCID == "Leifr" && !BoatEvents::hasBeenTriggered(BoatEvent::GivenBucketToLeifr))
		BoatEvents::triggerEvent(BoatEvent::GivenBucketToLeifr);

	// Event for dropping the flute on Brynja
	if (mDroppedItemID == "flute" && mCurrentNPCID == "Brynja" && !BoatEvents::hasBeenTriggered(BoatEvent::DroppedFluteOnBrynja))
		BoatEvents::triggerEvent(BoatEvent::DroppedFluteOnBrynja);
}

void Ship_level_1::checkEvents()
{
	// Event for asking Alfr to help you wake up Brynja
	if (BoatEvents::hasBeenHandled(BoatEvent::TalkedToValdis) && DialogHandler::getDialogue("Alfr").getIsOptionDisabled(3) && !BoatEvents::hasBeenTriggered(BoatEvent::FluteFromAlfr))
		BoatEvents::triggerEvent(BoatEvent::FluteFromAlfr);

	// Check if ulfrs startdialogue has been triggered
	if (!BoatEvents::hasBeenTriggered(BoatEvent::UlfrStartDialogue) && BoatEvents::hasBeenHandled(BoatEvent::StartDialogue))
		BoatEvents::triggerEvent(BoatEvent::UlfrStartDialogue);
}

void Ship_level_1::changeLevel(sf::Time &frameTime)
{
	if (mPortals[Ship1ToShip2]->getActivated())
	{
		LVLMI.changeLevel(Ship_2);
	}
}