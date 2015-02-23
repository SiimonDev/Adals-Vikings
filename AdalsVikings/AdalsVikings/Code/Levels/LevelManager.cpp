#include "LevelManager.h"
#include "PortalLoader.h"
#include "Level.h"
#include "Ship_level_1.h"
#include "Ship_level_2.h"
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
, mIsActive(false)
{
}

void LevelManager::load()
{
	NpcHandler::initialize();
	DialogWindow::load();
	DialogWindow::setTextSize(30);
	DialogWindow::setTextStyle(sf::Text::Bold);

	mPlayer.load();
	mPlayer.clearInventory();
	mPlayer.setPosition(sf::Vector2f(1400, 750));
	mActionWheel.load();
}

void LevelManager::unload()
{
	NpcHandler::unload();
	DialogWindow::unload();

	mPlayer.unload();
	mActionWheel.unload();
	PathFinder::unload();
}
void LevelManager::unloadCurrentAct()
{
	for (std::map<LevelID, LevelPtr>::iterator it = mLevelMap.begin(); it != mLevelMap.end(); ++it)
	{
		it->second->unload();
	}
	mLevelMap.clear();
	AudioPlayer::unload();
	PortalLoader::unload();
}

void LevelManager::update(sf::Time &frametime)
{
	if (mIsActive)
	{
		mLevelMap[mCurrentID]->update(frametime);
		DialogWindow::update(frametime);
	}
}

void LevelManager::render(IndexRenderer &iRenderer)
{
	if (mIsActive)
	{
		mLevelMap[mCurrentID]->render(iRenderer);
		DialogWindow::render(iRenderer);
	}
}

void LevelManager::changeLevel(LevelID id)
{
	mCurrentID = id;
	std::cout << std::endl << "==========================" << std::endl;
	std::cout << "===== Changing Level =====" << std::endl;
	std::cout << "==========================" << std::endl;

	mLevelMap[mCurrentID]->saveObjects();
	mPlayer.saveInventory();
	mPlayer.refreshInventory();
	mLevelMap[mCurrentID]->refreshLevel();
	PathFinder::setTileMap(mLevelMap[mCurrentID]->getTileMap());
}

void LevelManager::loadBoatScene()
{
	mCurrentAct = Ship;
	PortalLoader::initialize();
	BoatEvents::initialize();
	if (mLevelMap.size() != 0)
		unloadCurrentAct();

	mLevelMap[Ship_1] = std::move(LevelPtr(new Ship_level_1(mPlayer, mActionWheel)));
	mLevelMap[Ship_2] = std::move(LevelPtr(new Ship_level_2(mPlayer, mActionWheel)));

	for (std::map<LevelID, LevelPtr>::iterator it = mLevelMap.begin(); it != mLevelMap.end(); ++it)
	{
		it->second->load();
		it->second->resetLevel();
	}
	mCurrentID = Ship_2;
	PathFinder::setTileMap(mLevelMap[mCurrentID]->getTileMap());
}

void LevelManager::loadAct1()
{
	mCurrentAct = Act1;
	PortalLoader::initialize();
	// If there are still maps loaded then unload them
	if (mLevelMap.size() != 0)
		unloadCurrentAct();

	mLevelMap[Beach] = LevelPtr(new Beach_level(mPlayer, mActionWheel));

	for (std::map<LevelID, LevelPtr>::iterator it = mLevelMap.begin(); it != mLevelMap.end(); ++it)
	{
		it->second->load();
		it->second->resetLevel();
	}
	mCurrentID = Beach;
	PathFinder::setTileMap(mLevelMap[mCurrentID]->getTileMap());
}

void LevelManager::setIsActive(bool value)
{
	mIsActive = value;
}

Act & LevelManager::getCurrentAct()
{
	return mCurrentAct;
}
