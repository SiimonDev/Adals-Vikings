#pragma once
#include "..\Logics\ResourceManager.h"
#include "..\Logics\PathFinder.h"
#include "..\Logics\MouseState.h"
#include "..\Logics\BoatEvents.h"
#include "..\Logics\KeyboardState.h"
#include "..\Logics\Fade.h"
#include "..\Interface\ActionWheel.h"
#include "..\Objects\Player.h"
#include "..\Objects\ObjectHandler.h"
#include "..\Dialog\DialogWindow.h"
#include "..\Dialog\DialogHandler.h"
#include "..\NPCs\NpcHandler.h"
#include "LevelManager.h"
#include "TileMap.h"
#include "PortalLoader.h"
#include <External\dirent.h>
#include <SFML\Graphics.hpp>
#include <vector>

typedef std::unique_ptr<Npc> LNpcPtr;
typedef std::unique_ptr<Portal> LPortalPtr;
class Level
{
public:
	Level(Player &player, ActionWheel &ActionWheel);
	virtual ~Level();
	virtual void updateObjectActionWheel();
	virtual void updateNPCs(sf::Time frameTime);
	virtual void updateDialog(sf::Time frameTime);
	virtual void update(sf::Time &frametime);
	virtual void render(IndexRenderer &iRenderer);
	virtual void loadAllBackgrounds(std::string filepath);
	virtual void loadObjects();
	virtual void saveObjects();
	virtual void refreshLevel();
	virtual void resetLevel();
	virtual void load();
	virtual void unload();
	virtual void checkInteractEvents();
	virtual void checkEvents();

	virtual TileMap &getTileMap();

protected:
	void setDialogPosition();
	std::vector<int> mBackgroundsIndexes;
	std::vector<sf::Sprite> mBackgrounds;
	std::vector<Object*> mObjects;
	std::map<std::string, LNpcPtr> mNpcs;
	std::map<PortalId, LPortalPtr> mPortals;

	std::string mFolderPath;
	std::string mDroppedItemID;
	std::string mCurrentNPCID;

	ActionWheel *mActionWheel;
	Player &mPlayer;
	TileMap mTileMap;

	std::string mTileMapFilePath;
	std::string mIndexMapFilePath;

	Folder::ID mLevelID;

	int mObjIndex;

	bool mWalkToObject;
	bool mWalkToNPC;
	bool mIsInConversation;
	bool mOldIsInConversation;
};

