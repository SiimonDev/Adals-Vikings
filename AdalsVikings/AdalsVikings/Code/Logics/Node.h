#pragma once
#include <SFML\Graphics.hpp>

class Node
{
	sf::Vector2i pos;

	// total distance already travelled to reach the node
	int GValue;
	// FValue = GValue + remaining distance estimate
	int FValue;

public:
	Node(const sf::Vector2i &loc, int g, int f)
	{
		pos.x = loc.x; pos.y = loc.y; GValue = g; FValue = f;
	}

	sf::Vector2i getLocation() const { return pos; }
	int getGValue() const { return GValue; }
	int getFValue() const { return FValue; }

	void calculateFValue(const sf::Vector2i& locDest)
	{
		FValue = GValue + getHValue(locDest) * 10;
	}

	void updateGValue(const int & i) // i: direction
	{
		GValue += (i % 2 == 0 ? 10 : 14);
	}

	// Estimation function for the remaining distance to the goal.
	const int & getHValue(const sf::Vector2i& locDest) const
	{
		static int rowDistance;
		static int columnDistance;
		static int distance;

		rowDistance = locDest.x - pos.x;
		columnDistance = locDest.y - pos.y;

		// Manhattan distance
		distance = abs(rowDistance) + abs(columnDistance);

		return distance;
	}

	// Determine FValue (in the priority queue)
	friend bool operator<(const Node & a, const Node & b)
	{
		return a.getFValue() > b.getFValue();
	}
};
