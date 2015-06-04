#pragma once
#include "..\Logics\IndexRenderer.h"
#include "..\Levels\PortalLoader.h"
#include "..\Interface\ActionWheel.h"
#include "..\Objects\ObjectHandler.h"
#include "..\Interface\LoadingScreen.h"
#include "..\Interface\HUD.h"
#include "..\NPCs\NpcHandler.h"
#include <SFML\Graphics.hpp>
#include <map>
#include <memory>

#define LVLMI LevelManager::getInstance()

namespace Act
{
	enum ID
	{
		NONE,
		Ship,
		Act1
	};
}

class Level;
typedef std::unique_ptr<Level> LevelPtr;

class LevelManager
{
public:
	static LevelManager &getInstance();

	void load(bool reset = true);
	void unload();
	void unloadCurrentAct();
	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void changeLevel(LevelFolder::ID id);
	void setNearbyLevels();
	void save(std::string savePath);
	void loadSettings(std::string savePath);

	void loadBoatScene(bool reset);
	void loadAct1(bool reset);
	void resetNearbyLevels();
	void loadNearbyLevels();
	void unloadCacheLevels();

	std::map<LevelFolder::ID, LevelPtr> &getCurrentLevels();
	Act::ID &getCurrentAct();

private:
	void baseLoad(bool reset);

	LevelManager();
	LevelManager(const LevelManager&);
	void operator=(const LevelManager&);

	HUD mHud;
	Player mPlayer;
	ActionWheel mActionWheel;

	LevelFolder::ID mLoadedLevelID;
	LevelFolder::ID mCurrentLevelID;
	Act::ID mLoadedActID;
	Act::ID mCurrentActID;

	std::string mSavePath;
	sf::Vector2f mLoadedPlayerPos;

	std::vector<LevelFolder::ID> mNearbyLevels;
	std::map<LevelFolder::ID, LevelPtr> mLevelMap;
	bool mLoadedPlayer;
};

