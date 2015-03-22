#include "Level_Camp_Clearing.h"
#include "..\Logics\AudioPlayer.h"
#include <iostream>

Level_Camp_Clearing::Level_Camp_Clearing(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
	, mFade1(false)
	, mFade2(false)
{
	mBackgroundID = LevelFolder::Camp_Clearing;
}

void Level_Camp_Clearing::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Camp_Ambient, true, mAmbientSoundLevel);
	AudioPlayer::playHDDSound(HDDSound::Church_Music, true, mMusicSoundLevel);
}

void Level_Camp_Clearing::update(sf::Time &frametime)
{

	if (Act1Events::hasBeenTriggered(Act1Event::CampClearing_Leifr) && !Act1Events::hasBeenHandled(Act1Event::CampClearing_Leifr))
	{
		if (DialogHandler::getDialogue("LeifrBear_ClearingCamp").getHasStopped() && !mFade1)
		{
			FadeI.fadeOut(frametime);

			if (FadeI.getFaded())
			{
				mNpcs.erase("Leifr");
				mFade1 = true;
			}
		}
		else if (!mFade2 && mFade1)
		{
			FadeI.fadeIn(frametime);

			if (FadeI.getFaded())
			{
				Act1Events::handleEvent(Act1Event::CampClearing_Leifr);
				mFade2 = true;
			}
		}
	}

	if (Act1Events::hasBeenTriggered(Act1Event::LightCampFire) && !Act1Events::hasBeenHandled(Act1Event::LightCampFire))
	{
		if (mPlayer->hasItemInInventory("torch"))
			mPlayer->removeItemFromInventory("torch");
		FadeI.fadeOut(frametime);
		if (FadeI.getFaded())
		{
			LVLMI.changeLevel(LevelFolder::Camp_Finished);
			AudioPlayer::stopHDDSound(HDDSound::Camp_Ambient);
			AudioPlayer::stopHDDSound(HDDSound::Church_Music);
			mRestartSounds = true;
			Act1Events::handleEvent(Act1Event::LightCampFire);
		}
	}

	if (Act1Events::hasBeenTriggered(Act1Event::ForestCamp_NeedFireQuest) && mPlayer->hasItemInInventory("bearDeer") && !mSetLeifrDialogue)
	{
		mNpcs["Leifr"]->setDialogue("LeifrBear_ClearingCamp");
		mSetLeifrDialogue = true;
	}
	
	if (Act1Events::hasBeenTriggered(Act1Event::LightCampFire))
		mCampFire.animate(frametime);

	Level::update(frametime);
	changeLevel();
}

void Level_Camp_Clearing::render(IndexRenderer &iRenderer)
{
	if (Act1Events::hasBeenTriggered(Act1Event::LightCampFire))
		mCampFire.render(iRenderer);
	Level::render(iRenderer);
}

void Level_Camp_Clearing::load()
{
	if (mPlayer->hasItemInInventory("torch"))
	{
		RMI.loadResource(Texture::FireCampAnimation);

		mCampFire.load(RMI.getResource(Texture::FireCampAnimation), sf::Vector2i(3, 1), sf::milliseconds(300), sf::Time::Zero, true);
		mCampFire.setIndex(5);
		mCampFire.setProportions(sf::Vector2f(99, 115));
		mCampFire.setScaleFromHeight(115);
		mCampFire.setPosition(sf::Vector2f(900, 720));
	}

	mPortals[CampToRoad] = &PortalLoader::getPortal(CampToRoad);
	mPortals[CampToForestRoad] = &PortalLoader::getPortal(CampToForestRoad);
	//if (Act1Events::hasBeenHandled(Act1Event::ForestCamp_BeerDeer))
		mPortals[CampClearingToCamPFinished] = &PortalLoader::getPortal(CampClearingToCamPFinished);

	RMI.loadResource(Footsteps::Dirt);
	mNpcs["Leifr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Leifr")));
	mNpcs["Brynja"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Brynja")));
	mNpcs["Valdis"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Valdis")));

	/*------------------- Leifr ----------------*/
	mNpcs["Leifr"]->setScale(sf::Vector2f(0.28, 0.28));
	mNpcs["Leifr"]->setIndex(10);
	mNpcs["Leifr"]->setPosition(sf::Vector2f(1035, 729));
	mNpcs["Leifr"]->setInteractionPosition(sf::Vector2f(1160, 724));
	if (!Act1Events::hasBeenTriggered(Act1Event::ForestCamp_NeedFireQuest) && !Act1Events::hasBeenHandled(Act1Event::ForestCamp_BeerDeer))
		mNpcs["Leifr"]->setDialogue("Leifr_ClearingCamp");
	else if (Act1Events::hasBeenTriggered(Act1Event::ForestCamp_NeedFireQuest) && !mPlayer->hasItemInInventory("bearDeer") && !Act1Events::hasBeenHandled(Act1Event::ForestCamp_BeerDeer))
		mNpcs["Leifr"]->setDialogue("LeifrFire_ClearingCamp");
	else if (Act1Events::hasBeenTriggered(Act1Event::ForestCamp_NeedFireQuest) && mPlayer->hasItemInInventory("bearDeer") && !Act1Events::hasBeenHandled(Act1Event::ForestCamp_BeerDeer))
	{
		mNpcs["Leifr"]->setDialogue("LeifrBear_ClearingCamp");
		mSetLeifrDialogue = true;
	}
	else if (Act1Events::hasBeenHandled(Act1Event::ForestCamp_BeerDeer) && !Act1Events::hasBeenHandled(Act1Event::CampFinished_Conversation))
		mNpcs["Leifr"]->setDialogue("LeifrAFterDruids_ClearingCamp");

	/*------------------- Brynja ----------------*/
	mNpcs["Brynja"]->setScale(sf::Vector2f(0.45, 0.45));
	mNpcs["Brynja"]->setIndex(10);
	mNpcs["Brynja"]->setPosition(sf::Vector2f(1500, 850));
	mNpcs["Brynja"]->setInteractionPosition(sf::Vector2f(1385, 825));
	mNpcs["Brynja"]->setDialogue("Brynja_ClearingCamp");

	/*------------------- Valdis ----------------*/
	mNpcs["Valdis"]->setScale(sf::Vector2f(0.45, 0.45));
	mNpcs["Valdis"]->setIndex(10);
	mNpcs["Valdis"]->setPosition(sf::Vector2f(645, 860));
	mNpcs["Valdis"]->setInteractionPosition(sf::Vector2f(750, 860));
	mNpcs["Valdis"]->setFlip(true);
	mNpcs["Valdis"]->setDialogue("Valdis_ClearingCamp");

	if (Act1Events::hasBeenHandled(Act1Event::TavernInside_GiveAxeToBrandr))
	{
		mNpcs["Brandr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Brandr")));
		mNpcs["Brandr"]->setScale(sf::Vector2f(0.4, 0.4));
		mNpcs["Brandr"]->setPosition(sf::Vector2f(1370, 850));
		mNpcs["Brynja"]->setInteractionPosition(sf::Vector2f(1605, 850));
		mNpcs["Brandr"]->setInteractionPosition(sf::Vector2f(1605, 850));
		mNpcs["Brandr"]->setDialogue("BrandrBrynja_ClearingCamp");
		mNpcs["Brynja"]->setDialogue("BrandrBrynja_ClearingCamp");

	}

	if (!Act1Events::hasBeenHandled(Act1Event::CampClearing_Brynja))
		mPortals[CampToRoad]->setCannotDialogue("I should speak to the others first. They might need help with something, and I don't want to come off as an asshole.");
	else if (Act1Events::hasBeenHandled(Act1Event::CampClearing_Brynja))
		mPortals[CampToRoad]->setWorking(true);
	if (!Act1Events::hasBeenHandled(Act1Event::CampClearing_Valdis))
		mPortals[CampToForestRoad]->setCannotDialogue("I should speak to the others first. They might need help with something, and I don't want to come off as an asshole.");
	else if (Act1Events::hasBeenHandled(Act1Event::CampClearing_Valdis))
		mPortals[CampToForestRoad]->setWorking(true);

	Level::load();

	// Add collision from every NPC to the map
	mTileMap.addCollision(mNpcs["Leifr"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Brynja"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Valdis"]->getCollisionRect());

	// Add Index from every NPC to the map
	mTileMap.setIndexOnMap(mNpcs["Leifr"]->getIndexRect(), mNpcs["Leifr"]->getIndex() - 2);
	mTileMap.setIndexOnMap(mNpcs["Brynja"]->getIndexRect(), mNpcs["Brynja"]->getIndex() - 2);
	mTileMap.setIndexOnMap(mNpcs["Valdis"]->getIndexRect(), mNpcs["Valdis"]->getIndex() - 2);

	mCurrentFootsteps = Footsteps::Dirt;


	/* Debug */
	//mPortals[CampToForestRoad]->setWorking(true);
	//mPortals[CampToRoad]->setWorking(true);
	/* ===== */
}

void Level_Camp_Clearing::unload()
{
	RMI.unloadResource(Footsteps::Dirt);
	Level::unload();
}

void Level_Camp_Clearing::changeLevel()
{
	if (mPortals[CampToRoad]->getActivated() && mPortals[CampToRoad]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Road);
		AudioPlayer::stopHDDSound(HDDSound::Camp_Ambient);
		AudioPlayer::stopHDDSound(HDDSound::Church_Music);
		mRestartSounds = true;
	}
	else if (mPortals[CampToForestRoad]->getActivated() && mPortals[CampToForestRoad]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Forest_Road);
		AudioPlayer::stopHDDSound(HDDSound::Camp_Ambient);
		AudioPlayer::stopHDDSound(HDDSound::Church_Music);
		mRestartSounds = true;
	}
}

void Level_Camp_Clearing::checkInteractEvents()
{
	if (mDroppedItemID == "torch" && mObjects[mObjIndex]->getObjID() == "firePlaceCamp1" && !Act1Events::hasBeenTriggered(Act1Event::LightCampFire))
	{
		Act1Events::triggerEvent(Act1Event::LightCampFire);
	}
	if (mDroppedItemID == "stickCloth" && mObjects[mObjIndex]->getObjID() == "oilBarrel")
	{
		mPlayer->removeItemFromInventory("stickCloth");
		mPlayer->addItemToInventory("stickWetCloth");
	}
}
void Level_Camp_Clearing::checkEvents()
{
	if (DialogHandler::getDialogue("Brynja_ClearingCamp").getActiveConversation())
		Act1Events::triggerEvent(Act1Event::CampClearing_Brynja);
	if (Act1Events::hasBeenTriggered(Act1Event::CampClearing_Brynja) && !Act1Events::hasBeenHandled(Act1Event::CampClearing_Brynja))
		if (DialogHandler::getDialogue("Brynja_ClearingCamp").getHasStopped())
		{
			Act1Events::handleEvent(Act1Event::CampClearing_Brynja);
			mPortals[CampToRoad]->setWorking(true);
		}

	if (DialogHandler::getDialogue("Valdis_ClearingCamp").getActiveConversation())
		Act1Events::triggerEvent(Act1Event::CampClearing_Valdis);
	if (Act1Events::hasBeenTriggered(Act1Event::CampClearing_Valdis) && !Act1Events::hasBeenHandled(Act1Event::CampClearing_Valdis))
		if (DialogHandler::getDialogue("Valdis_ClearingCamp").getHasStopped())
		{
			mPortals[CampToForestRoad]->setWorking(true);
			Act1Events::handleEvent(Act1Event::CampClearing_Valdis);
		}

	if (Act1Events::hasBeenHandled(Act1Event::CampClearing_Leifr) && Act1Events::hasBeenHandled(Act1Event::CampClearing_Valdis) &&
		Act1Events::hasBeenHandled(Act1Event::CampClearing_Brynja) && !Act1Events::hasBeenTriggered(Act1Event::CampClearing_TalkedToAll))
	{
		Act1Events::triggerEvent(Act1Event::CampClearing_TalkedToAll);
	}

	if (!Act1Events::hasBeenTriggered(Act1Event::GotBeerDeerPelt) && mPlayer->hasItemInInventory("bearDeer"))
		Act1Events::triggerEvent(Act1Event::GotBeerDeerPelt);

	if (!Act1Events::hasBeenTriggered(Act1Event::CampClearing_Leifr) && Act1Events::hasBeenTriggered(Act1Event::GotBeerDeerPelt))
		Act1Events::triggerEvent(Act1Event::CampClearing_Leifr);

}
