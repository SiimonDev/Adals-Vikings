#pragma once
#include "..\Levels\TileMap.h"
#include "..\Logics\IndexRenderer.h"
#include "..\Logics\Animation.h"
#include "..\Interface\Inventory.h"
#include <SFML\Graphics.hpp>

typedef std::vector<sf::Vertex> Path;

namespace Intention
{
	enum ID
	{
		None,
		PickUp,
		Talk,
		Look,
		Interact
	};
}

namespace AnimationStyle
{
	enum ID
	{
		Right,
		Left,
		UpRight,
		UpLeft,
		Up,
		Down,
		PlayerStop,
		PlayerTalk,
		PlayerMonolog,
		PlayerIdle,
		PlayerPickup,
		Update
	};
}

namespace AnimationType
{
	enum ID
	{
		Movement,
		Idle,
		TalkToNpc,
		TalkToPlayer,
		Pickup
	};
}

class Player
{
public:
	Player();

	void load();
	void unload();
	void update(sf::Time &frameTime);
	void render(IndexRenderer &iRenderer);

	bool addItemToInventory(std::string objID);
	bool hasItemInInventory(std::string objID);
	bool removeItemFromInventory(std::string objID);
	void saveInventory();
	void refreshInventory();
	void clearInventory();
	void move(sf::Time &frameTime);
	void walkPath(Path &path);
	void playFootstepSound();
	void UpdateAnimationStyle();

	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	std::string getDroppedObjectID();
	Animation &getAnimation();

	Intention::ID getIntention();
	bool isDestinationReached();

	void setIndex(int index);
	void setPosition(sf::Vector2f &position);
	void setIntention(Intention::ID intention);
	void setAnimationStyle(AnimationType::ID type);
	void setFlip(bool value);
	void setFootsteps(Footsteps::ID footsteps);

	std::string &getName();
	float &getCurrentAlpha();

private:
	Path mCurrentPath;

	sf::Vector2f mProportions;
	sf::Vector2f mVelocity;
	sf::Vector2f mPosition;
	sf::Vector2f mScale;

	sf::Vertex mLastTarget;
	sf::Vertex mCurrentTarget;

	int mWidth;
	int mHeight;

	bool mDestinationReached;
	bool mTargetReached;
	bool mFlip;

	std::string mName;

	float mSpeed;
	float mCurrentAlpha;
	float mCurrentSpeed;
	float mTargetSpeed;
	float mAcceleration; // The speed increase/decrease every frame
	float mDistanceTraveled;
	float mTotalDistance;

	Inventory mInventory;
	Animation mPlayerAnimation;
	Intention::ID mIntention;
	AnimationStyle::ID mAnimationStyle;

	Footsteps::ID mFootsteps;
};