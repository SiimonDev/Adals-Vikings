#include "TestLevel.h"
#include <iostream>
#include "..\Logics\ResourceManager.h"
#include "..\Logics\PathFinder.h"

TestLevel::TestLevel()
{
	load();
	mPortalLoader.getPortal(Portal1).setRightWorld(true);
}


TestLevel::~TestLevel()
{
}

void TestLevel::update(sf::Time &frametime)
{
	mPlayer.update(frametime);
	mPortalLoader.getPortal(Portal1).update(frametime, mPlayer);
	Level::update(frametime);
}

void TestLevel::render(IndexRenderer &iRenderer)
{
	for (int i = 0; i < mBackgrounds.size(); i++){
		iRenderer.addISprite(mBackgrounds[i]);
	}
	mPlayer.render(iRenderer);
	mTileMap.draw(iRenderer);
}

void TestLevel::load()
{
	PathFinder::setTileMap(mTileMap);
	loadAllBackgrounds("Assets/MapFiles/Ship/");
	mPlayer.load(mTileMap, sf::Vector2f(100, 300));
}

void TestLevel::unload()
{
	
}
//Portal& TestLevel::getPortal()
//{
//	return mPortals.getPortal(Testportal1);
//}
