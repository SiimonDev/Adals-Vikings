#include "Level_Forest_Camp.h"
#include "..\Logics\AudioPlayer.h"
#include <iostream>

Level_Forest_Camp::Level_Forest_Camp(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Forest_Camp;
}

void Level_Forest_Camp::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Forest_Camp_Ambient, true, mAmbientSoundLevel);
	AudioPlayer::playHDDSound(HDDSound::Forest_Music, true, mMusicSoundLevel);
}

void Level_Forest_Camp::update(sf::Time &frametime)
{
	mFireAnimation.animate(frametime);

	if (Act1Events::hasBeenTriggered(Act1Event::ForestCamp_BeerDeer) && !Act1Events::hasBeenHandled(Act1Event::ForestCamp_BeerDeer))
	{
		if (mPlayer->hasItemInInventory("bearDeer"))
			mPlayer->removeItemFromInventory("bearDeer");

		if (!mFade1)
		{
			mUIUpdate = false;

			FadeI.fadeOut(frametime);
			if (FadeI.getFaded())
			{
				mPlayer->setBearCostume(true);
				mPlayer->UpdateAnimationStyle();
				mNpcs.erase("Leifr");
				mNpcs["HiddenLeifr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("HiddenLeifr")));
				mNpcs["HiddenLeifr"]->setPosition(sf::Vector2f(1570, 408));
				mFade1 = true;
			}
		}
		if (!mFade2 && mFade1)
		{
			FadeI.fadeIn(frametime);
			if (FadeI.getFaded())
			{
				DialogHandler::startDialogue("Leifr_BeforeDruids");
				mFade2 = true;
			}
		}
		if (DialogHandler::getDialogue("Leifr_BeforeDruids").getHasStopped() && !mDestinationReached && mFade2)
		{
			if (!mSuperPath)
			{
				Path path = PathFinder::getPath(mPlayer->getPosition(), sf::Vector2f(800, 900));
				mPlayer->walkPath(path);
				mSuperPath = true;
			}
			if (mPlayer->isDestinationReached())
			{
				mNpcs["HiddenLeifr"]->setPosition(sf::Vector2f(800, 600));
				mDestinationReached = true;
			}
		}

		if (mDestinationReached && !DialogHandler::getDialogue("Druids2_ForestCamp").getActiveConversation() && !DialogHandler::getDialogue("Druids2_ForestCamp").getHasStopped())
			DialogHandler::startDialogue("Druids2_ForestCamp");

		if (DialogHandler::getDialogue("Druids2_ForestCamp").getHasStopped())
		{
			if (!mFade3)
			{
				FadeI.fadeOut(frametime);
				if (FadeI.getFaded())
				{
					RMI.unloadResource(Texture::DruidsForest1);
					mNpcs.erase("DruidLeader");
					mNpcs.erase("Druid2");
					mNpcs.erase("Dennis");
					mNpcs.erase("Druid3");
					mNpcs.erase("Druid4");
					mNpcs.erase("Hipster Druid");
					mNpcs.erase("Druids");
					mFade3 = true;
				}
			}
			if (!mFade4 && mFade3)
			{
				FadeI.fadeIn(frametime);
				if (FadeI.getFaded())
				{
					mFade4 = true;
					DialogHandler::startDialogue("Leifr_AfterDruids");
				}
			}
			if (DialogHandler::getDialogue("Leifr_AfterDruids").getHasStopped())
			{
				if (!mFade5)
				{
					FadeI.fadeOut(frametime);

					if (FadeI.getFaded())
					{
						mNpcs.erase("HiddenLeifr");
						mPlayer->setBearCostume(false);
						mPlayer->UpdateAnimationStyle();
						mFade5 = true;
					}
				}

				if (mFade5 && !mFade6)
				{
					FadeI.fadeIn(frametime);

					if (FadeI.getFaded())
					{
						mFade6 = true;
						mUIUpdate = true;
						Act1Events::handleEvent(Act1Event::ForestCamp_BeerDeer);
					}
				}
			}
		}
	}
	
	/*if (Act1Events::hasBeenTriggered(Act1Event::ForestCampFire) && !Act1Events::hasBeenHandled(Act1Event::ForestCampFire))
	{
		if (!Act1Events::hasBeenHandled(Act1Event::ForestCamp_BeerDeer))
		{
			DialogHandler::getDialogue("FireDeny_ForestCamp").startDialogue();

		}
		else if (Act1Events::hasBeenHandled(Act1Event::ForestCamp_BeerDeer))
		{
			mPlayer->removeItemFromInventory("stickWetCloth");
			mPlayer->addItemToInventory("torch");
			Act1Events::handleEvent(Act1Event::ForestCampFire);
		}
	}*/

	Level::update(frametime);
	changeLevel();
}

void Level_Forest_Camp::render(IndexRenderer &iRenderer)
{ 
	mFireAnimation.render(iRenderer);
	if (!mFade3)
		iRenderer.addSprite(mDruids, 50);
	Level::render(iRenderer);
}

void Level_Forest_Camp::load()
{
	RMI.loadResource(Footsteps::Dirt);
	mPortals[ForestCampToForestRoad] = &PortalLoader::getPortal(ForestCampToForestRoad);
	mPortals[ForestCampToForestRoad]->setWorking(true);

	if (!Act1Events::hasBeenHandled(Act1Event::ForestCamp_BeerDeer))
	{
		RMI.loadResource(Texture::DruidsForest1);
		RMI.loadResource(Texture::BearWalk);
		RMI.loadResource(Texture::BearIdle);

		mNpcs["DruidLeader"] = NpcPtr(new Npc(NpcHandlerI.getNpc("DruidLeader")));
		mNpcs["Druids"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Druids")));
		mNpcs["Hipster druid"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Hipster druid")));
		mNpcs["Dennis"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Dennis")));
		mNpcs["Druid2"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Druid2")));
		mNpcs["Druid3"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Druid3")));
		mNpcs["Druid4"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Druid4")));

		mNpcs["DruidLeader"]->setDialogue("Druids_ForestCamp1");
		mNpcs["Druids"]->setDialogue("Druids_ForestCamp1");

		mNpcs["Druid2"]->setDialogue("Druids_ForestCamp1");
		mNpcs["Druid3"]->setDialogue("Druids_ForestCamp1");
		mNpcs["Druid4"]->setDialogue("Druids_ForestCamp1");
		mNpcs["Hipster druid"]->setDialogue("Druids_ForestCamp1");
		mNpcs["Dennis"]->setDialogue("Druids_ForestCamp1");

		if (Act1Events::hasBeenHandled(Act1Event::CampClearing_Leifr))
		{
			mNpcs["Leifr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Leifr")));
			mNpcs["Leifr"]->setDialogue("Leifr_ForestCamp");
			mNpcs["Leifr"]->setPosition(sf::Vector2f(1450, 580));
			mNpcs["Leifr"]->setScale(sf::Vector2f(0.45f, 0.45f));
			mNpcs["Leifr"]->setIndex(1);
			mNpcs["Leifr"]->setInteractionPosition(sf::Vector2f(1560, 565));
			Level::load();

			mTileMap.addCollision(mNpcs["Leifr"]->getCollisionRect());
			mTileMap.setIndexOnMap(mNpcs["Leifr"]->getIndexRect(), mNpcs["Leifr"]->getIndex() - 1);
		}
		else
			Level::load();

		mTileMap.addCollision(mNpcs["DruidLeader"]->getCollisionRect());
		mTileMap.setIndexOnMap(mNpcs["DruidLeader"]->getIndexRect(), mNpcs["DruidLeader"]->getIndex() - 1);

		mDruids.setTexture(RMI.getResource(Texture::DruidsForest1));
	}
	else
		Level::load();

	RMI.loadResource(Texture::FireForestCampAnimation);
	mFireAnimation.load(RMI.getResource(Texture::FireForestCampAnimation), sf::Vector2i(2, 4), sf::milliseconds(2000), sf::Time::Zero, true);
	mFireAnimation.setIndex(9999);
	mFireAnimation.setProportions(sf::Vector2f(961, 541));
	mFireAnimation.setScaleFromHeight(541 * 2);

	mCurrentFootsteps = Footsteps::Dirt;
}

void Level_Forest_Camp::unload()
{
	RMI.unloadResource(Footsteps::Dirt);
	RMI.unloadResource(Texture::FireForestCampAnimation);
	RMI.unloadResource(Texture::DruidsForest1);
	RMI.unloadResource(Texture::BearWalk);
	RMI.unloadResource(Texture::BearIdle);
	Level::unload();
}

void Level_Forest_Camp::changeLevel()
{
	if (mPortals[ForestCampToForestRoad]->getActivated() && mPortals[ForestCampToForestRoad]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Forest_Road);
		AudioPlayer::stopHDDSound(HDDSound::Forest_Camp_Ambient);
		mRestartSounds = true;
	}
}

void Level_Forest_Camp::checkInteractEvents()
{
	if (mDroppedItemID == "bearDeer" && mCurrentNPCID == "Leifr" && !Act1Events::hasBeenTriggered(Act1Event::ForestCamp_BeerDeer))
			Act1Events::triggerEvent(Act1Event::ForestCamp_BeerDeer);

	if (mDroppedItemID == "stickWetCloth" && mObjects[mObjIndex]->getObjID() == "forestCampFire" && !Act1Events::hasBeenTriggered(Act1Event::ForestCampFire))
	{
		if (!Act1Events::hasBeenHandled(Act1Event::ForestCamp_BeerDeer))
		{
			DialogHandler::startDialogue("FireDeny_ForestCamp");

		}
		else if (Act1Events::hasBeenHandled(Act1Event::ForestCamp_BeerDeer))
		{
			mPlayer->removeItemFromInventory("stickWetCloth");
			mPlayer->addItemToInventory("torch");
			Act1Events::handleEvent(Act1Event::ForestCampFire);
		}
	}
}
void Level_Forest_Camp::checkEvents()
{
	if (DialogHandler::getDialogue("Druids_ForestCamp1").getIsOptionDisabled(3) &&
		DialogHandler::getDialogue("Druids_ForestCamp1").getIsOptionDisabled(4) &&
		!Act1Events::hasBeenTriggered(Act1Event::ForestCamp_NeedFireQuest))
		Act1Events::triggerEvent(Act1Event::ForestCamp_NeedFireQuest);
}