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
#include "Level_Beach.h"
#include "..\Dialog\DialogHandler.h"
#include "..\Dialog\DialogWindow.h"
#include "..\Logics\AudioPlayer.h"
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
}

void LevelManager::load()
{
	NpcHandler::load();
	DialogWindow::load();
	DialogHandler::load();
	mPlayer.load();
	mPlayer.clearInventory();
	mActionWheel.load();
}

void LevelManager::unload()
{
	NpcHandler::unload();
	DialogWindow::unload();
	DialogHandler::unload();
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

void LevelManager::update(sf::Time &frametime)
{
	mLevelMap[mCurrentID]->update(frametime);
	DialogWindow::update(frametime);
}

void LevelManager::render(IndexRenderer &iRenderer)
{
	mLevelMap[mCurrentID]->render(iRenderer);
	DialogWindow::render(iRenderer);
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

	mLevelMap[LevelFolder::Ship_1] = std::move(LevelPtr(new Level_Ship_1(mPlayer, mActionWheel)));
	mLevelMap[LevelFolder::Ship_2] = std::move(LevelPtr(new Level_Ship_2(mPlayer, mActionWheel)));
	mCurrentID = LevelFolder::Ship_2;
	baseLoad();
}

void LevelManager::loadAct1()
{
	mCurrentAct = Act1;

	// Assing ;) all the levels
	mLevelMap[LevelFolder::Beach] = LevelPtr(new Level_Beach(mPlayer, mActionWheel));
	mLevelMap[LevelFolder::Road] = LevelPtr(new Level_Road(mPlayer, mActionWheel));
	mLevelMap[LevelFolder::Forest_Road] = LevelPtr(new Level_Forest_Road(mPlayer, mActionWheel));
	mLevelMap[LevelFolder::Forest_Camp] = LevelPtr(new Level_Forest_Camp(mPlayer, mActionWheel));
	mLevelMap[LevelFolder::Church_Outside] = LevelPtr(new Level_Church_Outside(mPlayer, mActionWheel));
	mLevelMap[LevelFolder::Church_Inside] = LevelPtr(new Level_Church_Inside(mPlayer, mActionWheel));
	mLevelMap[LevelFolder::Tavern_Outside] = LevelPtr(new Level_Tavern_Outside(mPlayer, mActionWheel));
	mLevelMap[LevelFolder::Tavern_Inside] = LevelPtr(new Level_Tavern_Inside(mPlayer, mActionWheel));
	mLevelMap[LevelFolder::Camp_Clearing] = LevelPtr(new Level_Camp_Clearing(mPlayer, mActionWheel));
	mLevelMap[LevelFolder::Camp_Finished] = LevelPtr(new Level_Camp_Finished(mPlayer, mActionWheel));

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
			std::cout << "LOAD: " << it->first << std::endl;
			it->second->load();
		}
	}
}

void LevelManager::unloadCacheLevels()
{
	for (std::map<LevelFolder::ID, LevelPtr>::iterator it = mLevelMap.begin(); it != mLevelMap.end(); ++it){
		if (it->first != mCurrentID &&!it->second->getIsNearbyLevel() && it->second->getIsLoaded())
		{
			std::cout << "UNLOAD: " << it->first << std::endl;
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
