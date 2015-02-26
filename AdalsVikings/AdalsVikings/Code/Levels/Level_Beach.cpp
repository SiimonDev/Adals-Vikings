#include "Level_Beach.h"
#include "..\Logics\ResourceManager.h"
#include "..\Logics\AudioPlayer.h"
#include "..\Interface\LoadingScreen.h"
#include "..\Logics\KeyboardState.h"
#include "..\Logics\WindowState.h"
#include <iostream>

Level_Beach::Level_Beach(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
	, mIntroFade1(false)
{
	mBackgroundID = LevelFolder::Beach;
}

void Level_Beach::update(sf::Time &frametime)
{
	introCutscene(frametime);
	talkToNpcs();
	endingCutscene(frametime);

	mWaveAnimation.animate(frametime);
	Level::update(frametime);
	changeLevel();
}

void Level_Beach::render(IndexRenderer &iRenderer)
{
	if (!Act1Events::hasBeenHandled(Act1Event::Beach_Intro))
		CurrentWindow.setView(mCutSceneView);

	mWaveAnimation.render(iRenderer);
	Level::render(iRenderer);
}

void Level_Beach::load()
{
	
	mPortals[BeachToRoad] = &PortalLoader::getPortal(BeachToRoad);
	mPortals[BeachToRoad]->setCannotDialogue("I cannot go there yet!");
	mPortals[BeachToRoad]->setWorking(true);
	if (!Act1Events::hasBeenTriggered(Act1Event::Beach_Intro) && !Act1Events::hasBeenHandled(Act1Event::Beach_Intro))
	{
		mCutSceneView.setCenter(1920 / 2 - 450, 1080 / 2 + 270);
		mCutSceneView.setSize(1920, 1080);
		mCutSceneView.zoom(0.5);

		//FadeI.setAlpha(255);

		mNpcs["Seagull"] = NpcPtr(new Npc(NpcHandler::getNpc("Seagull")));
		mNpcs["Brandr"] = NpcPtr(new Npc(NpcHandler::getNpc("Brandr")));
		mNpcs["Brynja"] = NpcPtr(new Npc(NpcHandler::getNpc("Brynja")));
		mNpcs["Valdis"] = NpcPtr(new Npc(NpcHandler::getNpc("Valdis")));

		mPlayer.setPosition(sf::Vector2f(410, 1070));
		mPlayer.setFlip(true);
		mPlayer.UpdateAnimationStyle();

		mNpcs["Brandr"]->setFlip(true);
		mNpcs["Brandr"]->setscale(sf::Vector2f(0.4, 0.4));
		mNpcs["Brandr"]->setPosition(sf::Vector2f(400, 1120));
		mNpcs["Brandr"]->setDialogue("IntroDialogue");
		mNpcs["Brandr"]->setIndex(5);

		mNpcs["Brynja"]->setFlip(false);
		mNpcs["Brynja"]->setscale(sf::Vector2f(0.4, 0.4));
		mNpcs["Brynja"]->setPosition(sf::Vector2f(600, 1070));
		mNpcs["Brynja"]->setDialogue("IntroDialogue");
		mNpcs["Brynja"]->setIndex(4);

		mNpcs["Valdis"]->setFlip(false);
		mNpcs["Valdis"]->setscale(sf::Vector2f(0.4, 0.4));
		mNpcs["Valdis"]->setPosition(sf::Vector2f(600, 1120));
		mNpcs["Valdis"]->setDialogue("Valdis");
		mNpcs["Valdis"]->setIndex(5);

		Act1Events::triggerEvent(Act1Event::Beach_Intro);

		/* ==== Load Npcs and set right position, dialogue, scale and so on... ===== */
		mNpcs["Yngvarr"] = NpcPtr(new Npc(NpcHandler::getNpc("Yngvarr")));
		mNpcs["Dagny"] = NpcPtr(new Npc(NpcHandler::getNpc("Dagny")));
		mNpcs["Alfr"] = NpcPtr(new Npc(NpcHandler::getNpc("Alfr")));
		mNpcs["Leifr"] = NpcPtr(new Npc(NpcHandler::getNpc("Leifr")));
		mNpcs["Finnr"] = NpcPtr(new Npc(NpcHandler::getNpc("Finnr")));

		/* ==== Yngvarr ===== */
		RMI.loadResource(Textures::YngvarrSadIdle);
		RMI.loadResource(Textures::YngvarrSadTalk);
		mNpcs["Yngvarr"]->setIdleAnimation(Textures::YngvarrSadIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(7));
		mNpcs["Yngvarr"]->SetTalkAnimation(Textures::YngvarrSadTalk, sf::Vector2i(2, 1), sf::milliseconds(400), sf::Time::Zero);
		mNpcs["Yngvarr"]->setFlip(false);
		mNpcs["Yngvarr"]->setscale(sf::Vector2f(0.4, 0.4));
		mNpcs["Yngvarr"]->setPosition(sf::Vector2f(350, 760));
		mNpcs["Yngvarr"]->setInteractionPosition(sf::Vector2f(420, 760));
		mNpcs["Yngvarr"]->setDialogue("Yngvarr");
		mNpcs["Yngvarr"]->setIndex(5);

		/* ==== Yngvarr ===== */
		mNpcs["Dagny"]->setFlip(true);
		mNpcs["Dagny"]->setscale(sf::Vector2f(0.5, 0.5));
		mNpcs["Dagny"]->setPosition(sf::Vector2f(250, 760));
		mNpcs["Dagny"]->setInteractionPosition(sf::Vector2f(300, 760));
		mNpcs["Dagny"]->setDialogue("Dagny");
		mNpcs["Dagny"]->setIndex(5);

		/* ==== Alfr ===== */
		mNpcs["Alfr"]->setFlip(false);
		mNpcs["Alfr"]->setscale(sf::Vector2f(0.35, 0.35));
		mNpcs["Alfr"]->setPosition(sf::Vector2f(1250, 590));
		mNpcs["Alfr"]->setInteractionPosition(sf::Vector2f(1200, 590));
		mNpcs["Alfr"]->setDialogue("Alfr");
		mNpcs["Alfr"]->setIndex(5);

		/* ==== Leifr ===== */
		RMI.loadResource(Textures::LeifrIdle);
		RMI.loadResource(Textures::LeifrTalk);
		mNpcs["Leifr"]->setIdleAnimation(Textures::LeifrIdle, sf::Vector2i(2, 1), sf::milliseconds(300), sf::seconds(7.2));
		mNpcs["Leifr"]->SetTalkAnimation(Textures::LeifrTalk, sf::Vector2i(2, 1), sf::milliseconds(400), sf::Time::Zero);
		mNpcs["Leifr"]->setFlip(true);
		mNpcs["Leifr"]->setscale(sf::Vector2f(0.4, 0.4));
		mNpcs["Leifr"]->setPosition(sf::Vector2f(700, 580));
		mNpcs["Leifr"]->setInteractionPosition(sf::Vector2f(750, 580));
		mNpcs["Leifr"]->setDialogue("Leifr");
		mNpcs["Leifr"]->setIndex(5);

		/* ==== Finnr ===== */
		mNpcs["Finnr"]->setFlip(false);
		mNpcs["Finnr"]->setscale(sf::Vector2f(0.4, 0.4));
		mNpcs["Finnr"]->setPosition(sf::Vector2f(1600, 520));
		mNpcs["Finnr"]->setInteractionPosition(sf::Vector2f(1550, 520));
		mNpcs["Finnr"]->setDialogue("Finnr");
		mNpcs["Finnr"]->setIndex(3);

		//mPortals[Portal3] = &PortalLoader::getPortal(Portal3); // This does not create a new portal it only references the one in PortalLoader

		/* ================================================================ */

		Level::load();

		// Add collision from every NPC to the map
		mTileMap.addCollision(mNpcs["Leifr"]->getCollisionRect());
		mTileMap.addCollision(mNpcs["Finnr"]->getCollisionRect());
		mTileMap.addCollision(mNpcs["Dagny"]->getCollisionRect());
		mTileMap.addCollision(mNpcs["Alfr"]->getCollisionRect());
		mTileMap.addCollision(mNpcs["Yngvarr"]->getCollisionRect());

		// Add Index from every NPC to the map
		mTileMap.setIndexOnMap(mNpcs["Brandr"]->getIndexRect(), mNpcs["Brandr"]->getIndex() - 1);
		mTileMap.setIndexOnMap(mNpcs["Valdis"]->getIndexRect(), mNpcs["Valdis"]->getIndex() - 1);
		mTileMap.setIndexOnMap(mNpcs["Leifr"]->getIndexRect(), mNpcs["Leifr"]->getIndex() - 1);
		mTileMap.setIndexOnMap(mNpcs["Finnr"]->getIndexRect(), mNpcs["Finnr"]->getIndex() - 1);
		mTileMap.setIndexOnMap(mNpcs["Dagny"]->getIndexRect(), mNpcs["Dagny"]->getIndex() - 1);
		mTileMap.setIndexOnMap(mNpcs["Alfr"]->getIndexRect(), mNpcs["Alfr"]->getIndex() - 1);
		mTileMap.setIndexOnMap(mNpcs["Yngvarr"]->getIndexRect(), mNpcs["Yngvarr"]->getIndex() - 1);

	}
	RMI.loadResource(Textures::WaveAnimation);
	mWaveAnimation.load(RMI.getResource(Textures::WaveAnimation), sf::Vector2i(10, 9), sf::seconds(10), sf::seconds(5), true);
	mWaveAnimation.setIndex(4);
	mWaveAnimation.setProportions(sf::Vector2f(1170, 640));
	mWaveAnimation.getSprite().setOrigin(mWaveAnimation.getSprite().getTextureRect().width, mWaveAnimation.getSprite().getTextureRect().height);
	mWaveAnimation.setPadding(1);
	mWaveAnimation.setPosition(sf::Vector2f(1920 + 3, 1080 + 3));

	RMI.loadResource(Sound::BeachAmbient);
	AudioPlayer::playSound(Sound::BeachAmbient, "beachAmbient", true);
	AudioPlayer::playMusic("assets/sounds/music/exp theme.ogg", "Beach", true, 20);
}

void Level_Beach::unload()
{
	RMI.unloadResource(Sound::BeachAmbient);
	RMI.unloadResource(Textures::WaveAnimation);
	RMI.unloadResource(Textures::YngvarrSadIdle);
	RMI.unloadResource(Textures::YngvarrSadTalk);
	Level::unload();
}

void Level_Beach::changeLevel()
{
	if (mPortals[BeachToRoad]->getActivated())
	{
		if (mPortals[BeachToRoad]->getWorking())
			LVLMI.changeLevel(LevelFolder::Road);
	}
}
void Level_Beach::checkInteractEvents()
{

}
void Level_Beach::checkEvents()
{

}
void Level_Beach::introCutscene(sf::Time &frameTime)
{
	if (Act1Events::hasBeenTriggered(Act1Event::Beach_Intro) && !Act1Events::hasBeenHandled(Act1Event::Beach_Intro))
	{
		if (!mIntroFade1)
		{
			FadeI.fadeIn(frameTime);
			if (FadeI.getFaded())
			{
				//FadeI.setAlpha(0);
				DialogHandler::getDialogue("IntroBeach").startDialogue();
				mIntroFade1 = true;
			}
		}
		else if (DialogHandler::getDialogue("IntroBeach").getHasStopped() && !mIntroFade2)
		{
			FadeI.fadeOut(frameTime);
			if (FadeI.getFaded())
			{
				mCutSceneView.zoom(2);
				mCutSceneView.setCenter(1920 / 2, 1080 / 2);
				//mCutSceneView.setViewport(sf::FloatRect(0, 0, 1920, 1080));

				//FadeI.setAlpha(255);

				mNpcs["Brandr"]->setPosition(sf::Vector2f(2000, 0));
				mNpcs["Brynja"]->setPosition(sf::Vector2f(2000, 0));

				mNpcs["Valdis"]->setFlip(true);
				mNpcs["Valdis"]->setscale(sf::Vector2f(0.4, 0.4));
				mNpcs["Valdis"]->setPosition(sf::Vector2f(1600, 720));
				mNpcs["Valdis"]->setInteractionPosition(sf::Vector2f(1550, 720));
				mNpcs["Valdis"]->UpdateAnimationStyle();

				mTileMap.addCollision(mNpcs["Valdis"]->getCollisionRect());
				mTileMap.setIndexOnMap(mNpcs["Valdis"]->getIndexRect(), mNpcs["Valdis"]->getIndex() - 1);

				mIntroFade2 = true;
			}
		}
		else if (mIntroFade2 && !mIntroFade3)
		{
			FadeI.fadeIn(frameTime);
			if (FadeI.getFaded())
			{
				//FadeI.setAlpha(0);
				Act1Events::handleEvent(Act1Event::Beach_Intro);
				mIntroFade3 = true;
			}
		}
	}
}
void Level_Beach::endingCutscene(sf::Time &frameTime)
{
	if (Act1Events::hasBeenTriggered(Act1Event::Beach_Ending) && !Act1Events::hasBeenHandled(Act1Event::Beach_Ending))
	{
		if (!mEndingFade1)
		{
			FadeI.fadeOut(frameTime);
			if (FadeI.getFaded())
			{
				//FadeI.setAlpha(255);

				mNpcs["Brynja"]->setFlip(true);
				mNpcs["Brynja"]->setscale(sf::Vector2f(0.4, 0.4));
				mNpcs["Brynja"]->setPosition(sf::Vector2f(580, 760));
				mNpcs["Brynja"]->setIndex(4);
				mNpcs["Brynja"]->UpdateAnimationStyle();

				mNpcs["Brandr"]->setFlip(true);
				mNpcs["Brandr"]->setscale(sf::Vector2f(0.4, 0.4));
				mNpcs["Brandr"]->setPosition(sf::Vector2f(600, 800));
				mNpcs["Brandr"]->setIndex(5);
				mNpcs["Brandr"]->UpdateAnimationStyle();

				mNpcs["Valdis"]->setFlip(false);
				mNpcs["Valdis"]->setPosition(sf::Vector2f(700, 680));
				mNpcs["Valdis"]->setIndex(3);
				mNpcs["Valdis"]->UpdateAnimationStyle();

				mNpcs["Finnr"]->setFlip(false);
				mNpcs["Finnr"]->setPosition(sf::Vector2f(720, 720));
				mNpcs["Finnr"]->setIndex(4);
				mNpcs["Finnr"]->UpdateAnimationStyle();

				mNpcs["Leifr"]->setFlip(false);
				mNpcs["Leifr"]->setPosition(sf::Vector2f(740, 760));
				mNpcs["Leifr"]->setIndex(5);
				mNpcs["Leifr"]->UpdateAnimationStyle();

				mNpcs["Alfr"]->setFlip(false);
				mNpcs["Alfr"]->setPosition(sf::Vector2f(740, 840));
				mNpcs["Alfr"]->setIndex(7);
				mNpcs["Alfr"]->UpdateAnimationStyle();

				mNpcs["Yngvarr"]->setFlip(false);
				mNpcs["Yngvarr"]->setPosition(sf::Vector2f(720, 880));
				mNpcs["Yngvarr"]->setIndex(8);
				mNpcs["Yngvarr"]->UpdateAnimationStyle();

				mNpcs["Dagny"]->setFlip(false);
				mNpcs["Dagny"]->setPosition(sf::Vector2f(700, 920));
				mNpcs["Dagny"]->setIndex(9);
				mNpcs["Dagny"]->UpdateAnimationStyle();

				mTileMap.setIndexOnMap(mNpcs["Valdis"]->getIndexRect(), mNpcs["Valdis"]->getIndex() - 1);
				mTileMap.setIndexOnMap(mNpcs["Leifr"]->getIndexRect(), mNpcs["Leifr"]->getIndex() - 1);
				mTileMap.setIndexOnMap(mNpcs["Finnr"]->getIndexRect(), mNpcs["Finnr"]->getIndex() - 1);
				mTileMap.setIndexOnMap(mNpcs["Dagny"]->getIndexRect(), mNpcs["Dagny"]->getIndex() - 1);
				mTileMap.setIndexOnMap(mNpcs["Alfr"]->getIndexRect(), mNpcs["Alfr"]->getIndex() - 1);
				mTileMap.setIndexOnMap(mNpcs["Yngvarr"]->getIndexRect(), mNpcs["Yngvarr"]->getIndex() - 1);

				mPlayer.setPosition(sf::Vector2f(760, 800));
				mPlayer.setFlip(false);
				mPlayer.setAnimationStyle(AnimationType::Idle);

				mEndingFade1 = true;
			}
		}
		else if (mEndingFade1 && !mEndingFade2)
		{
			FadeI.fadeIn(frameTime);
			if (FadeI.getFaded())
			{
				DialogHandler::getDialogue("EndingBeach").startDialogue();

				mEndingFade2 = true;
			}
		}
		else if (DialogHandler::getDialogue("EndingBeach").getHasStopped() && !mEndingFade3)
		{
			FadeI.fadeOut(frameTime);
			if (FadeI.getFaded())
			{
				//FadeI.setAlpha(255);
				mNpcs.erase("Brandr");
				mNpcs.erase("Brynja");
				mNpcs.erase("Yngvarr");
				mNpcs.erase("Valdis");
				mNpcs.erase("Alfr");
				mNpcs.erase("Dagny");
				mNpcs.erase("Leifr");
				mNpcs.erase("Finnr");

				mEndingFade3 = true;
			}
		}
		else if (mEndingFade3 && !mEndingFade4)
		{
			FadeI.fadeIn(frameTime);
			if (FadeI.getFaded())
			{
				//FadeI.setAlpha(0);
				Act1Events::handleEvent(Act1Event::Beach_Ending);
				mEndingFade4 = true;
			}

		}
	}
}
void Level_Beach::talkToNpcs()
{
	if (!Act1Events::hasBeenTriggered(Act1Event::Beach_Ending))
	{
		/* ==== Check if talked to Dagny ===== */
		if (DialogHandler::getDialogue("Dagny").getActiveConversation())
			Act1Events::triggerEvent(Act1Event::Beach_Dagny);
		if (Act1Events::hasBeenTriggered(Act1Event::Beach_Dagny) && !Act1Events::hasBeenHandled(Act1Event::Beach_Dagny))
			if (DialogHandler::getDialogue("Dagny").getHasStopped())
				Act1Events::handleEvent(Act1Event::Beach_Dagny);

		/* ==== Check if talked to Leifr ===== */
		if (DialogHandler::getDialogue("Leifr").getActiveConversation())
			Act1Events::triggerEvent(Act1Event::Beach_Leifr);
		if (Act1Events::hasBeenTriggered(Act1Event::Beach_Leifr) && !Act1Events::hasBeenHandled(Act1Event::Beach_Leifr))
			if (DialogHandler::getDialogue("Leifr").getHasStopped())
				Act1Events::handleEvent(Act1Event::Beach_Leifr);

		/* ==== Check if talked to Yngvarr ===== */
		if (DialogHandler::getDialogue("Yngvarr").getActiveConversation())
			Act1Events::triggerEvent(Act1Event::Beach_Yngvarr);
		if (Act1Events::hasBeenTriggered(Act1Event::Beach_Yngvarr) && !Act1Events::hasBeenHandled(Act1Event::Beach_Yngvarr))
			if (DialogHandler::getDialogue("Yngvarr").getHasStopped())
				Act1Events::handleEvent(Act1Event::Beach_Yngvarr);

		/* ==== Check if talked to Alfr ===== */
		if (DialogHandler::getDialogue("Alfr").getActiveConversation())
			Act1Events::triggerEvent(Act1Event::Beach_Alfr);
		if (Act1Events::hasBeenTriggered(Act1Event::Beach_Alfr) && !Act1Events::hasBeenHandled(Act1Event::Beach_Alfr))
			if (DialogHandler::getDialogue("Yngvarr").getHasStopped())
				Act1Events::handleEvent(Act1Event::Beach_Alfr);

		/* ==== Check if talked to Valdis ===== */
		if (DialogHandler::getDialogue("Valdis").getActiveConversation())
			Act1Events::triggerEvent(Act1Event::Beach_Valdis);
		if (Act1Events::hasBeenTriggered(Act1Event::Beach_Valdis) && !Act1Events::hasBeenHandled(Act1Event::Beach_Valdis))
			if (DialogHandler::getDialogue("Valdis").getHasStopped())
				Act1Events::handleEvent(Act1Event::Beach_Valdis);

		/* ==== Check if talked to Finnr ===== */
		if (DialogHandler::getDialogue("Finnr").getActiveConversation())
			Act1Events::triggerEvent(Act1Event::Beach_Finnr);
		if (Act1Events::hasBeenTriggered(Act1Event::Beach_Finnr) && !Act1Events::hasBeenHandled(Act1Event::Beach_Finnr))
			if (DialogHandler::getDialogue("Finnr").getHasStopped())
				Act1Events::handleEvent(Act1Event::Beach_Finnr);

		/* ==== Check if talked to All ===== */
		if (Act1Events::hasBeenHandled(Act1Event::Beach_Finnr) && Act1Events::hasBeenHandled(Act1Event::Beach_Alfr) &&
			Act1Events::hasBeenHandled(Act1Event::Beach_Dagny) && Act1Events::hasBeenHandled(Act1Event::Beach_Leifr) &&
			Act1Events::hasBeenHandled(Act1Event::Beach_Yngvarr) && Act1Events::hasBeenHandled(Act1Event::Beach_Valdis))
		{
			Act1Events::triggerEvent(Act1Event::Beach_Ending);
		}
	}
}