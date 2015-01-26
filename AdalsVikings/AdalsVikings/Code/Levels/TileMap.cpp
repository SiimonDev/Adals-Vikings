#include "TileMap.h"
#include <cassert>
#include <iostream>

sf::Vector2i TileMap::getTileSize(){ return mTileSize; }
sf::Vector2i TileMap::getMapSize(){ return mMapSize; }

int **TileMap::getTileArray(){ return mTiles; }

bool TileMap::isYeallow(sf::Color &color){
	// Check if blue is between 0 - 10
	// Check if red is between 200 - 255
	// Check if green is between 200 - 255
	if (color.b >= 0 && color.b <= 10){
		if (color.r >= 200 && color.r <= 255){
			if (color.g >= 200 && color.g <= 255){
				return true;
			}
		}
	}
	return false;
}

sf::Color TileMap::getColorAt(sf::Vector2i &texCoord){
	// Get the color at a sertain point in the collision-map
	// and also make sure that this point is within the bounderies of the image
	assert(texCoord.x >= 0 && texCoord.x <= mCollisionMap.getSize().x);
	assert(texCoord.y >= 0 && texCoord.y <= mCollisionMap.getSize().y);
	return mCollisionMap.getPixel(texCoord.x, texCoord.y);
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

void TileMap::setTiles(sf::Vector2i &tileSize, sf::Image &image){
	mCollisionMap = image;
	mTileSize = tileSize;
	mMapSize.x = image.getSize().x / mTileSize.x;
	mMapSize.y = image.getSize().y / mTileSize.y;

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
	for (size_t x = 0; x < mMapSize.x; x++){
		for (size_t y = 0; y < mMapSize.y; y++){

			sf::Color pixelColor = getColorAt(sf::Vector2i((x * mTileSize.x) + (mTileSize.x / 2), (y * mTileSize.y) + (mTileSize.y / 2)));
			//std::cout << float(pixelColor.r) << ", " << float(pixelColor.g) << ", " << float(pixelColor.b) << ", " << float(pixelColor.a) <<std::endl;

			sf::Color color;
			if (isYeallow(pixelColor)){
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

void TileMap::draw(sf::RenderWindow &window)
{
	//window.draw(mVerts, mMapSize.x * mMapSize.y, sf::Points);
}