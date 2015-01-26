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
void TestLevel::render(sf::RenderWindow &window)
{
	window.draw(mBackground);
	mPlayer.render(window);
	mTileMap.draw(window);
}
void TestLevel::load()
{
	ResourceManager::GetInstance().load(Textures::TestBackground, "Assets/MapFiles/Ship/BoatL1.png");
	mImage.loadFromFile("Assets/MapFiles/Ship/BoatRC.png");
	mTileMap.setTiles(sf::Vector2i(20, 20), mImage);
	mBackground.setTexture(ResourceManager::GetInstance().getTexture(Textures::TestBackground));
	mPlayer.load(mTileMap, sf::Vector2f(100, 300));
	readFiles("Assets/MapFiles/Ship");

}
void TestLevel::unload()
{
	
}