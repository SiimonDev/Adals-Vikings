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
	static Path getPath(TileMap &tileMap, const sf::Vector2f &startLoc, const sf::Vector2f &endLoc);
private:
	static sf::Vector2i getClosestFreeTile(TileMap &tileMap, const sf::Vector2f &startLoc);
};