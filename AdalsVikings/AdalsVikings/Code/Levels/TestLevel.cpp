#include "TestLevel.h"
#include <iostream>
#include "..\Logics\ResourceManager.h"

TestLevel::TestLevel()
{
	load();
}


TestLevel::~TestLevel()
{
}

void TestLevel::update(sf::Time &frametime)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		Path path = PathFinder::getPath(mTileMap, mPlayer.getPosition(), sf::Vector2f(MouseState::getInstance().getMousePosition()));
		mPlayer.walkPath(path);
	}

	mPlayer.update(frametime);
}

void TestLevel::render(IndexRenderer &iRenderer)
{
	for (int i = 0; i < mBackgrounds.size(); i++){
		iRenderer.addTexture(mBackgrounds[i]);
	}
	mPlayer.render(iRenderer);
	mTileMap.draw(iRenderer);
}

void TestLevel::load()
{
	loadAllBackgrounds("Assets/MapFiles/Ship/");
	mPlayer.load(mTileMap, sf::Vector2f(100, 300));
}

void TestLevel::unload()
{
	
}