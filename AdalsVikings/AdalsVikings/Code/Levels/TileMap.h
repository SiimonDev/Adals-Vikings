#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "..\Logics\IndexRenderer.h"

class TileMap
{
public:
	sf::Vector2i getTileSize();
	sf::Vector2i getMapSize();
	sf::Vector2i getClosestTile(sf::Vector2f &pos);

	int **getTileArray();
	sf::Color getColorAt(sf::Vector2i &texCoord);

	bool isYeallow(sf::Color &color);
	void setTiles(sf::Vector2i &tileSize, sf::Image &image);
	void draw(IndexRenderer &iRenderer);

private:
	sf::Vertex *mVerts;
	sf::Image mCollisionMap;
	sf::Vector2i mTileSize;
	sf::Vector2i mMapSize;

	int **mTiles;
};

