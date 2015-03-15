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
#include "..\Logics\FolderHelper.h"

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
	mSavePath = "assets/saves/";
}

void LevelManager::load(bool reset)
{
	mLoadedLevelID = LevelFolder::NONE;
	mLoadedActID = Act::NONE;
	mLoadedPlayerPos = sf::Vector2f(-1, -1);

	NpcHandlerI.load();
	PlayerMonologueI.load();
	DialogHandler::load();
	mHud.load();
	mActionWheel.load();
	mPlayer.load();

	if (reset)
	{
		BoatEvents::initialize();
		Act1Events::initialize();
		mPlayer.clearInventory();

		loadBoatScene(reset); //<--- Change this if you want to spawn on a different act
	}
	else
	{
		BoatEvents::initialize(mSavePath + "BoatEvents.txt");
		Act1Events::initialize(mSavePath + "Act1Events.txt");
		loadSettings(mSavePath);
		
		if (mLoadedActID == Act::Ship)
			loadBoatScene(reset);
		else if (mLoadedActID == Act::Act1)
			loadAct1(reset);

		mPlayer.setPosition(mLoadedPlayerPos);
	}
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
	if (!MHI.hasActiveMenu())
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

		mLevelMap[mCurrentLevelID]->update(frameTime);
		PlayerMonologueI.update(frameTime);
	}

	if (MHI.getEvent() == MenuEvent::SavePressed)
		save(mSavePath);
}
void LevelManager::render(IndexRenderer &iRenderer)
{
	mHud.render(iRenderer);
	mLevelMap[mCurrentLevelID]->render(iRenderer);
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
	mLevelMap[mCurrentLevelID]->saveObjects();
	mCurrentLevelID = id;
	mLevelMap[mCurrentLevelID]->refreshLevel();
	save(mSavePath);

	setNearbyLevels();
	LSI.startLoading(LoadTask::LoadNearbyLevels);
	PathFinder::setTileMap(mLevelMap[mCurrentLevelID]->getTileMap());
}
void LevelManager::setNearbyLevels()
{
	mNearbyLevels.clear();
	mNearbyLevels = mLevelMap[mCurrentLevelID]->getConnectedLevels();
	mNearbyLevels.push_back(mCurrentLevelID);

	resetNearbyLevels();

	for each (LevelFolder::ID levelID in mNearbyLevels)
		mLevelMap[levelID]->setIsNearbyLevel(true);
}

void LevelManager::save(std::string savePath)
{
	// Save All the events
	if (mCurrentActID == Act::Ship)
		BoatEvents::saveEvents(savePath + "BoatEvents.txt");
	else if (mCurrentActID == Act::Act1)
		Act1Events::saveEvents(savePath + "Act1Events.txt");

	// Save some stuff
	std::ofstream itemFile(savePath + "SaveStuff.txt");
	itemFile << "*mapID: " << mCurrentLevelID << std::endl;
	itemFile << "*currentActID: " << mCurrentActID << std::endl;
	itemFile << "*playerPos: " << mPlayer.getPosition().x << ", " << mPlayer.getPosition().y << std::endl;
	itemFile.close();
}
void LevelManager::loadSettings(std::string savePath)
{
	// Load Some Stuff
	std::ifstream itemFile(savePath + "SaveStuff.txt");
	std::string line;
	while (std::getline(itemFile, line))
	{
		if (line.find("*mapID:") != std::string::npos)
		{
			int start = line.find(" ", 0);
			int end = line.size();
			std::string subString = line.substr(start + 1, (end - start) - 1);

			mLoadedLevelID = static_cast<LevelFolder::ID>(atoi(subString.c_str()));
		}
		else if (line.find("*currentActID:") != std::string::npos)
		{
			int start = line.find(" ", 0);
			int end = line.size();
			std::string subString = line.substr(start + 1, (end - start) - 1);

			mLoadedActID = static_cast<Act::ID>(atoi(subString.c_str()));
		}
		else if (line.find("*playerPos:") != std::string::npos)
		{
			int start = line.find(" ", 0);
			int end = line.find(", ", 0);
			std::string subString = line.substr(start + 1, (end - start) - 1);
			float xPos = atof(subString.c_str());

			start = end;
			end = line.size();
			subString = line.substr(start + 1, (end - start) - 1);
			float yPos = atof(subString.c_str());

			mLoadedPlayerPos = sf::Vector2f(xPos, yPos);
		}
	}
	itemFile.close();
}
void LevelManager::loadBoatScene(bool reset)
{
	mCurrentActID = Act::Ship;

	mLevelMap[LevelFolder::Ship_1] = std::move(LevelPtr(new Level_Ship_1(mPlayer, mHud, mActionWheel)));
	mLevelMap[LevelFolder::Ship_2] = std::move(LevelPtr(new Level_Ship_2(mPlayer, mHud, mActionWheel)));

	if (reset){
		mCurrentLevelID = LevelFolder::Ship_2; //<--- Change this if you want to spawn on a different level
		baseLoad(true);
	}
	else{
		if (mLoadedLevelID != LevelFolder::NONE)
			mCurrentLevelID = mLoadedLevelID;
		else
			mCurrentLevelID = LevelFolder::Ship_2;
		baseLoad(false);
	}
}
void LevelManager::loadAct1(bool reset)
{
	mCurrentActID = Act::Act1;

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

	if (mLoadedLevelID == LevelFolder::NONE)
	{
		mCurrentLevelID = LevelFolder::Beach;  //<--- Change this if you want to spawn on a different level
		baseLoad(true);
	}
	else
	{
		if (mLoadedLevelID != LevelFolder::NONE)
			mCurrentLevelID = mLoadedLevelID;
		else
			mCurrentLevelID = LevelFolder::Farm_1;

		baseLoad(false);
	}
}

Act::ID &LevelManager::getCurrentAct()
{
	return mCurrentActID;
}
void LevelManager::baseLoad(bool reset)
{
	// onödig komentar
	PortalLoader::load();
	mPlayer.refreshInventory();

	// Load all the levels
	for (std::map<LevelFolder::ID, LevelPtr>::iterator it = mLevelMap.begin(); it != mLevelMap.end(); ++it)
	{
		it->second->setBackgroundID();
		if (reset)
			it->second->resetLevel();
	}
	mLevelMap[mCurrentLevelID]->setIsNearbyLevel(true);
	mLevelMap[mCurrentLevelID]->setBackgroundID();
	mLevelMap[mCurrentLevelID]->load();
	setNearbyLevels();
	loadNearbyLevels();

	PathFinder::setTileMap(mLevelMap[mCurrentLevelID]->getTileMap());
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
		if (it->first != mCurrentLevelID &&!it->second->getIsNearbyLevel() && it->second->getIsLoaded())
		{
			std::cout << "Unloading Level: ID: " << it->first << std::endl;
			it->second->unload();
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
		if (it->first != mCurrentLevelID)
			it->second->setIsNearbyLevel(false);
	}
}
