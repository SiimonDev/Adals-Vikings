#include "PathFinder.h"
#include <cassert>
#include <iostream>
#include <queue>

using namespace std;

// Possible directions
const int iDir[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
const int jDir[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

static int lastMapWidth = 0;
static int lastMapHeight = 0;

static int **closedNodes;
static int **openNodes;
static int **dirMap;

Path PathFinder::getPath(TileMap &tileMap, const sf::Vector2f &startLoc, const sf::Vector2f &endLoc)
{
	Path path;
	sf::Vector2i startLocation = getClosestFreeTile(tileMap, startLoc);
	sf::Vector2i endLocation = getClosestFreeTile(tileMap, endLoc);

	int mapWidth = tileMap.getMapSize().x;
	int mapHeight = tileMap.getMapSize().y;

	int **squares = tileMap.getTileArray();

	// This part checks if the size of the map has changed.
	// If it has then update the size of the arrays that hold the map-data
	if (lastMapWidth != mapWidth && lastMapHeight != mapHeight)
	{
		closedNodes = new int*[mapWidth];
		openNodes = new int*[mapWidth];
		dirMap = new int*[mapWidth];

		for (size_t x = 0; x < mapWidth; x++){
			closedNodes[x] = new int[mapHeight];
			openNodes[x] = new int[mapHeight];
			dirMap[x] = new int[mapHeight];
		}
	}

	lastMapWidth = mapWidth;
	lastMapHeight = mapHeight;

	// list of open (not-yet-checked-out) nodes
	priority_queue<Node> closedNodesQueue[2];

	// Queue index
	int queueIndex;

	Node* tempNode1;
	Node* tempNode2;
	int i, j, xPos, yPos, iNext, jNext;
	queueIndex = 0;

	// reset the Node lists to zero
	for (j = 0; j < mapHeight; j++)
	{
		for (i = 0; i < mapWidth; i++) 
		{
			closedNodes[i][j] = 0;
			openNodes[i][j] = 0;
		}
	}

	// create the start node and push into list of open nodes
	tempNode1 = new Node(startLocation, 0, 0);
	tempNode1->calculateFValue(endLocation);
	closedNodesQueue[queueIndex].push(*tempNode1);

	// A* search
	while (!closedNodesQueue[queueIndex].empty()) 
	{
		// get the current node w/ the lowest FValue
		// from the list of open nodes
		tempNode1 = new Node(closedNodesQueue[queueIndex].top().getLocation(), closedNodesQueue[queueIndex].top().getGValue(), closedNodesQueue[queueIndex].top().getFValue());

		xPos = tempNode1->getLocation().x;
		yPos = tempNode1->getLocation().y;

		// remove the node from the open list
		closedNodesQueue[queueIndex].pop();
		openNodes[xPos][yPos] = 0;

		// mark it on the closed nodes list
		closedNodes[xPos][yPos] = 1;

		// stop searching when the goal state is reached
		if (xPos == endLocation.x && yPos == endLocation.y) 
		{
			// generate the path from finish to start from dirMap
			while (!(xPos == startLocation.x && yPos == startLocation.y)) 
			{
				//cout << "row, col=" << row << "," << col << endl;
				sf::Vector2f pos(
					float((xPos * tileMap.getTileSize().x) + (tileMap.getTileSize().x / 2)), 
					float((yPos * tileMap.getTileSize().y) + (tileMap.getTileSize().y / 2)));
				path.push_back(sf::Vertex(pos, tileMap.getColorAt(sf::Vector2i(pos))));

				j = dirMap[xPos][yPos];
				xPos += iDir[j];
				yPos += jDir[j];
			}
			// Push back the start location
			sf::Vector2f pos(
				float((startLocation.x * tileMap.getTileSize().x) + (tileMap.getTileSize().x / 2)), 
				float((startLocation.y * tileMap.getTileSize().y) + (tileMap.getTileSize().y / 2)));
			path.push_back(sf::Vertex(pos, tileMap.getColorAt(sf::Vector2i(pos))));

			// garbage collection
			delete tempNode1;

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
			if (!(iNext < 0 || iNext > mapWidth - 1 || jNext < 0 || jNext > mapHeight - 1 || squares[iNext][jNext] == 1 || closedNodes[iNext][jNext] == 1))
			{
				// generate a child node
				tempNode2 = new Node(sf::Vector2i(iNext, jNext), tempNode1->getGValue(), tempNode1->getFValue());
				tempNode2->updateGValue(i);
				tempNode2->calculateFValue(endLocation);

				// if it is not in the open list then add into that
				if (openNodes[iNext][jNext] == 0) {
					openNodes[iNext][jNext] = tempNode2->getFValue();
					closedNodesQueue[queueIndex].push(*tempNode2);
					// mark its parent node direction
					dirMap[iNext][jNext] = (i + 8 / 2) % 8;
				}

				// already in the open list
				else if (openNodes[iNext][jNext] > tempNode2->getFValue()) 
				{
					// update the FValue info
					openNodes[iNext][jNext] = tempNode2->getFValue();

					// update the parent direction info,  mark its parent node direction
					dirMap[iNext][jNext] = (i + 8 / 2) % 8;

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
					closedNodesQueue[queueIndex].push(*tempNode2);
				}
				else delete tempNode2;
			}
		}
		delete tempNode1;
	}
	// no path found
	return path;
}

sf::Vector2i PathFinder::getClosestFreeTile(TileMap &tileMap, const sf::Vector2f &pos)
{
	float radius = 1;
	float maxRadius = 1000;
	int **squares = tileMap.getTileArray();

	while (radius <= maxRadius)
	{
		for (float angle = 0; angle <= 360; angle += 2){
			sf::Vector2f searhLocation = pos + (sf::Vector2f(cos(angle), sin(angle)) * radius);
			sf::Vector2i tileLoc = tileMap.getClosestTile(searhLocation);
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