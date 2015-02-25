#include "LevelManager.h"
#include "PortalLoader.h"
#include "Level.h"
#include "Ship_level_1.h"
#include "Ship_level_2.h"
#include "Church_Level.h"
#include "Road_Level.h"
#include "Beach_Level.h"
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
	DialogWindow::setTextSize(30);
	DialogWindow::setTextStyle(sf::Text::Bold);
	

	mPlayer.load();
	mPlayer.clearInventory();
	mActionWheel.load();
}

void LevelManager::unload()
{
	NpcHandler::unload();
	DialogWindow::unload();

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
	mCurrentID = id;
	/*//std::cout << std::endl;
	//std::cout << "==========================" << std::endl;
	//std::cout << "===== Changing Level =====" << std::endl;
	//std::cout << "==========================" << std::endl;*/

	mLevelMap[mCurrentID]->saveObjects();
	mPlayer.saveInventory();
	mPlayer.refreshInventory();
	mLevelMap[mCurrentID]->refreshLevel();
	PathFinder::setTileMap(mLevelMap[mCurrentID]->getTileMap());
}

void LevelManager::loadBoatScene()
{
	mCurrentAct = Ship;

	// Assign all the levels
	mLevelMap[LevelFolder::Ship_1] = std::move(LevelPtr(new Ship_level_1(mPlayer, mActionWheel)));
	mLevelMap[LevelFolder::Ship_2] = std::move(LevelPtr(new Ship_level_2(mPlayer, mActionWheel)));
	mCurrentID = LevelFolder::Ship_2;
	baseLoad();
}

void LevelManager::loadAct1()
{
	mCurrentAct = Act1;

	// Assing all the levels
	mLevelMap[LevelFolder::Beach] = LevelPtr(new Beach_level(mPlayer, mActionWheel));
	mLevelMap[LevelFolder::Road] = LevelPtr(new Road_Level(mPlayer, mActionWheel));
	mLevelMap[LevelFolder::Church] = LevelPtr(new Church_Level(mPlayer, mActionWheel));
	mCurrentID = LevelFolder::Beach;
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
	for (std::map<LevelFolder::ID, LevelPtr>::iterator it = mLevelMap.begin(); it != mLevelMap.end(); ++it){
		it->second->load();
		it->second->resetLevel();
	}

	PathFinder::setTileMap(mLevelMap[mCurrentID]->getTileMap());
}