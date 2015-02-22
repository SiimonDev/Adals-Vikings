#include "LevelManager.h"
#include "..\Dialog\DialogWindow.h"
#include "..\Logics\BoatEvents.h"
#include "Level.h"
#include "Ship_level_1.h"
#include "Ship_level_2.h"
#include "Beach_Level.h"
#include "PortalLoader.h"
#include <iostream>

LevelManager &LevelManager::getInstance()
{
	static LevelManager instance;
	return instance;
}

LevelManager::LevelManager()
: mLoadedPlayer(false)
{
}

LevelManager::~LevelManager()
{
	//for (std::map<LevelID, LevelPtr>::iterator it = mLevelMap.begin(); it != mLevelMap.end(); ++it)
	//{
	//	delete it->second;
	//}
	//mLevelMap.clear();
}

void LevelManager::load()
{
	NpcHandler::initialize();
	PortalLoader::initialize();
	DialogWindow::load();
	DialogWindow::setTextSize(30);
	DialogWindow::setTextStyle(sf::Text::Bold);

	mPlayer.load();
	mPlayer.clearInventory();
	mPlayer.setPosition(sf::Vector2f(1400, 750));
	mActionWheel.load();
	
	loadBoatScene();
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
	for (std::map<LevelID, LevelPtr>::iterator it = mLevelMap.begin(); it != mLevelMap.end(); ++it)
	{
		it->second->unload();
		delete it->second;
		mLevelMap.erase(it);
		it = mLevelMap.begin();
	}
	AudioPlayer::unload();
	mLevelMap.clear();
}

void LevelManager::update(sf::Time &frametime)
{
	mCurrentLevel->update(frametime);
	DialogWindow::update(frametime);
}

void LevelManager::render(IndexRenderer &iRenderer)
{
	mCurrentLevel->render(iRenderer);
	DialogWindow::render(iRenderer);
}

void LevelManager::changeLevel(LevelID id)
{
	std::cout << std::endl << "==========================" << std::endl;
	std::cout << "===== Changing Level =====" << std::endl;
	std::cout << "==========================" << std::endl;

	mCurrentLevel->saveObjects();
	mPlayer.saveInventory();
	mPlayer.refreshInventory();
	mCurrentLevel = mLevelMap[id];
	mCurrentLevel->refreshLevel();
	PathFinder::setTileMap(mCurrentLevel->getTileMap());
}

void LevelManager::loadBoatScene()
{
	BoatEvents::initialize();
	if (mLevelMap.size() != 0)
		unloadCurrentAct();

	mLevelMap[Ship_1] = LevelPtr(new Ship_level_1(mPlayer, mActionWheel));
	mLevelMap[Ship_2] = LevelPtr(new Ship_level_2(mPlayer, mActionWheel));

	for (std::map<LevelID, LevelPtr>::iterator it = mLevelMap.begin(); it != mLevelMap.end(); ++it)
	{
		it->second->load();
		it->second->resetLevel();
	}
	mCurrentLevel = mLevelMap[Ship_2];
	PathFinder::setTileMap(mCurrentLevel->getTileMap());
}

void LevelManager::loadAct1()
{
	// If there are still maps loaded then unload them
	if (mLevelMap.size() != 0)
		unloadCurrentAct();

	mLevelMap[Beach] = LevelPtr(new Beach_level(mPlayer, mActionWheel));

	for (std::map<LevelID, LevelPtr>::iterator it = mLevelMap.begin(); it != mLevelMap.end(); ++it)
	{
		it->second->load();
		it->second->resetLevel();
	}
	mCurrentLevel = mLevelMap[Beach];
	PathFinder::setTileMap(mCurrentLevel->getTileMap());
}