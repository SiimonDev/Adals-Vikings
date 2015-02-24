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
	mFolderPath = "Assets/MapFiles/Ship1/";
	mLevelID = TextureFolder::ShipLevel1;
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
				FadeI.setAlpha(1);
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
			FadeI.setAlpha(1);
			FadeI.setFadeDuration(sf::seconds(1));
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
				RMI.unload(Textures::BrynjaIdle);
				RMI.unload(Textures::BrynjaTalk);
				RMI.load(Textures::BrynjaIdle, "assets/Images/Brynja/character_brynja_blink.png");
				RMI.load(Textures::BrynjaTalk, "assets/Images/Brynja/character_brynja_talk.png");
				FadeI.setAlpha(254);

				mNpcs["Brynja"]->setIdleAnimation(Textures::BrynjaIdle, "assets/Images/Brynja/character_brynja_blink.png", sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(5));
				mNpcs["Brynja"]->SetTalkAnimation(Textures::BrynjaTalk, "assets/Images/Brynja/character_brynja_talk.png", sf::Vector2i(4, 1), sf::milliseconds(650), sf::Time::Zero);
				mNpcs["Brynja"]->setProportions(sf::Vector2f(290, 452));
				mNpcs["Brynja"]->setPosition(sf::Vector2f(1080, 620));
				mBrynjaFade1 = true;
			}
		}
		else if (mBrynjaFade1 && !mBrynjaFade2)
		{
			FadeI.setFadeDuration(sf::seconds(2));
			FadeI.fadeIn(frametime);

			if (FadeI.getFaded())
			{
				FadeI.setAlpha(0);
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
	mPortals[Portal1] = &PortalLoader::getPortal(Portal1); // This does not create a new portal it only references the one in PortalLoader

	mNpcs["Valdis"] = NpcPtr(new Npc(NpcHandler::getNpc("Valdis")));
	mNpcs["Valdis"]->setIndex(14);
	mNpcs["Leifr"] = NpcPtr(new Npc(NpcHandler::getNpc("Leifr")));
	mNpcs["Finnr"] = NpcPtr(new Npc(NpcHandler::getNpc("Finnr")));
	mNpcs["Brynja"] = NpcPtr(new Npc(NpcHandler::getNpc("Brynja")));
	mNpcs["Alfr"] = NpcPtr(new Npc(NpcHandler::getNpc("Alfr")));
	mNpcs["Alfr"]->setIndex(16);

	if (!mStartBrynja)
	{
		RMI.unload(Textures::BrynjaIdle);
		RMI.unload(Textures::BrandrTalk);
		RMI.load(Textures::BrynjaIdle, "assets/images/Brynja/character_brynja_sleeping.png");
		RMI.load(Textures::BrynjaTalk, "assets/images/Brynja/character_brynja_sleeping.png");
		mNpcs["Brynja"]->setIdleAnimation(Textures::BrynjaIdle, "assets/images/Brynja/character_brynja_sleeping.png", sf::Vector2i(3, 4), sf::milliseconds(1200), sf::milliseconds(2000));
		mNpcs["Brynja"]->SetTalkAnimation(Textures::BrynjaTalk, "assets/images/Brynja/character_brynja_sleeping.png", sf::Vector2i(3, 4), sf::milliseconds(1400), sf::milliseconds(2000));
		mNpcs["Brynja"]->setPosition(sf::Vector2f(1080, 680));
		mNpcs["Brynja"]->setProportions(sf::Vector2f(504, 160));
		mNpcs["Brynja"]->setscale(sf::Vector2f(0.5f, 0.5f));
	}

	Level::load();

	RMI.load(Sound::BoatAmbient, "assets/sounds/Boat.wav");
	RMI.load(SoundFolder::Hardwood, "assets/sounds/footsteps/Hardwood/");
	mCurrentStepSound = SoundFolder::Hardwood;

	AudioPlayer::playSound(Sound::BoatAmbient, "boatAmbient", true);
	AudioPlayer::playMusic("assets/sounds/music/Theme2.ogg", "boat1", true, 20);

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
	RMI.unload(Sound::BoatAmbient);
	RMI.unload(SoundFolder::Hardwood);
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
	if (mPortals[Portal1]->getActivated())
	{
		LVLMI.changeLevel(Ship_2);
	}
}