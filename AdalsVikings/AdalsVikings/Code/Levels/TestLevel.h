#pragma once
#include "Level.h"
#include "TileMap.h"
#include "..\Logics\PathFinder.h"
#include "..\Logics\MouseState.h"
#include "..\Objects\Player.h"
class TestLevel : public Level
{
public:
	TestLevel();
	~TestLevel();

	void update(sf::Time &frametime);
	void render(sf::RenderWindow &window);
	void load();
	void unload();

private:
	sf::Sprite mBackground;
	sf::Image mImage;

	Player mPlayer;
	TileMap mTileMap;
};

