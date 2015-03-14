#include "LevelManager.h"
#include "PortalLoader.h"
#include "Level.h"
#include "Level_Ship_1.h"
#include "Level_Ship_2.h"
#include "Level_Church_Outside.h"
#include "Level_Church_Inside.h"
#include "Level_Tavern_Outside.h"
#include "Level_Tavern_Inside.h"
#include "Level_Forest_Road.h"
#include "Level_Forest_Camp.h"
#include "Level_Camp_Clearing.h"
#include "Level_Camp_Finished.h"
#include "Level_Road.h"
#include "Level_Farm_1.h"
#include "Level_Farm_2.h"
#include "Level_City_Gates.h"
#include "Level_Beach.h"
#include "Level_Beach_Hills.h"
#include "Level_Cavern_Left.h"
#include "Level_Cavern_Right.h"
#include "Level_Cliffs_Down.h"
#include "Level_Cliffs_Up.h"
#include "Level_Hills.h"
#include "Level_Ruins.h"
#include "..\Dialog\DialogHandler.h"
#include "..\Dialog\PlayerMonologue.h"
#include "..\Logics\AudioPlayer.h"
#include "..\Logics\Debug.h"
#include <iostream>

LevelManager &LevelManager::getInstance()
{
	static std::unique_ptr<LevelManager> instance;

	if (instance == NULL)
		instance = std::unique_ptr<LevelManager>(new LevelManager());

	return *instance;
}

LevelManager::LevelManager()
: mLoadedPlayer(false)
{
	DebugI.initialize(mPlayer);
}

void LevelManager::load()
{
	NpcHandlerI.load();
	PlayerMonologueI.load();
	DialogHandler::load();
	mHud.load();
	mPlayer.load();
	mPlayer.clearInventory();
	mActionWheel.load();
}

void LevelManager::unload()
{
	NpcHandlerI.unload();
	PlayerMonologueI.unload();
	DialogHandler::unload();
	mHud.unload();
	mPlayer.unload();
	mActionWheel.unload();
	PathFinder::unload();
	unloadCurrentAct();
}

void LevelManager::unloadCurrentAct()
{
	mPlayer.saveInventory();

	AudioPlayer::unload();
	PortalLoader::unload();

	for (std::map<LevelFolder::ID, LevelPtr>::iterator it = mLevelMap.begin(); it != mLevelMap.end(); ++it)
		it->second->unload();
	mLevelMap.clear();
}

void LevelManager::update(sf::Time &frameTime)
{
	mHud.update(frameTime);
	if (mHud.isInventoryButtonReleased())
		mPlayer.toggleInventory();

	if (!mPlayer.isInventoryActive())
	{
		sf::Vector2f playerPos = (sf::Vector2f(mPlayer.getSprite().getGlobalBounds().left + mPlayer.getSprite().getGlobalBounds().width / 2, mPlayer.getSprite().getGlobalBounds().top));
		PlayerMonologueI.setPosition(playerPos);
	}
	else
	{
		sf::Vector2f monologuePos = (sf::Vector2f(1920 / 2, 1080 / 4));
		PlayerMonologueI.setPosition(monologuePos);
	}

	mLevelMap[mCurrentID]->update(frameTime);
	PlayerMonologueI.update(frameTime);
}

void LevelManager::render(IndexRenderer &iRenderer)
{
	mHud.render(iRenderer);
	mLevelMap[mCurrentID]->render(iRenderer);
	PlayerMonologueI.render(iRenderer);
}

void LevelManager::changeLevel(LevelFolder::ID id)
{
	std::cout << std::endl;
	std::cout << "==========================" << std::endl;
	std::cout << "===== Changing Level =====" << std::endl;
	std::cout << "==========================" << std::endl;

	mPlayer.saveInventory();
	mPlayer.refreshInventory();
	mLevelMap[mCurrentID]->saveObjects();
	mCurrentID = id;
	mLevelMap[mCurrentID]->refreshLevel();

	setNearbyLevels();
	LSI.startLoading(LoadTask::LoadNearbyLevels);
	PathFinder::setTileMap(mLevelMap[mCurrentID]->getTileMap());
}

void LevelManager::setNearbyLevels()
{
	mNearbyLevels.clear();
	mNearbyLevels = mLevelMap[mCurrentID]->getConnectedLevels();
	mNearbyLevels.push_back(mCurrentID);

	resetNearbyLevels();

	for each (LevelFolder::ID levelID in mNearbyLevels)
		mLevelMap[levelID]->setIsNearbyLevel(true);
}

void LevelManager::loadBoatScene()
{
	mCurrentAct = Ship;

	mLevelMap[LevelFolder::Ship_1] = std::move(LevelPtr(new Level_Ship_1(mPlayer, mHud, mActionWheel)));
	mLevelMap[LevelFolder::Ship_2] = std::move(LevelPtr(new Level_Ship_2(mPlayer, mHud, mActionWheel)));
	mCurrentID = LevelFolder::Ship_2;
	baseLoad();
}

void LevelManager::loadAct1()
{
	mCurrentAct = Act1;

	// Assing ;) all the levels
	mLevelMap[LevelFolder::Beach] = LevelPtr(new Level_Beach(mPlayer, mHud, mActionWheel));
	mLevelMap[LevelFolder::Beach_Hills] = LevelPtr(new Level_Beach_Hills(mPlayer, mHud, mActionWheel));
	mLevelMap[LevelFolder::Road] = LevelPtr(new Level_Road(mPlayer, mHud, mActionWheel));
	mLevelMap[LevelFolder::Farm_1] = LevelPtr(new Level_Farm_1(mPlayer, mHud, mActionWheel));
	mLevelMap[LevelFolder::Farm_2] = LevelPtr(new Level_Farm_2(mPlayer, mHud, mActionWheel));
	mLevelMap[LevelFolder::City_Gates] = LevelPtr(new Level_City_Gates(mPlayer, mHud, mActionWheel));
	mLevelMap[LevelFolder::Forest_Road] = LevelPtr(new Level_Forest_Road(mPlayer, mHud, mActionWheel));
	mLevelMap[LevelFolder::Forest_Camp] = LevelPtr(new Level_Forest_Camp(mPlayer, mHud, mActionWheel));
	mLevelMap[LevelFolder::Church_Outside] = LevelPtr(new Level_Church_Outside(mPlayer, mHud, mActionWheel));
	mLevelMap[LevelFolder::Church_Inside] = LevelPtr(new Level_Church_Inside(mPlayer, mHud, mActionWheel));
	mLevelMap[LevelFolder::Tavern_Outside] = LevelPtr(new Level_Tavern_Outside(mPlayer, mHud, mActionWheel));
	mLevelMap[LevelFolder::Tavern_Inside] = LevelPtr(new Level_Tavern_Inside(mPlayer, mHud, mActionWheel));
	mLevelMap[LevelFolder::Camp_Clearing] = LevelPtr(new Level_Camp_Clearing(mPlayer, mHud, mActionWheel));
	mLevelMap[LevelFolder::Camp_Finished] = LevelPtr(new Level_Camp_Finished(mPlayer, mHud, mActionWheel));

	mLevelMap[LevelFolder::Cavern_Left] = LevelPtr(new Level_Cavern_Left(mPlayer, mHud, mActionWheel));
	mLevelMap[LevelFolder::Cavern_Right] = LevelPtr(new Level_Cavern_Right(mPlayer, mHud, mActionWheel));
	mLevelMap[LevelFolder::Cliffs_Down] = LevelPtr(new Level_Cliffs_Down(mPlayer, mHud, mActionWheel));
	mLevelMap[LevelFolder::Cliffs_Up] = LevelPtr(new Level_Cliffs_Up(mPlayer, mHud, mActionWheel));
	mLevelMap[LevelFolder::Hills] = LevelPtr(new Level_Hills(mPlayer, mHud, mActionWheel));
	mLevelMap[LevelFolder::Ruins] = LevelPtr(new Level_Ruins(mPlayer, mHud, mActionWheel));

	mCurrentID = LevelFolder::Forest_Camp;
	baseLoad();
}

Act &LevelManager::getCurrentAct()
{
	return mCurrentAct;
}

void LevelManager::baseLoad()
{
	// onödig komentar
	Act1Events::initialize();
	PortalLoader::load();
	mPlayer.refreshInventory();

	// Load all the levels
	for (std::map<LevelFolder::ID, LevelPtr>::iterator it = mLevelMap.begin(); it != mLevelMap.end(); ++it)
	{
		it->second->setBackgroundID();
		it->second->resetLevel();
	}
	mLevelMap[mCurrentID]->setIsNearbyLevel(true);
	mLevelMap[mCurrentID]->setBackgroundID();
	mLevelMap[mCurrentID]->load();
	setNearbyLevels();
	loadNearbyLevels();

	PathFinder::setTileMap(mLevelMap[mCurrentID]->getTileMap());
}

void LevelManager::loadNearbyLevels()
{
	for (std::map<LevelFolder::ID, LevelPtr>::iterator it = mLevelMap.begin(); it != mLevelMap.end(); ++it){
		if (it->second->getIsNearbyLevel() && !it->second->getIsLoaded())
		{
			std::cout << "Loading Level: ID: " << it->first << std::endl;
			it->second->load();
		}
	}
}

void LevelManager::unloadCacheLevels()
{
	for (std::map<LevelFolder::ID, LevelPtr>::iterator it = mLevelMap.begin(); it != mLevelMap.end(); ++it){
		if (it->first != mCurrentID &&!it->second->getIsNearbyLevel() && it->second->getIsLoaded())
		{
			std::cout << "Unloading Level: ID: " << it->first << std::endl;
			it->second->unload();
			mPlayer.saveInventory();
			it->second->setLoaded(false);
		}
	}
}

std::map<LevelFolder::ID, LevelPtr> & LevelManager::getCurrentLevels()
{
	return mLevelMap;
}

void LevelManager::resetNearbyLevels()
{
	for (std::map<LevelFolder::ID, LevelPtr>::iterator it = mLevelMap.begin(); it != mLevelMap.end(); ++it)
	{
		if (it->first != mCurrentID)
			it->second->setIsNearbyLevel(false);
	}
}
