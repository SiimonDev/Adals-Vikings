#include "Level_Beach.h"
#include "..\Logics\ResourceManager.h"
#include "..\Logics\AudioPlayer.h"
#include "..\Interface\LoadingScreen.h"
#include "..\Logics\KeyboardState.h"
#include "..\Logics\WindowState.h"
#include <iostream>

static Animation mWaveAnimation;

Level_Beach::Level_Beach(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
	, mIntroFade1(false)
{
	mBackgroundID = LevelFolder::Beach;
}

void Level_Beach::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Beach_Ambient, true, 20);
	AudioPlayer::playHDDSound(HDDSound::Beach_Road_Tavern_Outside_Music, true, 20);
}

void Level_Beach::update(sf::Time &frametime)
{
	introCutscene(frametime);
	talkToNpcs();
	endingCutscene(frametime);

	mWaveAnimation.animate(frametime);
	if (mWaveAnimation.getCurrentFrame() == 1)
		AudioPlayer::playHDDSound(HDDSound::Beach_Wave, false, 20);

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
	mRestartSounds = true;
	mPortals[BeachToRoad] = &PortalLoader::getPortal(BeachToRoad);
	mPortals[BeachToTavernOutside] = &PortalLoader::getPortal(BeachToTavernOutside);
	mPortals[BeachToBeachHill] = &PortalLoader::getPortal(BeachToBeachHill);

	if (Act1Events::hasBeenHandled(Act1Event::CampClearing_Brynja))
		mPortals[BeachToTavernOutside]->setWorking(true);

	mNpcs["Seagull"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Seagull")));

	RMI.loadResource(Texture::WaveAnimationBeach);
	mWaveAnimation.load(RMI.getResource(Texture::WaveAnimationBeach), sf::Vector2i(10, 9), sf::seconds(10), sf::seconds(7), true);
	mWaveAnimation.setIndex(4);
	mWaveAnimation.setProportions(sf::Vector2f(1170, 640));
	mWaveAnimation.getSprite().setOrigin(mWaveAnimation.getSprite().getTextureRect().width, mWaveAnimation.getSprite().getTextureRect().height);
	mWaveAnimation.setPadding(1);
	mWaveAnimation.setPosition(sf::Vector2f(1920 + 3, 1080 + 3));


	if (!Act1Events::hasBeenHandled(Act1Event::Beach_Ending))
	{
		mPortals[BeachToRoad]->setCannotDialogue("I was told not to leave the beach!");
		mPortals[BeachToTavernOutside]->setCannotDialogue("I was told not to leave the beach!");
		mPortals[BeachToBeachHill]->setCannotDialogue("I was told not to leave the beach!");

		mCutSceneView.setCenter(1920 / 2 - 450, 1080 / 2 + 270);
		mCutSceneView.setSize(1920, 1080);
		mCutSceneView.zoom(0.5);

		/* ===== Load necessary resources ===== */
		RMI.loadResource(Texture::LeifrIdle);
		RMI.loadResource(Texture::LeifrTalk);

		/* ==== Load Npcs and set right position, dialogue, scale and so on... ===== */
		mNpcs["Yngvarr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Yngvarr")));
		mNpcs["Dagny"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Dagny")));
		mNpcs["Alfr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Alfr")));
		mNpcs["Leifr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Leifr")));
		mNpcs["Finnr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Finnr")));
		mNpcs["Brandr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Brandr")));
		mNpcs["Brynja"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Brynja")));
		mNpcs["Valdis"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Valdis")));

		mPlayer->setPosition(sf::Vector2f(410, 1070));
		mPlayer->setFlip(true);
		mPlayer->UpdateAnimationStyle();

		mNpcs["Brandr"]->setFlip(true);
		mNpcs["Brandr"]->setScale(sf::Vector2f(0.4, 0.4));
		mNpcs["Brandr"]->setPosition(sf::Vector2f(400, 1120));
		mNpcs["Brandr"]->setDialogue("Intro_Beach");
		mNpcs["Brandr"]->setIndex(14);

		mNpcs["Brynja"]->setFlip(false);
		mNpcs["Brynja"]->setScale(sf::Vector2f(0.4, 0.4));
		mNpcs["Brynja"]->setPosition(sf::Vector2f(600, 1070));
		mNpcs["Brynja"]->setDialogue("Intro_Beach");
		mNpcs["Brynja"]->setIndex(14);

		mNpcs["Valdis"]->setFlip(false);
		mNpcs["Valdis"]->setScale(sf::Vector2f(0.45f, 0.45f));
		mNpcs["Valdis"]->setPosition(sf::Vector2f(600, 1120));
		mNpcs["Valdis"]->setDialogue("Valdis_Beach");
		mNpcs["Valdis"]->setIndex(14);

		/* ==== Yngvarr ===== */
		RMI.loadResource(Texture::YngvarrSadIdle);
		RMI.loadResource(Texture::YngvarrSadTalk);
		mNpcs["Yngvarr"]->setIdleAnimation(Texture::YngvarrSadIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(7));
		mNpcs["Yngvarr"]->SetTalkAnimation(Texture::YngvarrSadTalk, sf::Vector2i(2, 1), sf::milliseconds(400), sf::Time::Zero);
		mNpcs["Yngvarr"]->setFlip(false);
		mNpcs["Yngvarr"]->setScale(sf::Vector2f(0.4, 0.4));
		mNpcs["Yngvarr"]->setPosition(sf::Vector2f(350, 760));
		mNpcs["Yngvarr"]->setInteractionPosition(sf::Vector2f(420, 760));
		mNpcs["Yngvarr"]->setDialogue("Yngvarr_Beach");
		mNpcs["Yngvarr"]->setIndex(14);

		/* ==== Dagny ===== */
		mNpcs["Dagny"]->setFlip(true);
		mNpcs["Dagny"]->setScale(sf::Vector2f(0.5, 0.5));
		mNpcs["Dagny"]->setPosition(sf::Vector2f(250, 760));
		mNpcs["Dagny"]->setInteractionPosition(sf::Vector2f(300, 760));
		mNpcs["Dagny"]->setDialogue("Dagny_Beach");
		mNpcs["Dagny"]->setIndex(14);

		/* ==== Alfr ===== */
		mNpcs["Alfr"]->setFlip(false);
		mNpcs["Alfr"]->setScale(sf::Vector2f(0.35, 0.35));
		mNpcs["Alfr"]->setPosition(sf::Vector2f(1250, 580));
		mNpcs["Alfr"]->setInteractionPosition(sf::Vector2f(1200, 590));
		mNpcs["Alfr"]->setDialogue("Alfr_Beach");
		mNpcs["Alfr"]->setIndex(14);

		/* ==== Leifr ===== */
		mNpcs["Leifr"]->setFlip(true);
		mNpcs["Leifr"]->setScale(sf::Vector2f(0.3f, 0.3f));
		mNpcs["Leifr"]->setPosition(sf::Vector2f(700, 540));
		mNpcs["Leifr"]->setInteractionPosition(sf::Vector2f(750, 580));
		mNpcs["Leifr"]->setDialogue("Leifr_Beach");
		mNpcs["Leifr"]->setIndex(14);

		/* ==== Finnr ===== */
		mNpcs["Finnr"]->setFlip(false);
		mNpcs["Finnr"]->setScale(sf::Vector2f(0.4, 0.4));
		mNpcs["Finnr"]->setPosition(sf::Vector2f(1600, 520));
		mNpcs["Finnr"]->setInteractionPosition(sf::Vector2f(1550, 520));
		mNpcs["Finnr"]->setDialogue("Finnr_Beach");
		mNpcs["Finnr"]->setIndex(12);
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
		//mTileMap.setIndexOnMap(mNpcs["Leifr"]->getIndexRect(), mNpcs["Leifr"]->getIndex() - 1);
		mTileMap.setIndexOnMap(mNpcs["Finnr"]->getIndexRect(), mNpcs["Finnr"]->getIndex() - 1);
		mTileMap.setIndexOnMap(mNpcs["Dagny"]->getIndexRect(), mNpcs["Dagny"]->getIndex() - 1);
		mTileMap.setIndexOnMap(mNpcs["Alfr"]->getIndexRect(), mNpcs["Alfr"]->getIndex() - 1);
		mTileMap.setIndexOnMap(mNpcs["Yngvarr"]->getIndexRect(), mNpcs["Yngvarr"]->getIndex() - 1);
	}
	else
		Level::load();

		if (!Act1Events::hasBeenTriggered(Act1Event::Beach_Intro))
			Act1Events::triggerEvent(Act1Event::Beach_Intro);
}

void Level_Beach::unload()
{
	RMI.unloadResource(Texture::WaveAnimationBeach);
	RMI.unloadResource(Texture::YngvarrSadIdle);
	RMI.unloadResource(Texture::YngvarrSadTalk);

	Level::unload();
}

void Level_Beach::changeLevel()
{
	if (mPortals[BeachToRoad]->getActivated() && mPortals[BeachToRoad]->getWorking())
	{
		Act1Events::triggerEvent(Act1Event::Enter_Road);
		LVLMI.changeLevel(LevelFolder::Road);
		AudioPlayer::stopHDDSound(HDDSound::Beach_Ambient);
		AudioPlayer::stopHDDSound(HDDSound::Beach_Wave);
		mRestartSounds = true;
	}
	else if (mPortals[BeachToTavernOutside]->getActivated() && mPortals[BeachToTavernOutside]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Tavern_Outside);
		AudioPlayer::stopHDDSound(HDDSound::Beach_Ambient);
		AudioPlayer::stopHDDSound(HDDSound::Beach_Wave);
		mRestartSounds = true;
	}
	else if (mPortals[BeachToBeachHill]->getActivated() && mPortals[BeachToBeachHill]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Beach_Hills);
		AudioPlayer::stopHDDSound(HDDSound::Beach_Ambient);
		AudioPlayer::stopHDDSound(HDDSound::Beach_Wave);
		mRestartSounds = true;
	}
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
				DialogHandler::getDialogue("Intro_Beach").startDialogue();
				mIntroFade1 = true;
			}
		}
		else if (DialogHandler::getDialogue("Intro_Beach").getHasStopped() && !mIntroFade2)
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
				mNpcs["Valdis"]->setScale(sf::Vector2f(0.4, 0.4));
				mNpcs["Valdis"]->setPosition(sf::Vector2f(1600, 720));
				mNpcs["Valdis"]->setInteractionPosition(sf::Vector2f(1550, 720));
				mNpcs["Valdis"]->updateAnimationStyle();

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
				mNpcs["Brynja"]->setScale(sf::Vector2f(0.4, 0.4));
				mNpcs["Brynja"]->setPosition(sf::Vector2f(580, 760));
				mNpcs["Brynja"]->setIndex(14);
				mNpcs["Brynja"]->updateAnimationStyle();

				mNpcs["Brandr"]->setFlip(true);
				mNpcs["Brandr"]->setScale(sf::Vector2f(0.4, 0.4));
				mNpcs["Brandr"]->setPosition(sf::Vector2f(600, 800));
				mNpcs["Brandr"]->setIndex(15);
				mNpcs["Brandr"]->updateAnimationStyle();

				mNpcs["Valdis"]->setFlip(false);
				mNpcs["Valdis"]->setPosition(sf::Vector2f(700, 680));
				mNpcs["Valdis"]->setIndex(13);
				mNpcs["Valdis"]->updateAnimationStyle();

				mNpcs["Finnr"]->setFlip(false);
				mNpcs["Finnr"]->setPosition(sf::Vector2f(720, 720));
				mNpcs["Finnr"]->setIndex(14);
				mNpcs["Finnr"]->updateAnimationStyle();

				mNpcs["Leifr"]->setFlip(false);
				mNpcs["Leifr"]->setPosition(sf::Vector2f(740, 760));
				mNpcs["Leifr"]->setIndex(15);
				mNpcs["Leifr"]->updateAnimationStyle();

				mNpcs["Alfr"]->setFlip(false);
				mNpcs["Alfr"]->setPosition(sf::Vector2f(740, 840));
				mNpcs["Alfr"]->setIndex(17);
				mNpcs["Alfr"]->updateAnimationStyle();

				mNpcs["Yngvarr"]->setFlip(false);
				mNpcs["Yngvarr"]->setPosition(sf::Vector2f(720, 880));
				mNpcs["Yngvarr"]->setIndex(18);
				mNpcs["Yngvarr"]->updateAnimationStyle();

				mNpcs["Dagny"]->setFlip(false);
				mNpcs["Dagny"]->setPosition(sf::Vector2f(700, 920));
				mNpcs["Dagny"]->setIndex(19);
				mNpcs["Dagny"]->updateAnimationStyle();

				mPlayer->setPosition(sf::Vector2f(760, 800));
				mPlayer->setFlip(false);
				mPlayer->setAnimationStyle(AnimationType::Idle);

				mEndingFade1 = true;
			}
		}
		else if (mEndingFade1 && !mEndingFade2)
		{
			FadeI.fadeIn(frameTime);
			if (FadeI.getFaded())
			{
				DialogHandler::getDialogue("Ending_Beach").startDialogue();

				mEndingFade2 = true;
			}
		}
		else if (DialogHandler::getDialogue("Ending_Beach").getHasStopped() && !mEndingFade3)
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
				mPortals[BeachToTavernOutside]->setCannotDialogue("Brandr and the others went that way... I should go the other.");
				mPortals[BeachToRoad]->setWorking(true);
				mPortals[BeachToBeachHill]->setWorking(true);
				Act1Events::handleEvent(Act1Event::Beach_Ending);
				mEndingFade4 = true;
			}

		}
	}
}

void Level_Beach::talkToNpcs()
{
	/* Debug stuff */
	//Act1Events::handleEvent(Act1Event::Beach_Ending);
	//Act1Events::handleEvent(Act1Event::Beach_Intro);

	//Act1Events::handleEvent(Act1Event::Beach_Dagny);
	//Act1Events::handleEvent(Act1Event::Beach_Leifr);
	//Act1Events::handleEvent(Act1Event::Beach_Yngvarr);
	//Act1Events::handleEvent(Act1Event::Beach_Alfr);
	//Act1Events::handleEvent(Act1Event::Beach_Valdis);
	//Act1Events::handleEvent(Act1Event::Beach_Finnr);

	//mPortals[BeachToRoad]->setWorking(true);
	//mPortals[BeachToTavernOutside]->setWorking(true);
	/*=============*/

	if (!Act1Events::hasBeenTriggered(Act1Event::Beach_Ending))
	{
		/* ==== Check if talked to Dagny ===== */
		if (DialogHandler::getDialogue("Dagny_Beach").getActiveConversation())
			Act1Events::triggerEvent(Act1Event::Beach_Dagny);
		if (Act1Events::hasBeenTriggered(Act1Event::Beach_Dagny) && !Act1Events::hasBeenHandled(Act1Event::Beach_Dagny))
			if (DialogHandler::getDialogue("Dagny_Beach").getHasStopped())
				Act1Events::handleEvent(Act1Event::Beach_Dagny);

		/* ==== Check if talked to Leifr ===== */
		if (DialogHandler::getDialogue("Leifr_Beach").getActiveConversation())
			Act1Events::triggerEvent(Act1Event::Beach_Leifr);
		if (Act1Events::hasBeenTriggered(Act1Event::Beach_Leifr) && !Act1Events::hasBeenHandled(Act1Event::Beach_Leifr))
			if (DialogHandler::getDialogue("Leifr_Beach").getHasStopped())
				Act1Events::handleEvent(Act1Event::Beach_Leifr);

		/* ==== Check if talked to Yngvarr ===== */
		if (DialogHandler::getDialogue("Yngvarr_Beach").getActiveConversation())
			Act1Events::triggerEvent(Act1Event::Beach_Yngvarr);
		if (Act1Events::hasBeenTriggered(Act1Event::Beach_Yngvarr) && !Act1Events::hasBeenHandled(Act1Event::Beach_Yngvarr))
			if (DialogHandler::getDialogue("Yngvarr_Beach").getHasStopped())
				Act1Events::handleEvent(Act1Event::Beach_Yngvarr);

		/* ==== Check if talked to Alfr ===== */
		if (DialogHandler::getDialogue("Alfr_Beach").getActiveConversation())
			Act1Events::triggerEvent(Act1Event::Beach_Alfr);
		if (Act1Events::hasBeenTriggered(Act1Event::Beach_Alfr) && !Act1Events::hasBeenHandled(Act1Event::Beach_Alfr))
			if (DialogHandler::getDialogue("Yngvarr_Beach").getHasStopped())
				Act1Events::handleEvent(Act1Event::Beach_Alfr);

		/* ==== Check if talked to Valdis ===== */
		if (DialogHandler::getDialogue("Valdis_Beach").getActiveConversation())
			Act1Events::triggerEvent(Act1Event::Beach_Valdis);
		if (Act1Events::hasBeenTriggered(Act1Event::Beach_Valdis) && !Act1Events::hasBeenHandled(Act1Event::Beach_Valdis))
			if (DialogHandler::getDialogue("Valdis_Beach").getHasStopped())
				Act1Events::handleEvent(Act1Event::Beach_Valdis);

		/* ==== Check if talked to Finnr ===== */
		if (DialogHandler::getDialogue("Finnr_Beach").getActiveConversation())
			Act1Events::triggerEvent(Act1Event::Beach_Finnr);
		if (Act1Events::hasBeenTriggered(Act1Event::Beach_Finnr) && !Act1Events::hasBeenHandled(Act1Event::Beach_Finnr))
			if (DialogHandler::getDialogue("Finnr_Beach").getHasStopped())
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