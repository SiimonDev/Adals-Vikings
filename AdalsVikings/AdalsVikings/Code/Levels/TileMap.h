#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

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
	void draw(sf::RenderWindow &window);

private:
	sf::Vertex *mVerts;
	sf::Image mCollisionMap;
	sf::Vector2i mTileSize;
	sf::Vector2i mMapSize;

	int **mTiles;
};

