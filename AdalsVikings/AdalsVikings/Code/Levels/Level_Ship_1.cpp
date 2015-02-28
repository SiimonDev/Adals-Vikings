#include "Level_Ship_1.h"
#include "..\Logics\ResourceManager.h"
#include "..\Logics\AudioPlayer.h"
#include "..\Logics\WindowState.h"
#include <iostream>

Level_Ship_1::Level_Ship_1(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
	, mGameStart(false)
	, mOldBucketAdded(false)
	, mBrynjaFade1(false)
	, mBrynjaFade2(false)
	, mStartBrynja(false)
	, mBrynjaConv(false)
{
	mBackgroundID = LevelFolder::Ship_1;
}

void Level_Ship_1::update(sf::Time &frametime)
{
	if (KeyboardState::isPressed(sf::Keyboard::F))
	{
		mPlayer.addItemToInventory("bucket");
	}

	if(BoatEvents::hasBeenTriggered(BoatEvent::IntroScreen) && !BoatEvents::hasBeenHandled(BoatEvent::IntroScreen))
	{
		if (!mPlayer.isDestinationReached())
		{
			BoatEvents::handleEvent(BoatEvent::IntroScreen);
		}
	}

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
				RMI.unloadResource(Texture::BrynjaSleeping);
				mNpcs["Brynja"]->setIdleAnimation(Texture::BrynjaIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(5));
				mNpcs["Brynja"]->SetTalkAnimation(Texture::BrynjaTalk, sf::Vector2i(4, 1), sf::milliseconds(650), sf::Time::Zero);
				mNpcs["Brynja"]->setProportions(sf::Vector2f(290, 452));
				mNpcs["Brynja"]->setscale(sf::Vector2f(0.5f, 0.5f));
				mNpcs["Brynja"]->setPosition(sf::Vector2f(1080, 708));
				mNpcs["Brynja"]->setInteractionPosition(sf::Vector2f(940, 710));
				mNpcs["Brynja"]->updateAnimationStyle();
				mNpcs["Brynja"]->setFlip(true);
				RMI.unloadResource(Texture::BrynjaSleeping);

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

void Level_Ship_1::render(IndexRenderer &iRenderer)
{
	if (BoatEvents::hasBeenTriggered(BoatEvent::IntroScreen) && !BoatEvents::hasBeenHandled(BoatEvent::IntroScreen))
		iRenderer.addSprite(mIntroScreen, 99999);
	CurrentWindow.setView(sf::View(sf::FloatRect(0, 0, 1920, 1080)));
	Level::render(iRenderer);
}

void Level_Ship_1::load()
{
	mPortals[Ship1ToShip2] = &PortalLoader::getPortal(Ship1ToShip2); // This does not create a new portal it only references the one in PortalLoader
	mPortals[Ship1ToShip2]->setWorking(true);

	RMI.loadResource(Texture::IntroScreen);
	RMI.loadResource(Texture::ValdisSittingIdle);
	RMI.loadResource(Texture::ValdisSittingTalk);
	RMI.loadResource(Texture::LeifrSitIdle);
	RMI.loadResource(Texture::LeifrSitTalk);
	RMI.loadResource(Sound::BoatAmbient);
	RMI.loadResource(Footsteps::Hardwood);
	mCurrentFootsteps = Footsteps::Hardwood;

	mIntroScreen.setTexture(RMI.getResource(Texture::IntroScreen));
	mIntroScreen.setScale(2, 2);
	mIntroScreen.setPosition(150, 50);

	mNpcs["Valdis"] = NpcPtr(new Npc(NpcHandler::getNpc("Valdis")));
	mNpcs["Valdis"]->setIdleAnimation(Texture::ValdisSittingIdle, sf::Vector2i(2, 1), sf::milliseconds(350), sf::seconds(7));
	mNpcs["Valdis"]->SetTalkAnimation(Texture::ValdisSittingTalk, sf::Vector2i(2, 1), sf::milliseconds(400), sf::Time::Zero);
	mNpcs["Valdis"]->setProportions(sf::Vector2f(150, 134.5));
	mNpcs["Valdis"]->setscale(sf::Vector2f(1.1f, 1.1f));
	mNpcs["Valdis"]->setIndex(14);

	mNpcs["Leifr"] = NpcPtr(new Npc(NpcHandler::getNpc("Leifr")));
	mNpcs["Finnr"] = NpcPtr(new Npc(NpcHandler::getNpc("Finnr")));
	mNpcs["Brynja"] = NpcPtr(new Npc(NpcHandler::getNpc("Brynja")));
	mNpcs["Alfr"] = NpcPtr(new Npc(NpcHandler::getNpc("Alfr")));
	mNpcs["Alfr"]->setIndex(16);
	mNpcs["Leifr"]->setIdleAnimation(Texture::LeifrSitIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(5));
	mNpcs["Leifr"]->SetTalkAnimation(Texture::LeifrSitTalk, sf::Vector2i(2, 1), sf::milliseconds(350), sf::Time::Zero);

	if (!mStartBrynja)
	{
		RMI.loadResource(Texture::BrynjaIdle);
		RMI.loadResource(Texture::BrynjaTalk);
		RMI.loadResource(Texture::BrynjaSleeping);
		mNpcs["Brynja"]->setIdleAnimation(Texture::BrynjaSleeping, sf::Vector2i(3, 4), sf::milliseconds(1200), sf::milliseconds(2000));
		mNpcs["Brynja"]->SetTalkAnimation(Texture::BrynjaSleeping, sf::Vector2i(3, 4), sf::milliseconds(1400), sf::milliseconds(2000));

		mNpcs["Brynja"]->setPosition(sf::Vector2f(1080, 730));
		mNpcs["Brynja"]->setInteractionPosition(sf::Vector2f(900, 710));
		mNpcs["Brynja"]->setProportions(sf::Vector2f(504, 160));
		mNpcs["Brynja"]->setscale(sf::Vector2f(0.6f, 0.6f));
	}

	Level::load();

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

void Level_Ship_1::unload()
{
	RMI.unloadResource(Texture::IntroScreen);
	RMI.unloadResource(Texture::ValdisSittingIdle);
	RMI.unloadResource(Texture::ValdisSittingTalk);
	RMI.unloadResource(Texture::LeifrSitIdle);
	RMI.unloadResource(Texture::LeifrSitTalk);
	RMI.unloadResource(Sound::BoatAmbient);
	RMI.unloadResource(Footsteps::Hardwood);
	Level::unload();
}

void Level_Ship_1::checkInteractEvents()
{
	// Event for dropping the bucket on Leifr
	if (mDroppedItemID == "bucket" && mCurrentNPCID == "Leifr" && !BoatEvents::hasBeenTriggered(BoatEvent::GivenBucketToLeifr))
		BoatEvents::triggerEvent(BoatEvent::GivenBucketToLeifr);

	// Event for dropping the flute on Brynja
	if (mDroppedItemID == "flute" && mCurrentNPCID == "Brynja" && !BoatEvents::hasBeenTriggered(BoatEvent::DroppedFluteOnBrynja))
		BoatEvents::triggerEvent(BoatEvent::DroppedFluteOnBrynja);
}

void Level_Ship_1::checkEvents()
{
	// Event for asking Alfr to help you wake up Brynja
	if (BoatEvents::hasBeenHandled(BoatEvent::TalkedToValdis) && DialogHandler::getDialogue("Alfr").getIsOptionDisabled(3) && !BoatEvents::hasBeenTriggered(BoatEvent::FluteFromAlfr))
		BoatEvents::triggerEvent(BoatEvent::FluteFromAlfr);

	// Check if ulfrs startdialogue has been triggered
	if (!BoatEvents::hasBeenTriggered(BoatEvent::UlfrStartDialogue) && BoatEvents::hasBeenHandled(BoatEvent::StartDialogue))
		BoatEvents::triggerEvent(BoatEvent::UlfrStartDialogue);

	if (DialogHandler::getDialogue("IntroUlfr").getHasStopped() && !BoatEvents::hasBeenTriggered(BoatEvent::IntroScreen))
		BoatEvents::triggerEvent(BoatEvent::IntroScreen);

}

void Level_Ship_1::changeLevel(sf::Time &frameTime)
{
	if (mPortals[Ship1ToShip2]->getActivated())
	{
		LVLMI.changeLevel(LevelFolder::Ship_2);
	}
}