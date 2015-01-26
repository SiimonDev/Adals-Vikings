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
	static Path getPath(TileMap &tileMap, const sf::Vector2i &startLocation, const sf::Vector2i &endLocation);
	static sf::Vector2i getClosestNode(TileMap &tileMap, const sf::Vector2i &startLocation);
private:

};