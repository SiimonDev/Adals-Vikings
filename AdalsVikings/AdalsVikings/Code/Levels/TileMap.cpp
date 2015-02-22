#include "TileMap.h"
#include "..\Logics\WindowState.h"
#include <cassert>
#include <iostream>

TileMap::TileMap()
{

}
TileMap::~TileMap()
{
	unload();
}

void TileMap::load(sf::Vector2i &tileSize, sf::Image &tileMap, sf::Image &indexMap)
{
	setTiles(tileSize, tileMap);
	mIndexMap = &indexMap;
}

void TileMap::unload()
{
	if (mTiles != NULL && mVerts != NULL)
	{
		for (size_t i = 0; i < mMapSize.x; i++){
			delete[] mTiles[i];
		}
		delete[] mTiles;
		delete mVerts;

		mTiles = NULL;
		mVerts = NULL;
	}
}

void TileMap::render(IndexRenderer &iRenderer)
{
	CurrentWindow.draw(mVerts, mMapSize.x * mMapSize.y, sf::Points);
}

void TileMap::setTiles(sf::Vector2i &tileSize, sf::Image &tileMap)
{
	mCollisionMap = &tileMap;
	mTileSize = tileSize;
	mMapSize.x = tileMap.getSize().x / mTileSize.x;
	mMapSize.y = tileMap.getSize().y / mTileSize.y;

	mTiles = new int*[mMapSize.x];
	for (size_t x = 0; x < mMapSize.x; x++){
		mTiles[x] = new int[mMapSize.y];
	}

	for (size_t x = 0; x < mMapSize.x; x++){
		for (size_t y = 0; y < mMapSize.y; y++){
			mTiles[x][y] = 0;
		}
	}

	mVerts = new sf::Vertex[mMapSize.x * mMapSize.y];
	for (size_t x = 0; x < mMapSize.x; x++)
	{
		for (size_t y = 0; y < mMapSize.y; y++)
		{
			sf::Color pixelColor = getColorAt(sf::Vector2f((x * mTileSize.x) + (mTileSize.x / 2), (y * mTileSize.y) + (mTileSize.y / 2)));

			sf::Color color;
			if (isYellow(pixelColor)){
				color = sf::Color::White;
				mTiles[x][y] = 0;
			}
			else{
				color = sf::Color::Black;
				mTiles[x][y] = 1;
			}

			mVerts[x + (y * mMapSize.x)] = sf::Vertex(sf::Vector2f(float((x * mTileSize.x) + (mTileSize.x / 2)), float((y * mTileSize.y) + (mTileSize.y / 2))), color);
		}
	}
}

void TileMap::addCollision(const sf::IntRect &rect)
{
	float xPos = rect.left;
	float yPos = rect.top;
	int width = rect.width;
	int height = rect.height;

	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			sf::Vector2i tile = getClosestTile(sf::Vector2f(xPos + x, yPos + y));
			mTiles[tile.x][tile.y] = 1;
		}
	}
	refreshVertices();
}

void TileMap::removeCollision(sf::IntRect &rect)
{
	float xPos = rect.left;
	float yPos = rect.top;
	int width = rect.width;
	int height = rect.height;

	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			sf::Vector2i tile = getClosestTile(sf::Vector2f(xPos + x, yPos + y));
			mTiles[tile.x][tile.y] = 0;
		}
	}
	refreshVertices();
}

void TileMap::refreshVertices()
{
	for (size_t x = 0; x < mMapSize.x; x++)
	{
		for (size_t y = 0; y < mMapSize.y; y++)
		{
			sf::Color color;
			if (mTiles[x][y] == 0){
				color = sf::Color::White;
			}
			else{
				color = sf::Color::Black;
			}

			mVerts[x + (y * mMapSize.x)] = sf::Vertex(sf::Vector2f(float((x * mTileSize.x) + (mTileSize.x / 2)), float((y * mTileSize.y) + (mTileSize.y / 2))), color);
		}
	}
}


sf::Color TileMap::getColorAt(sf::Vector2f &texCoord)
{
	assert(texCoord.x >= 0 && texCoord.x <= mCollisionMap->getSize().x);
	assert(texCoord.y >= 0 && texCoord.y <= mCollisionMap->getSize().y);
	return mCollisionMap->getPixel(texCoord.x, texCoord.y);
}
int TileMap::getIndexAt(sf::Vector2f &texCoord)
{
	assert(texCoord.x >= 0 && texCoord.x <= mIndexMap->getSize().x);
	assert(texCoord.y >= 0 && texCoord.y <= mIndexMap->getSize().y);
	return float(mIndexMap->getPixel(texCoord.x, texCoord.y).a);
}

sf::Vector2i TileMap::getClosestTile(sf::Vector2f &pos)
{
	if (pos.x >= (mMapSize.x * mTileSize.x) || pos.x <= 0){
		return sf::Vector2i();
	}
	else if (pos.y >= mMapSize.y * mTileSize.y || pos.y <= 0){
		return sf::Vector2i();
	}

	int xIndex = pos.x / mTileSize.x;
	int yIndex = pos.y / mTileSize.y;

	return sf::Vector2i(xIndex, yIndex);
}
sf::Vector2i TileMap::getTileSize()
{ 
	return mTileSize; 
}
sf::Vector2i TileMap::getMapSize()
{
	return mMapSize; 
}
int **TileMap::getTileArray(){
	return mTiles; 
}
bool TileMap::isYellow(sf::Color &color){
	if (color.b >= 0 && color.b <= 20){
		if (color.r >= 200 && color.r <= 255){
			if (color.g >= 200 && color.g <= 255){
				return true;
			}
		}
	}
	return false;
}