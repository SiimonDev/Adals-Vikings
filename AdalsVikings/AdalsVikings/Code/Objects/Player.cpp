#include "Player.h"
#include <math.h>
#include <iostream>
#include "..\Logics\ResourceManager.h"
#include "..\Logics\PathFinder.h"


Player::Player()
	: mDestinationReached(true)
	, mTargetReached(true)
	, mVelocity(sf::Vector2f(0,0))
	, mStepsTaken(0)
	, mTotalSteps(0)
	, mAlphaPerStep(0)
	, mCurrentAlpha(0)
{
	rotationSpeed = 3;

	mScale = sf::Vector2f(1, 1);
	mSpeed = 3.f;
	/*mPosition = sf::Vector2f(750, 1000);*/
}

Player::~Player(){

}

sf::Vector2f Player::getPosition()
{ 
	return mPosition; 
}

void Player::load(TileMap &tileMap, sf::Vector2f &spawnPosition){

	mPosition.x = (PathFinder::getClosestFreeTile(tileMap, spawnPosition).x * tileMap.getTileSize().x) + tileMap.getTileSize().x / 2;
	mPosition.y = (PathFinder::getClosestFreeTile(tileMap, spawnPosition).y * tileMap.getTileSize().y) + tileMap.getTileSize().y / 2;
	ResourceManager::GetInstance().load(Textures::Player, "Assets/Images/Asteroid3.png");

	ResourceManager::GetInstance().getTexture(Textures::Player).setSmooth(true);
	mPlayerSprite.setTexture(ResourceManager::GetInstance().getTexture(Textures::Player));
}
void Player::unload()
{
	ResourceManager::GetInstance().unload(Textures::Player);
}
void Player::update(sf::Time &frameTime){
	mRotation += rotationSpeed;
	move(frameTime);
}

void Player::walkPath(Path &path){
	if (path.size() > 0)
	{
		mCurrentPath = path;

		mLastTarget = mCurrentPath.at(mCurrentPath.size() - 1);
		mCurrentPath.pop_back();

		mDestinationReached = false;
		mTargetReached = true;
	}
}

void Player::move(sf::Time &frameTime){

	if (mTargetReached && !mDestinationReached)
	{
		if (!mCurrentPath.empty())
		{
			mCurrentTarget = mCurrentPath.at(mCurrentPath.size() - 1);

			// Calculate what speed the player should be moving at.
			// First we see what baspeed the player has (based on tha alpha of the current position).
			// After this we calculate the difference in alpha between the current position and the target position.
			// Last we determine the speed based on how long the player have to trawel (how big the alpha-difference is)
			float bSpeed = ((mSpeed * mCurrentTarget.color.a) / 255);
			float alphaDiff = float(mLastTarget.color.a) - float(mCurrentTarget.color.a);
			float speed = bSpeed - (abs(alphaDiff) / 255);

			// Calculate the angle toward the next target
			// and then use this angle to create a mVelocity (the size of and angle of a "step")
			mDistanceToTarget.x = mCurrentTarget.position.x - mPosition.x;
			mDistanceToTarget.y = mCurrentTarget.position.y - mPosition.y;
			float pointAngle = (float)atan2(mDistanceToTarget.y, mDistanceToTarget.x);
			mVelocity = sf::Vector2f(cos(pointAngle), sin(pointAngle)) * speed;

			// Calculate how many steps that has to be taken to reach the goal
			// using pythagoras algorithm (the lenth of the distance vector / the length of the mVelocity vector)
			float distanceLength = sqrt((mDistanceToTarget.x * mDistanceToTarget.x) + (mDistanceToTarget.y * mDistanceToTarget.y));
			float mVelocityLength = sqrt(((mVelocity.x * mVelocity.x) + (mVelocity.y * mVelocity.y)));
			mTotalSteps = distanceLength / mVelocityLength;
			mAlphaPerStep = (alphaDiff / float(mTotalSteps));
			mCurrentAlpha = float(mLastTarget.color.a);

			mLastTarget = mCurrentTarget;
			mTargetReached = false;
			mCurrentPath.pop_back();
		}
		else
		{
			mDestinationReached = true;
		}
	}

	if (!mTargetReached && !mDestinationReached)
	{
		mStepsTaken++;

		// Take a step (position + the angle and lenths of a step (mVelocity))
		mPosition += mVelocity;

		// Incrementally reduce/increase the alpha every step.
		mCurrentAlpha -= mAlphaPerStep;
		mScale.x = (1.f / 100.f) * mCurrentAlpha;
		mScale.y = (1.f / 100.f) * mCurrentAlpha;

		// Check if the total number if steps has been taken
		// if it has then set the target as reached and reset the stepcounter
		if (mStepsTaken >= mTotalSteps){
			mTargetReached = true;
			mStepsTaken = 0;
		}
	}
}

void Player::render(sf::RenderWindow &window)
{
	mWidth = ResourceManager::GetInstance().getTexture(Textures::Player).getSize().x;
	mHeight = ResourceManager::GetInstance().getTexture(Textures::Player).getSize().y;
	mPlayerSprite.setOrigin(mWidth / 2, mHeight / 2);
	mPlayerSprite.setPosition(mPosition);
	mPlayerSprite.setRotation(mRotation);
	mPlayerSprite.setScale(mScale);
	window.draw(mPlayerSprite);
}