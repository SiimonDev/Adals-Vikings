#pragma once
#include <SFML\Graphics.hpp>
#include "..\Levels\TileMap.h"
#include "..\Logics\IndexRenderer.h"

typedef std::vector<sf::Vertex> Path;

class Player
{
public:
	Player();
	~Player();

	sf::Vector2f getPosition();
	void load(TileMap &tileMap, sf::Vector2f &spawnPosition);
	void unload();
	void move(sf::Time &frameTime);
	void walkPath(Path &path);

	void update(sf::Time &frameTime);
	void render(IndexRenderer &iRenderer);

private:
	int mWidth;
	int mHeight;

	float mRotation;

	sf::Vector2f mPosition;
	sf::Vector2f mScale;
	mv::ISprite mISprite;

	float mSpeed;
	float scaleSpeed;
	float rotationSpeed;

	sf::Vertex mLastTarget;
	sf::Vertex mCurrentTarget;
	sf::Vector2f mDistanceToTarget;
	Path mCurrentPath;

	bool mDestinationReached;
	bool mTargetReached;
	sf::Vector2f mVelocity;

	int mStepsTaken;
	int mTotalSteps;
	float mAlphaPerStep;
	float mCurrentAlpha;
};