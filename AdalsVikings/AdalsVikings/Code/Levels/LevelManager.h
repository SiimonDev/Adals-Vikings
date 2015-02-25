#pragma once
#include "..\Logics\IndexRenderer.h"
#include "..\Levels\PortalLoader.h"
#include "..\Interface\ActionWheel.h"
#include "..\Objects\ObjectHandler.h"
#include "..\NPCs\NpcHandler.h"
#include <SFML\Graphics.hpp>
#include <map>
#include <memory>

#define LVLMI LevelManager::getInstance()

enum LevelID
{
	Ship_1,
	Ship_2,
	Beach,
	Road
};
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
	void changeLevel(LevelID id);

	void loadBoatScene();
	void loadAct1();

	Act &getCurrentAct();

private:
	void baseLoad();

	LevelManager();
	LevelManager(const LevelManager&);
	void operator=(const LevelManager&);

	Player mPlayer;
	ActionWheel mActionWheel;
	LevelID mCurrentID;
	Act mCurrentAct;

	std::map<LevelID, LevelPtr> mLevelMap;
	bool mLoadedPlayer;
};

