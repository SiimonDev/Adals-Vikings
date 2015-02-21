#pragma once
#include "..\Levels\TileMap.h"
#include "..\Logics\IndexRenderer.h"
#include "..\Logics\Animation.h"
#include "..\Interface\Inventory.h"
#include <SFML\Graphics.hpp>

typedef std::vector<sf::Vertex> Path;

enum Intention
{
	None,
	PickUp,
	Talk,
	Look,
	Interact
};

enum AnimationStyle
{
	Right,
	Left,
	Up,
	Down,
	PlayerStop,
	PlayerTalk,
	PlayerMonolog,
	PlayerIdle,
	PlayerPickup
};

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

	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	std::string getDroppedObjectID();
	Animation &getAnimation();

	Intention getIntention();
	bool isDestinationReached();

	void setIndex(int index);
	void setPosition(sf::Vector2f &position);
	void setIntention(Intention intention);
	void setAnimationStyle(std::string style);
	void setFlip(bool value);

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
	Intention mIntention;
	AnimationStyle mAnimationStyle;
};