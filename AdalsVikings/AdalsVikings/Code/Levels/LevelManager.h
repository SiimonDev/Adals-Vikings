#pragma once
#include "..\Logics\IndexRenderer.h"
#include "..\Levels\PortalLoader.h"
#include "..\Interface\ActionWheel.h"
#include "..\Objects\ObjectHandler.h"
#include "..\Interface\LoadingScreen.h"
#include "..\NPCs\NpcHandler.h"
#include <SFML\Graphics.hpp>
#include <map>
#include <memory>

#define LVLMI LevelManager::getInstance()

enum Act
{
	Ship,
	Act1
};

class Level;
typedef std::unique_ptr<Level> LevelPtr;

class LevelManager
{
public:
	static LevelManager &getInstance();

	void load();
	void unload();
	void unloadCurrentAct();
	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void changeLevel(LevelFolder::ID id);
	void setNearbyLevels();

	void loadBoatScene();
	void loadAct1();
	void resetNearbyLevels();
	void loadNearbyLevels();
	void unloadCacheLevels();

	std::map<LevelFolder::ID, LevelPtr> &getCurrentLevels();
	Act &getCurrentAct();

private:
	void baseLoad();

	LevelManager();
	LevelManager(const LevelManager&);
	void operator=(const LevelManager&);

	Player mPlayer;
	ActionWheel mActionWheel;
	LevelFolder::ID mCurrentID;
	Act mCurrentAct;

	std::vector<LevelFolder::ID> mNearbyLevels;
	std::map<LevelFolder::ID, LevelPtr> mLevelMap;
	bool mLoadedPlayer;
};

