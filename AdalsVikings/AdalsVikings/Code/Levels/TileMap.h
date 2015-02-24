#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "..\Logics\IndexRenderer.h"

class TileMap
{
public:
	TileMap();

	void load(sf::Vector2i &tileSize, sf::Image &tileMap, sf::Image &indexMap);
	void unload();
	void render(IndexRenderer &iRenderer);

	void setTiles(sf::Vector2i &tileSize, sf::Image &image);
	void addCollision(const sf::IntRect &rect);
	void removeCollision(sf::IntRect &rect);
	void setIndexOnMap(const sf::IntRect &rect, sf::Uint8 index = 1);
	void refreshVertices();
	
	sf::Color getColorAt(sf::Vector2f &texCoord);
	int getIndexAt(sf::Vector2f &texCoord);
	sf::Vector2i getClosestTile(sf::Vector2f &pos);
	sf::Vector2i getTileSize();
	sf::Vector2i getMapSize();

	int **getTileArray();

	bool isYellow(sf::Color &color);

private:
	sf::Vertex *mVerts;
	sf::Image* mCollisionMap;
	sf::Image* mIndexMap;
	sf::Vector2i mTileSize;
	sf::Vector2i mMapSize;

	int **mTiles;
};