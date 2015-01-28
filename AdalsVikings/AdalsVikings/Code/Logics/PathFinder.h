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
	static void setTileMap(TileMap &tileMap);
	static Path getPath(const sf::Vector2f &startLoc, const sf::Vector2f &endLoc);
	static sf::Vector2i getClosestFreeTile(const sf::Vector2f &startLoc);
private:
	PathFinder(){}
	PathFinder(const PathFinder&){}
	void operator=(const PathFinder&){}
};