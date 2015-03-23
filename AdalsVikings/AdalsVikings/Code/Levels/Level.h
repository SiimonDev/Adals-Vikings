#pragma once
#include "..\Logics\ResourceManager.h"
#include "..\Logics\PathFinder.h"
#include "..\Logics\MouseState.h"
#include "..\Logics\BoatEvents.h"
#include "..\Logics\Act1Events.h"
#include "..\Logics\KeyboardState.h"
#include "..\Logics\Fade.h"
#include "..\Logics\Fade.h"
#include "..\Interface\ActionWheel.h"
#include "..\Interface\HUD.h"
#include "..\Objects\Player.h"
#include "..\Objects\ObjectHandler.h"
#include "..\Dialog\PlayerMonologue.h"
#include "..\Dialog\DialogHandler.h"
#include "..\NPCs\NpcHandler.h"
#include "LevelManager.h"
#include "TileMap.h"
#include "PortalLoader.h"
//#include <External\dirent.h>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <vector>

class Level
{
public:
	Level(Player &player, HUD &hud, ActionWheel &ActionWheel);
	virtual void updateObjects(sf::Time frameTime);
	virtual void updateNPCs(sf::Time frameTime);
	virtual void updateDialog(sf::Time frameTime);
	virtual void update(sf::Time &frametime);
	virtual void render(IndexRenderer &iRenderer);
	virtual void loadAllBackgrounds();
	virtual void loadObjects();
	virtual void saveObjects();
	virtual void refreshLevel(bool resetObjects = false);
	virtual void resetLevel();
	virtual void load();
	virtual void unload();
	virtual void checkInteractEvents();
	virtual void checkEvents();
	virtual void setLoaded(bool value);
	virtual void setIsNearbyLevel(bool value);
	virtual void setBackgroundID();

	virtual bool &getIsNearbyLevel();
	virtual bool &getIsLoaded();
	virtual TileMap &getTileMap();
	virtual std::vector<LevelFolder::ID> getConnectedLevels();

protected:
	virtual void restartSounds();

	std::vector<int> mBackgroundsIndexes;
	std::vector<sf::Sprite> mBackgrounds;
	std::vector<Object*> mObjects;
	std::map<std::string, NpcPtr> mNpcs;
	std::map<PortalId, Portal*> mPortals;
	std::vector<LevelFolder::ID> MConnectedLevels;

	std::string mFolderPath;
	std::string mDroppedItemID;
	std::string mCurrentNPCID;
	std::ifstream mInstream;
	std::ofstream mOfstream;

	ActionWheel *mActionWheel;
	Player* mPlayer;
	HUD* mHud;
	TileMap mTileMap;

	std::string mTileMapFilePath;
	std::string mIndexMapFilePath;

	LevelFolder::ID mBackgroundID;
	Footsteps::ID mCurrentFootsteps;

	sf::Time mConversationCooldownTime;

	int mObjIndex;

	float mAmbientSoundLevel;
	float mMusicSoundLevel;

	bool mWalkToObject;
	bool mWalkToNPC;
	bool mIsInConversation;
	bool mOldIsInConversation;
	bool mConversationStopped;
	bool mIsNearbyLevel, mIsLoaded, mHasBeenReset;
	bool mRestartSounds;
	bool mUIUpdate;
};

