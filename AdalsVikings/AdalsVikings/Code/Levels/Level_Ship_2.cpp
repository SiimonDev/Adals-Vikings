#include "level_Ship_2.h"
#include "..\Interface\LoadingScreen.h"
#include "..\Logics\KeyboardState.h"
#include "..\Logics\WindowState.h"
#include "..\Logics\BoatEvents.h"
#include <iostream>

Level_Ship_2::Level_Ship_2(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
	, mShowIntroScreen(false)
	, mDone(false)
	, mEnd(false)
	, mStartedGiveDialogue(false)
	, mBrandrMapFade(false)
	, mZoom(1.f)
	, mAlpha(0)
{
	mFadeRectangle.setSize(sf::Vector2f(1920, 1080));
	mFadeRectangle.setFillColor(sf::Color(0, 0, 0, mAlpha));
	mBackgroundID = LevelFolder::Ship_2;
}

void Level_Ship_2::update(sf::Time &frameTime)
{

	mSeaAnimation.animate(frameTime);
	mWaveAnimation.animate(frameTime);

	if (!BoatEvents::hasBeenHandled(BoatEvent::StartDialogue) && BoatEvents::hasBeenTriggered(BoatEvent::StartDialogue))
	{
		if (!DialogHandler::getDialogue("Intro_Ship2").getActiveConversation() && !DialogHandler::getDialogue("Intro_Ship2").getHasStopped())
			DialogHandler::startDialogue("Intro_Ship2");

		if (DialogHandler::getDialogue("Intro_Ship2").getHasStopped())
		{
			FadeI.fadeOut(frameTime);
			if (FadeI.getFaded())
			{
				LVLMI.changeLevel(LevelFolder::Ship_1);
				BoatEvents::handleEvent(BoatEvent::StartDialogue);
			}
		}
	}

	if ((mPlayer->hasItemInInventory("bucket") || mPlayer->hasItemInInventory("brokenBucket")) && !DialogHandler::getDialogue("Dagny_Ship2").getIsOptionDisabled(2))
		DialogHandler::getDialogue("Dagny_Ship2").disableOption(2);

	if (BoatEvents::hasBeenTriggered(BoatEvent::TalkedToBrandr) && !BoatEvents::hasBeenHandled(BoatEvent::TalkedToBrandr))
	{
		DialogHandler::getDialogue("Brandr_Ship2").enableOption(2);
		DialogHandler::getDialogue("Dagny_Ship2").enableOption(1);
		DialogHandler::getDialogue("Finnr_Ship1").enableOption(1);
		DialogHandler::getDialogue("Leifr_Ship1").enableOption(1);
		DialogHandler::getDialogue("Alfr_Ship1").enableOption(2);
		DialogHandler::getDialogue("Valdis_Ship1").enableOption(2);
		BoatEvents::handleEvent(BoatEvent::TalkedToBrandr);
	}
	if (!BoatEvents::hasBeenHandled(BoatEvent::GivenMapToBrandr) && BoatEvents::hasBeenTriggered(BoatEvent::GivenMapToBrandr))
	{
		if (mPlayer->hasItemInInventory("map"))
			mPlayer->removeItemFromInventory("map");

		if (!DialogHandler::getDialogue("GivenMapToBrandr_Ship").getActiveConversation() && !DialogHandler::getDialogue("GivenMapToBrandr_Ship").getHasStopped())
			DialogHandler::getDialogue("GivenMapToBrandr_Ship").startDialogue();

		if (DialogHandler::getDialogue("GivenMapToBrandr_Ship").getHasStopped())
		{
			FadeI.fadeOut(frameTime);
			if (FadeI.getFaded())
			{
				LSI.startLoading(LoadTask::LoadAct1);
				BoatEvents::handleEvent(BoatEvent::GivenMapToBrandr);
			}
		}
	}

	//runCutscene(frameTime);
	changeLevel(frameTime);
	Level::update(frameTime);
}

void Level_Ship_2::render(IndexRenderer &iRenderer)
{
	if (!BoatEvents::hasBeenHandled(BoatEvent::StartDialogue))
		CurrentWindow.setView(mCutsceneView);
	else
		CurrentWindow.setView(sf::View(sf::FloatRect(0, 0, 1920, 1080)));
	mSeaAnimation.render(iRenderer);
	mWaveAnimation.render(iRenderer);
	Level::render(iRenderer);
}

void Level_Ship_2::load()
{
	RMI.loadResource(Texture::BrandrAngryTalk);
	RMI.loadResource(Texture::BrandrAngryIdle);
	RMI.loadResource(Texture::FrontBoatWaveAnimation);
	RMI.loadResource(Texture::WaveAnimationBoat);
	mPortals[Ship2ToShip1] = &PortalLoader::getPortal(Ship2ToShip1); // This does not create a new portal it only references the one in PortalLoader;
	mPortals[Ship2ToShip1]->setWorking(true);

	mNpcs["Dagny"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Dagny")));
	mNpcs["Dagny"]->setIndex(14);

	mNpcs["Brandr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Brandr")));
	mNpcs["Brandr"]->setIndex(14);
	mNpcs["Brandr"]->SetTalkAnimation(Texture::BrandrAngryTalk, sf::Vector2i(4, 1), sf::milliseconds(550), sf::Time::Zero);
	mNpcs["Brandr"]->setIdleAnimation(Texture::BrandrAngryIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(3.7));

	mNpcs["Yngvarr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Yngvarr")));
	mNpcs["Yngvarr"]->setIndex(14);

	if (!BoatEvents::hasBeenTriggered(BoatEvent::StartDialogue))
	{
		mCutsceneView.setCenter(1920 / 2 - 100, 1080 / 2);
		mCutsceneView.setSize(1920, 1080);
		mCutsceneView.zoom(0.4);
		mNpcs["Brandr"]->setFlip(false);
		mNpcs["Yngvarr"]->setFlip(true);
	}
	else
	{
		mNpcs["Brandr"]->setFlip(true);
		mNpcs["Yngvarr"]->setFlip(false);
	}
	Level::load();

	// Add collision from every NPC to the map
	mTileMap.addCollision(mNpcs["Dagny"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Brandr"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Yngvarr"]->getCollisionRect());

	// Add Index from every NPC to the map
	mTileMap.setIndexOnMap(mNpcs["Dagny"]->getIndexRect(), mNpcs["Dagny"]->getIndex() - 1);
	mTileMap.setIndexOnMap(mNpcs["Brandr"]->getIndexRect(), mNpcs["Brandr"]->getIndex() - 1);
	mTileMap.setIndexOnMap(mNpcs["Yngvarr"]->getIndexRect(), mNpcs["Yngvarr"]->getIndex() - 1);

	//Set Dialogues
	mNpcs["Dagny"]->setDialogue("Dagny_Ship2");
	mNpcs["Brandr"]->setDialogue("Brandr_Ship2");
	mNpcs["Yngvarr"]->setDialogue("Yngvarr_Ship2");

	mSeaAnimation.load(RMI.getResource(Texture::WaveAnimationBoat), sf::Vector2i(6, 12), sf::seconds(12), sf::seconds(0), true);
	mSeaAnimation.setIndex(2);
	mSeaAnimation.getSprite().setOrigin(0, 0);
	mSeaAnimation.setProportions(sf::Vector2f(1920, 600));
	mSeaAnimation.setPosition(sf::Vector2f(0, 240));

	mWaveAnimation.load(RMI.getResource(Texture::FrontBoatWaveAnimation), sf::Vector2i(2, 2), sf::seconds(1), sf::seconds(0), true);
	mWaveAnimation.setIndex(200);
	mWaveAnimation.setProportions(sf::Vector2f(1440, 60));
	mWaveAnimation.getSprite().setOrigin(mWaveAnimation.getSprite().getTextureRect().width, mWaveAnimation.getSprite().getTextureRect().height);
	mWaveAnimation.setPosition(sf::Vector2f(1920, 1080));

	mCurrentFootsteps = Footsteps::Hardwood;
}

void Level_Ship_2::unload()
{
	RMI.unloadResource(Texture::BrandrAngryTalk);
	RMI.unloadResource(Texture::BrandrAngryIdle);
	RMI.unloadResource(Texture::FrontBoatWaveAnimation);
	RMI.unloadResource(Texture::WaveAnimationBoat);
	Level::unload();
}

void Level_Ship_2::changeLevel(sf::Time &frameTime)
{
	if (mPortals[Ship2ToShip1]->getActivated() && mPortals[Ship2ToShip1]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Ship_1);
	}
}

void Level_Ship_2::runCutscene(sf::Time &frameTime)
{
	/*if (!BoatEvents::hasBeenHandled(BoatEvent::StartDialogue) && BoatEvents::hasBeenTriggered(BoatEvent::StartDialogue))
	{
		if (!DialogHandler::getDialogue("Intro_Ship2").getActiveConversation() && !DialogHandler::getDialogue("Intro_Ship2").getHasStopped())
			DialogHandler::getDialogue("Intro_Ship2").startDialogue();

		if (DialogHandler::getDialogue("Intro_Ship2").getHasStopped())
		{
			FadeI.fadeOut(frameTime);
			if (FadeI.getFaded())
			{
				LVLMI.changeLevel(LevelFolder::Ship_1);
				BoatEvents::handleEvent(BoatEvent::StartDialogue);
			}
		}
	}*/
}

void Level_Ship_2::checkInteractEvents()
{
	if (mDroppedItemID == "map" && mCurrentNPCID == "Brandr" && !BoatEvents::hasBeenTriggered(BoatEvent::GivenMapToBrandr))
		BoatEvents::triggerEvent(BoatEvent::GivenMapToBrandr);
}

void Level_Ship_2::checkEvents()
{
	if (!BoatEvents::hasBeenTriggered(BoatEvent::StartDialogue))
		BoatEvents::triggerEvent(BoatEvent::StartDialogue);

	if (!BoatEvents::hasBeenTriggered(BoatEvent::TalkedToBrandr) && DialogHandler::getDialogue("Brandr_Ship2").getHasStopped())
		BoatEvents::triggerEvent(BoatEvent::TalkedToBrandr);
}