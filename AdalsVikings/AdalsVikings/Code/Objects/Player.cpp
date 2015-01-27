#include "Player.h"
#include <math.h>
#include <iostream>
#include "..\Logics\ResourceManager.h"
#include "..\Logics\PathFinder.h"


sf::Vector2f Player::getPosition(){ return mPosition; }

bool destinationReached = true;
bool targetReached = true;
sf::Vector2f velocity;

int stepsTaken = 0;
int totalSteps = 0;
float alphaPerStep = 0;
float currentAlpha = 0;

Player::Player()
{
	rotationSpeed = 3;

	mScale = sf::Vector2f(1, 1);
	mSpeed = 3.f;
	/*mPosition = sf::Vector2f(750, 1000);*/
}

Player::~Player(){

}

void Player::load(TileMap &tileMap, sf::Vector2f &spawnPosition)
{
	mPosition.x = (PathFinder::getClosestFreeTile(tileMap, spawnPosition).x * tileMap.getTileSize().x) + tileMap.getTileSize().x / 2;
	mPosition.y = (PathFinder::getClosestFreeTile(tileMap, spawnPosition).y * tileMap.getTileSize().y) + tileMap.getTileSize().y / 2;
	ResourceManager::GetInstance().load(Textures::Player, "Assets/Images/Asteroid3.png");
	ResourceManager::GetInstance().getTexture(Textures::Player).setSmooth(true);
	mISprite.getSprite().setTexture(ResourceManager::GetInstance().getTexture(Textures::Player));
	mISprite.setIndex(3);

	mWidth = ResourceManager::GetInstance().getTexture(Textures::Player).getSize().x;
	mHeight = ResourceManager::GetInstance().getTexture(Textures::Player).getSize().y;
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
		currentPath = path;

		lastTarget = currentPath.at(currentPath.size() - 1);
		currentPath.pop_back();

		destinationReached = false;
		targetReached = true;
	}
}

void Player::move(sf::Time &frameTime){

	if (targetReached && !destinationReached)
	{
		if (!currentPath.empty())
		{
			currentTarget = currentPath.at(currentPath.size() - 1);

			// Calculate what speed the player should be moving at.
			// First we see what baspeed the player has (based on tha alpha of the current position).
			// After this we calculate the difference in alpha between the current position and the target position.
			// Last we determine the speed based on how long the player have to trawel (how big the alpha-difference is)
			float bSpeed = ((mSpeed * currentTarget.color.a) / 255);
			float alphaDiff = float(lastTarget.color.a) - float(currentTarget.color.a);
			float speed = bSpeed - (abs(alphaDiff) / 255);

			// Calculate the angle toward the next target
			// and then use this angle to create a velocity (the size of and angle of a "step")
			distanceToTarget.x = currentTarget.position.x - mPosition.x;
			distanceToTarget.y = currentTarget.position.y - mPosition.y;
			float pointAngle = (float)atan2(distanceToTarget.y, distanceToTarget.x);
			velocity = sf::Vector2f(cos(pointAngle), sin(pointAngle)) * speed;

			// Calculate how many steps that has to be taken to reach the goal
			// using pythagoras algorithm (the lenth of the distance vector / the length of the velocity vector)
			float distanceLength = sqrt((distanceToTarget.x * distanceToTarget.x) + (distanceToTarget.y * distanceToTarget.y));
			float velocityLength = sqrt(((velocity.x * velocity.x) + (velocity.y * velocity.y)));
			totalSteps = distanceLength / velocityLength;
			alphaPerStep = (alphaDiff / float(totalSteps));
			currentAlpha = float(lastTarget.color.a);

			lastTarget = currentTarget;
			targetReached = false;
			currentPath.pop_back();
		}
		else
		{
			destinationReached = true;
		}
	}

	if (!targetReached && !destinationReached)
	{
		stepsTaken++;

		// Take a step (position + the angle and lenths of a step (velocity))
		mPosition += velocity;

		// Incrementally reduce/increase the alpha every step.
		currentAlpha -= alphaPerStep;
		mScale.x = (1.f / 100.f) * currentAlpha;
		mScale.y = (1.f / 100.f) * currentAlpha;

		// Check if the total number if steps has been taken
		// if it has then set the target as reached and reset the stepcounter
		if (stepsTaken >= totalSteps){
			targetReached = true;
			stepsTaken = 0;
		}
	}
}

void Player::render(IndexRenderer &iRenderer)
{
	mISprite.getSprite().setOrigin(mWidth / 2, mHeight / 2);
	mISprite.getSprite().setPosition(mPosition);
	mISprite.getSprite().setRotation(mRotation);
	mISprite.getSprite().setScale(mScale);
	iRenderer.addTexture(mISprite);
}