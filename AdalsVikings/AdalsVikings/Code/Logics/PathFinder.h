#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include <string>
#include "..\Levels\TileMap.h"
#include "Node.h"

#define PathFinderI PathFinder::getInstance()

typedef std::vector<sf::Vertex> Path;

class PathFinder
{
public:
	static PathFinder &getInstance();

	void load();
	void unload();

	void setTileMap(TileMap &tileMap);

	Path getPath(const sf::Vector2f &startLoc, const sf::Vector2f &endLoc);
	sf::Vector2i getClosestFreeTile(const sf::Vector2f &startLoc);
	
	TileMap &getCurrentTileMap();
	int getIndexAt(sf::Vector2f &pos);
	float getAlphaAt(sf::Vector2f &pos);

private:
	PathFinder();
	PathFinder(const PathFinder&){}
	void operator=(const PathFinder&){}

	int **mClosedNodes;
	int **mOpenNodes;
	int **mDirMap;
	int **mSquares;

	int mMapWidth;
	int mMapHeight;

	TileMap* mTileMap;
};