#include "Level_Ship_1.h"
#include "..\Logics\ResourceManager.h"
#include "..\Logics\AudioPlayer.h"
#include "..\Logics\WindowState.h"
#include <iostream>

Level_Ship_1::Level_Ship_1(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
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
	mSeaAnimation.animate(frametime);
	mWaveAnimation.animate(frametime);
	mRopeAnimation.animate(frametime);

	if (BoatEvents::hasBeenTriggered(BoatEvent::IntroScreen) && !BoatEvents::hasBeenHandled(BoatEvent::IntroScreen))
	{
		mHud->displayHelp(true);
		BoatEvents::handleEvent(BoatEvent::IntroScreen);
	}

	if (BoatEvents::hasBeenTriggered(BoatEvent::UlfrStartDialogue) && !BoatEvents::hasBeenHandled(BoatEvent::UlfrStartDialogue))
	{
		if (!mGameStart)
		{
			mPlayer->setPosition(sf::Vector2f(1400, 750));
			FadeI.fadeIn(frametime);
			if (FadeI.getFaded())
			{
				if (!DialogHandler::getDialogue("IntroUlfr_Ship1").getActiveConversation() && !DialogHandler::getDialogue("IntroUlfr_Ship1").getHasStopped())
					DialogHandler::startDialogue("IntroUlfr_Ship1");
				mGameStart = true;
			}
		}
		if (DialogHandler::getDialogue("IntroUlfr_Ship1").getHasStopped())
			BoatEvents::handleEvent(BoatEvent::UlfrStartDialogue);
	}

	if (BoatEvents::hasBeenTriggered(BoatEvent::GivenBucketToLeifr) && !BoatEvents::hasBeenHandled(BoatEvent::GivenBucketToLeifr))
	{
		if (mPlayer->hasItemInInventory("bucket"))
			mPlayer->removeItemFromInventory("bucket");
		if (!DialogHandler::getDialogue("BucketDialogue_Ship1").getActiveConversation() && !DialogHandler::getDialogue("BucketDialogue_Ship1").getHasStopped())
			DialogHandler::startDialogue("BucketDialogue_Ship1");

		if (DialogHandler::getDialogue("BucketDialogue_Ship1").getHasStopped())
		{
			if (!mBucketFade1)
			{
				FadeI.fadeOut(frametime);
				if (FadeI.getFaded())
				{
					if (!FadeI.getWait())
					{
						AudioPlayer::playSound(Sound::BucketBreak, "Leifr", false);
						FadeI.setWaitDuration(sf::seconds(2));
					}
					FadeI.wait(frametime);
					if (FadeI.getFinishedWaiting())
					{
						mBucketFade1 = true;
					}
				}
			}
			if (mBucketFade1 && !mBucketFade2)
			{
				FadeI.fadeIn(frametime);

				if (FadeI.getFaded())
				{
					DialogHandler::startDialogue("BucketDialogue2_Ship1");
					mBucketFade2 = true;
				}
			}
		}
			if (DialogHandler::getDialogue("BucketDialogue2_Ship1").getHasStopped())
			{
				mPlayer->addItemToInventory("bucketBroken");
				BoatEvents::handleEvent(BoatEvent::GivenBucketToLeifr);
			}
	}
	if (BoatEvents::hasBeenTriggered(BoatEvent::FluteFromAlfr) && !BoatEvents::hasBeenHandled(BoatEvent::FluteFromAlfr))
	{
		mPlayer->addItemToInventory("flute");
		BoatEvents::handleEvent(BoatEvent::FluteFromAlfr);
	}
	if (BoatEvents::hasBeenTriggered(BoatEvent::DroppedFluteOnBrynja) && !BoatEvents::hasBeenHandled(BoatEvent::DroppedFluteOnBrynja))
	{
		if (mPlayer->hasItemInInventory("flute"))
		{
			DialogHandler::getDialogue("Leifr_Ship1").disableOption(2);
			DialogHandler::getDialogue("Alfr_Ship1").disableOption(3);
			mPlayer->removeItemFromInventory("flute");
			DialogHandler::startDialogue("BrynjaFlute_Ship1");
		}

		if (DialogHandler::getDialogue("BrynjaFlute_Ship1").getHasStopped())
		{
			if (!mBrynjaFade1)
			{
				FadeI.fadeOut(frametime);
				if (FadeI.getFaded())
				{
					if (!FadeI.getWait())
					{
						AudioPlayer::playSound(Sound::ValdisHitBrynja, "Valdis", false, 30.f);
						FadeI.setWaitDuration(sf::seconds(1));
					}
					FadeI.wait(frametime);
					if (FadeI.getFinishedWaiting())
					{
						RMI.unloadResource(Texture::BrynjaSleeping);
						RMI.loadResource(Texture::ValdisIdle);
						RMI.loadResource(Texture::ValdisTalk);
						mNpcs["Brynja"]->setIdleAnimation(Texture::BrynjaIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(5));
						mNpcs["Brynja"]->SetTalkAnimation(Texture::BrynjaTalk, sf::Vector2i(4, 1), sf::milliseconds(650), sf::Time::Zero);
						mNpcs["Brynja"]->setScale(sf::Vector2f(0.5f, 0.5f));
						mNpcs["Brynja"]->setPosition(sf::Vector2f(1080, 718));
						mNpcs["Brynja"]->setInteractionPosition(sf::Vector2f(940, 710));
						mNpcs["Brynja"]->setDialogue("BrynjaAwake_ship");
						mNpcs["Brynja"]->setFlip(true);
						mNpcs["Brynja"]->updateAnimationStyle();

						mNpcs["Valdis"]->setIdleAnimation(Texture::ValdisIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(5));
						mNpcs["Valdis"]->SetTalkAnimation(Texture::ValdisTalk, sf::Vector2i(2, 1), sf::milliseconds(650), sf::Time::Zero);
						mNpcs["Valdis"]->setPosition(sf::Vector2f(1230, 723));
						mNpcs["Valdis"]->setScale(sf::Vector2f(0.5f, 0.5f));
						mNpcs["Valdis"]->updateAnimationStyle();

						mBrynjaFade1 = true;
					}
				}
			}
		}
		if (mBrynjaFade1 && !mBrynjaFade2)
		{
			FadeI.fadeIn(frametime);

			if (FadeI.getFaded()){
				mBrynjaFade2 = true;
			}
		}
		if (mBrynjaFade2 && !DialogHandler::getDialogue("BrynjaConversation_Ship1").getActiveConversation() && !DialogHandler::getDialogue("BrynjaConversation_Ship1").getHasStopped())
			DialogHandler::startDialogue("BrynjaConversation_Ship1");

		if (DialogHandler::getDialogue("BrynjaConversation_Ship1").getHasStopped())
		{
			mPlayer->addItemToInventory("fluteBroken");
			mPlayer->addItemToInventory("map");
			DialogHandler::getDialogue("Brandr_Ship2").disableOption(2);
			if (!BoatEvents::hasBeenTriggered(BoatEvent::GottenMap))
			{
				BoatEvents::triggerEvent(BoatEvent::GottenMap);
				BoatEvents::handleEvent(BoatEvent::GottenMap);
			}
			BoatEvents::handleEvent(BoatEvent::DroppedFluteOnBrynja);
		}
	}

	if (BoatEvents::hasBeenTriggered(BoatEvent::TalkedToValdis) && !BoatEvents::hasBeenHandled(BoatEvent::TalkedToValdis))
	{
		DialogHandler::getDialogue("Finnr_Ship1").enableOption(2);
		DialogHandler::getDialogue("Leifr_Ship1").enableOption(2);
		DialogHandler::getDialogue("Alfr_Ship1").enableOption(3);
		if (!mPlayer->hasItemInInventory("bucket") || !mPlayer->hasItemInInventory("brokenBucket"))
			DialogHandler::getDialogue("Dagny_Ship2").enableOption(2);
		BoatEvents::handleEvent(BoatEvent::TalkedToValdis);
	}
	Level::update(frametime);
	changeLevel(frametime);
}

void Level_Ship_1::render(IndexRenderer &iRenderer)
{
	CurrentWindow.setView(sf::View(sf::FloatRect(0, 0, 1920, 1080)));
	mSeaAnimation.render(iRenderer);
	mWaveAnimation.render(iRenderer);
	mRopeAnimation.render(iRenderer);
	Level::render(iRenderer);
}

void Level_Ship_1::load()
{
	mPortals[Ship1ToShip2] = &PortalLoader::getPortal(Ship1ToShip2); // This does not create a new portal it only references the one in PortalLoader
	mPortals[Ship1ToShip2]->setWorking(true);

	RMI.loadResource(Texture::IntroScreen);
	RMI.loadResource(Texture::BackBoatRopeAnimation);
	RMI.loadResource(Texture::BackBoatWaveAnimation);
	RMI.loadResource(Texture::WaveAnimationBoat);
	RMI.loadResource(Footsteps::Hardwood);
	RMI.loadResource(Sound::BucketBreak);
	RMI.loadResource(Sound::ValdisHitBrynja);

	mNpcs["Leifr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Leifr")));
	mNpcs["Finnr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Finnr")));
	mNpcs["Brynja"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Brynja")));
	mNpcs["Alfr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Alfr")));

	mNpcs["Valdis"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Valdis")));
	mNpcs["Valdis"]->setIndex(14);

	mNpcs["Alfr"]->setIndex(16);

	mNpcs["Leifr"]->setIdleAnimation(Texture::LeifrSitIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(5));
	mNpcs["Leifr"]->SetTalkAnimation(Texture::LeifrSitTalk, sf::Vector2i(2, 1), sf::milliseconds(350), sf::Time::Zero);
	mNpcs["Leifr"]->setScale(sf::Vector2f(0.5f, 0.5f));

	if (!BoatEvents::hasBeenHandled(BoatEvent::DroppedFluteOnBrynja))
	{
		RMI.loadResource(Texture::BrynjaIdle);
		RMI.loadResource(Texture::BrynjaTalk);
		RMI.loadResource(Texture::BrynjaSleeping);
		mNpcs["Brynja"]->setIdleAnimation(Texture::BrynjaSleeping, sf::Vector2i(3, 4), sf::milliseconds(1200), sf::milliseconds(2000));
		mNpcs["Brynja"]->SetTalkAnimation(Texture::BrynjaSleeping, sf::Vector2i(3, 4), sf::milliseconds(1400), sf::milliseconds(2000));
		mNpcs["Brynja"]->setPosition(sf::Vector2f(1080, 730));
		mNpcs["Brynja"]->setInteractionPosition(sf::Vector2f(900, 710));
		mNpcs["Brynja"]->setScale(sf::Vector2f(0.6f, 0.6f));
		mNpcs["Brynja"]->setDialogue("Brynja_Ship1");

		mNpcs["Valdis"]->setIdleAnimation(Texture::ValdisSittingIdle, sf::Vector2i(2, 1), sf::milliseconds(350), sf::seconds(7));
		mNpcs["Valdis"]->SetTalkAnimation(Texture::ValdisSittingTalk, sf::Vector2i(2, 1), sf::milliseconds(400), sf::Time::Zero);
		mNpcs["Valdis"]->setScale(sf::Vector2f(0.3f, 0.3f));
	}
	else
	{
		RMI.loadResource(Texture::BrynjaIdle);
		RMI.loadResource(Texture::BrynjaTalk);
		RMI.loadResource(Texture::ValdisIdle);
		RMI.loadResource(Texture::ValdisTalk);
		mNpcs["Valdis"]->setIdleAnimation(Texture::ValdisIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(5));
		mNpcs["Valdis"]->SetTalkAnimation(Texture::ValdisTalk, sf::Vector2i(4, 1), sf::milliseconds(650), sf::Time::Zero);
		mNpcs["Valdis"]->setScale(sf::Vector2f(0.5f, 0.5f));
		mNpcs["Valdis"]->setPosition(sf::Vector2f(1230, 723));
		mNpcs["Brynja"]->setIdleAnimation(Texture::BrynjaIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(5));
		mNpcs["Brynja"]->SetTalkAnimation(Texture::BrynjaTalk, sf::Vector2i(4, 1), sf::milliseconds(650), sf::Time::Zero);
		mNpcs["Brynja"]->setDialogue("BrynjaAwake_ship");
		mNpcs["Brynja"]->setScale(sf::Vector2f(0.5f, 0.5f));
		mNpcs["Brynja"]->setPosition(sf::Vector2f(1080, 718));
		mNpcs["Brynja"]->setInteractionPosition(sf::Vector2f(940, 710));
		mNpcs["Brynja"]->updateAnimationStyle();
		mNpcs["Brynja"]->setFlip(true);
	}

	Level::load();

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

	//Set Dialogues
	mNpcs["Valdis"]->setDialogue("Valdis_Ship1");
	mNpcs["Leifr"]->setDialogue("Leifr_Ship1");
	mNpcs["Finnr"]->setDialogue("Finnr_Ship1");
	mNpcs["Alfr"]->setDialogue("Alfr_Ship1");
	mNpcs["Brynja"]->setDialogue("Brynja_Ship1");

	/*if (!BoatEvents::hasBeenHandled(BoatEvent::UlfrStartDialogue))
		mPlayer->setPosition(sf::Vector2f(1400, 750));*/

	mSeaAnimation.load(RMI.getResource(Texture::WaveAnimationBoat), sf::Vector2i(6, 12), sf::seconds(12), sf::seconds(0), true);
	mSeaAnimation.setIndex(2);
	mSeaAnimation.getSprite().setOrigin(0, 0);
	mSeaAnimation.setProportions(sf::Vector2f(1920, 600));
	mSeaAnimation.setPosition(sf::Vector2f(0, 240));

	mWaveAnimation.load(RMI.getResource(Texture::BackBoatWaveAnimation), sf::Vector2i(2, 2), sf::seconds(1), sf::seconds(0), true);
	mWaveAnimation.setIndex(200);
	mWaveAnimation.setProportions(sf::Vector2f(1920, 120));
	mWaveAnimation.getSprite().setOrigin(mWaveAnimation.getSprite().getTextureRect().width, mWaveAnimation.getSprite().getTextureRect().height);
	mWaveAnimation.setPosition(sf::Vector2f(1920, 1080));

	mRopeAnimation.load(RMI.getResource(Texture::BackBoatRopeAnimation), sf::Vector2i(4, 1), sf::seconds(1.5), sf::seconds(0), true);
	mRopeAnimation.setIndex(11);
	mRopeAnimation.setProportions(sf::Vector2f(485, 494));
	mRopeAnimation.setPosition(sf::Vector2f(155, 215));

	mCurrentFootsteps = Footsteps::Hardwood;
}

void Level_Ship_1::unload()
{
	RMI.unloadResource(Texture::IntroScreen);
	RMI.unloadResource(Texture::BackBoatRopeAnimation);
	RMI.unloadResource(Texture::BackBoatWaveAnimation);
	RMI.unloadResource(Texture::WaveAnimationBoat);
	RMI.unloadResource(Footsteps::Hardwood);
	RMI.unloadResource(Texture::BrynjaIdle);
	RMI.unloadResource(Texture::BrynjaTalk);
	RMI.unloadResource(Texture::ValdisIdle);
	RMI.unloadResource(Texture::ValdisTalk);
	RMI.unloadResource(Sound::BucketBreak);
	RMI.unloadResource(Sound::ValdisHitBrynja);
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
	if (BoatEvents::hasBeenHandled(BoatEvent::TalkedToValdis) && DialogHandler::getDialogue("Alfr_Ship1").getIsOptionDisabled(3) && !BoatEvents::hasBeenTriggered(BoatEvent::FluteFromAlfr))
		BoatEvents::triggerEvent(BoatEvent::FluteFromAlfr);

	// Check if ulfrs startdialogue has been triggered
	if (!BoatEvents::hasBeenTriggered(BoatEvent::UlfrStartDialogue))
		BoatEvents::triggerEvent(BoatEvent::UlfrStartDialogue);

	if (DialogHandler::getDialogue("IntroUlfr_Ship1").getHasStopped() && !BoatEvents::hasBeenTriggered(BoatEvent::IntroScreen))
		BoatEvents::triggerEvent(BoatEvent::IntroScreen);

	if (BoatEvents::hasBeenHandled(BoatEvent::TalkedToBrandr) && !BoatEvents::hasBeenTriggered(BoatEvent::TalkedToValdis) &&
		DialogHandler::getDialogue("Valdis_Ship1").getIsOptionDisabled(2) && DialogHandler::getDialogue("Valdis_Ship1").getHasStopped())
		BoatEvents::triggerEvent(BoatEvent::TalkedToValdis);

}

void Level_Ship_1::changeLevel(sf::Time &frameTime)
{
	if (mPortals[Ship1ToShip2]->getActivated() && mPortals[Ship1ToShip2]->getWorking())
		LVLMI.changeLevel(LevelFolder::Ship_2);
}