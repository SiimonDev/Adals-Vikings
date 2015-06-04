#include "PathFinder.h"
#include <cassert>
#include <iostream>
#include <queue>
#include <memory>
#include "ResourceManager.h"

using namespace std;

// Possible directions
const int iDir[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
const int jDir[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
typedef std::unique_ptr<int> intPtr;
static int **mClosedNodes;
static int **mOpenNodes;
static int **mDirMap;
static int **mSquares;

static int mMapWidth = 0;
static int mMapHeight = 0;

static TileMap* mTileMap;

void PathFinder::load()
{

}

void PathFinder::unload()
{
	for (size_t i = 0; i < mMapWidth; i++){
		delete[] mClosedNodes[i];
		delete[] mOpenNodes[i];
		delete[] mDirMap[i];
	}
	delete[] mClosedNodes;
	delete[] mOpenNodes;
	delete[] mDirMap;

	mClosedNodes = NULL;
	mOpenNodes = NULL;
	mDirMap = NULL;
	mMapWidth = 0;
	mMapHeight = 0;
}

void PathFinder::setTileMap(TileMap &tileMap)
{
	mTileMap = &tileMap;

	unload();
	mMapWidth = mTileMap->getMapSize().x;
	mMapHeight = mTileMap->getMapSize().y;
	mSquares = mTileMap->getTileArray();

	mClosedNodes = new int*[mMapWidth];
	mOpenNodes = new int*[mMapWidth];
	mDirMap = new int*[mMapWidth];

	for (size_t x = 0; x < mMapWidth; x++){
		mClosedNodes[x] = new int[mMapHeight];
		mOpenNodes[x] = new int[mMapHeight];
		mDirMap[x] = new int[mMapHeight];
	}
}

Path PathFinder::getPath(const sf::Vector2f &startLoc, const sf::Vector2f &endLoc)
{
	Path path;
	Node tempNode1;
	Node tempNode2;

	int queueIndex = 0;
	int i, j, xPos, yPos, iNext, jNext;

	sf::Vector2i startLocation = getClosestFreeTile(startLoc);
	sf::Vector2i endLocation = getClosestFreeTile(endLoc);

	// list of open (not-yet-checked-out) nodes
	priority_queue<Node> closedNodesQueue[2];

	// create the start node and push into list of open nodes
	tempNode1 = Node(startLocation, 0, 0);
	tempNode1.calculateFValue(endLocation);
	closedNodesQueue[queueIndex].push(tempNode1);

	// reset the Node lists to zero
	for (j = 0; j < mMapHeight; j++)
	{
		for (i = 0; i < mMapWidth; i++)
		{
			mClosedNodes[i][j] = 0;
			mOpenNodes[i][j] = 0;
		}
	}

	// A* search
	while (!closedNodesQueue[queueIndex].empty())
	{
		// get the current node w/ the lowest FValue
		// from the list of open nodes
		tempNode1 = Node(closedNodesQueue[queueIndex].top().getLocation(), closedNodesQueue[queueIndex].top().getGValue(), closedNodesQueue[queueIndex].top().getFValue());

		xPos = tempNode1.getLocation().x;
		yPos = tempNode1.getLocation().y;

		// remove the node from the open list
		closedNodesQueue[queueIndex].pop();
		mOpenNodes[xPos][yPos] = 0;

		// mark it on the closed nodes list
		mClosedNodes[xPos][yPos] = 1;

		// stop searching when the goal state is reached
		if (xPos == endLocation.x && yPos == endLocation.y)
		{
			// generate the path from finish to start from dirMap
			while (!(xPos == startLocation.x && yPos == startLocation.y))
			{
				//cout << "row, col=" << row << "," << col << endl;
				sf::Vector2f pos(
					float((xPos * mTileMap->getTileSize().x) + (mTileMap->getTileSize().x / 2)),
					float((yPos * mTileMap->getTileSize().y) + (mTileMap->getTileSize().y / 2)));
				path.push_back(sf::Vertex(pos, mTileMap->getColorAt(pos)));

				j = mDirMap[xPos][yPos];
				xPos += iDir[j];
				yPos += jDir[j];
			}
			// Push back the start location
			sf::Vector2f pos(
				float((startLocation.x * mTileMap->getTileSize().x) + (mTileMap->getTileSize().x / 2)),
				float((startLocation.y * mTileMap->getTileSize().y) + (mTileMap->getTileSize().y / 2)));
			path.push_back(sf::Vertex(pos, mTileMap->getColorAt(pos)));

			// empty the leftover nodes
			while (!closedNodesQueue[queueIndex].empty())
				closedNodesQueue[queueIndex].pop();
			return path;
		}

		// generate moves in all possible directions
		for (i = 0; i < 8; i++)
		{
			iNext = xPos + iDir[i];
			jNext = yPos + jDir[i];

			// if not wall (obstacle) nor in the closed list
			if (!(iNext < 0 || iNext > mMapWidth - 1 || jNext < 0 || jNext > mMapHeight - 1 || mSquares[iNext][jNext] == 1 || mClosedNodes[iNext][jNext] == 1))
			{
				// generate a child node
				tempNode2 = Node(sf::Vector2i(iNext, jNext), tempNode1.getGValue(), tempNode1.getFValue());
				tempNode2.updateGValue(i);
				tempNode2.calculateFValue(endLocation);

				// if it is not in the open list then add into that
				if (mOpenNodes[iNext][jNext] == 0) {
					mOpenNodes[iNext][jNext] = tempNode2.getFValue();
					closedNodesQueue[queueIndex].push(tempNode2);
					// mark its parent node direction
					mDirMap[iNext][jNext] = (i + 8 / 2) % 8;
				}

				// already in the open list
				else if (mOpenNodes[iNext][jNext] > tempNode2.getFValue())
				{
					// update the FValue info
					mOpenNodes[iNext][jNext] = tempNode2.getFValue();

					// update the parent direction info,  mark its parent node direction
					mDirMap[iNext][jNext] = (i + 8 / 2) % 8;

					// replace the node by emptying one q to the other one
					// except the node to be replaced will be ignored
					// and the new node will be pushed in instead
					while (!(closedNodesQueue[queueIndex].top().getLocation().x == iNext && closedNodesQueue[queueIndex].top().getLocation().y == jNext))
					{
						closedNodesQueue[1 - queueIndex].push(closedNodesQueue[queueIndex].top());
						closedNodesQueue[queueIndex].pop();
					}

					// remove the wanted node
					closedNodesQueue[queueIndex].pop();

					// empty the larger size q to the smaller one
					if (closedNodesQueue[queueIndex].size() > closedNodesQueue[1 - queueIndex].size())
						queueIndex = 1 - queueIndex;
					while (!closedNodesQueue[queueIndex].empty())
					{
						closedNodesQueue[1 - queueIndex].push(closedNodesQueue[queueIndex].top());
						closedNodesQueue[queueIndex].pop();
					}
					queueIndex = 1 - queueIndex;

					// add the better node instead
					closedNodesQueue[queueIndex].push(tempNode2);
				}
			}
		}
	}
	// no path found
	return path;
}

sf::Vector2i PathFinder::getClosestFreeTile(const sf::Vector2f &pos)
{
	float radius = 1;
	float maxRadius = 1920;
	int **squares = mTileMap->getTileArray();

	while (radius <= maxRadius)
	{
		for (float angle = 0; angle <= 360; angle += 2){
			sf::Vector2f searhLocation = pos + (sf::Vector2f(cos(angle), sin(angle)) * radius);
			sf::Vector2i tileLoc = mTileMap->getClosestTile(searhLocation);
			if (tileLoc != sf::Vector2i())
			{
				if (squares[tileLoc.x][tileLoc.y] == 0){
					return tileLoc;
				}
			}
		}
		radius += 20;
	}
	
	return sf::Vector2i(0, 0);
}

TileMap &PathFinder::getCurrentTileMap()
{
	return *mTileMap;
}

int PathFinder::getIndexAt(sf::Vector2f &pos)
{
	return mTileMap->getIndexAt(pos);
}

float PathFinder::getAlphaAt(sf::Vector2f &pos)
{
	return float(mTileMap->getColorAt(pos).a);
}