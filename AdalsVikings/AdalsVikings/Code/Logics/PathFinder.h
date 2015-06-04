#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include <string>
#include "..\Levels\TileMap.h"
#include "Node.h"

typedef std::vector<sf::Vertex> Path;

class PathFinder
{
public:
	static void load();
	static void unload();

	static void setTileMap(TileMap &tileMap);

	static Path getPath(const sf::Vector2f &startLoc, const sf::Vector2f &endLoc);
	static sf::Vector2i getClosestFreeTile(const sf::Vector2f &startLoc);
	
	static TileMap &getCurrentTileMap();
	static int getIndexAt(sf::Vector2f &pos);
	static float getAlphaAt(sf::Vector2f &pos);

private:
	PathFinder(){}
	PathFinder(const PathFinder&){}
	void operator=(const PathFinder&){}
};