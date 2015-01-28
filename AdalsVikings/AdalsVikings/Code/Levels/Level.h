#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include <External\dirent.h>
#include "..\Logics\LevelManager.h"
#include "..\Logics\ResourceManager.h"
#include "..\Logics\PathFinder.h"
#include "..\Logics\MouseState.h"
#include "..\Objects\Player.h"
#include "..\Logics\ISprite.h"
#include "TileMap.h"
#include "PortalLoader.h"
class Level
{
public:
	Level();
	virtual ~Level();

	virtual void update(sf::Time &frametime);
	virtual void render(IndexRenderer &iRenderer) = 0;
	virtual void loadAllBackgrounds(std::string filepath);
	virtual void load() = 0;
	virtual void unload() = 0;
	//virtual Portal& getPortal() = 0;

protected:
	std::vector<mv::ISprite> mBackgrounds;
	sf::Image mRCImage;

	Player mPlayer;
	TileMap mTileMap;

	PortalLoader mPortalLoader;
};

