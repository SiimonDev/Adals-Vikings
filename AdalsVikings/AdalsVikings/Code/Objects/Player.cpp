#include "Player.h"
#include "..\Logics\ResourceManager.h"
#include "..\Logics\PathFinder.h"
#include "..\Logics\MouseState.h"
#include "..\Logics\WindowState.h"
#include "..\Logics\KeyboardState.h"
#include <iostream>
#include <math.h>

Player::Player()
	: mDestinationReached(true)
	, mTargetReached(true)
	, mVelocity()
	, mCurrentAlpha(0)
	, mPlayerAnimation()
	, mName("Ulfr")
	, mIntention(Intention::None)
{
	mSpeed = 3.f;
	mProportions = sf::Vector2f(285.7f, 512.f);
}

void Player::load()
{
	mInventory.load();

	RMI.load(Textures::UlfrIdle, "Assets/images/ulfr/character_ulfr_idle.png");
	RMI.load(Textures::UlfrBack, "Assets/images/ulfr/character_ulfr_back.png");
	RMI.load(Textures::UlfrFront, "Assets/images/ulfr/character_ulfr_front.png");
	RMI.load(Textures::UlfrWalk, "Assets/images/ulfr/character_ulfr_walk.png");
	RMI.load(Textures::UlfrTalkToNpc, "Assets/images/ulfr/character_ulfr_talk.png");
	RMI.load(Textures::UlfrTalkToPlayer, "Assets/images/ulfr/character_ulfr_front.png");
	RMI.load(Textures::UlfrStop, "assets/images/ulfr/character_ulfr_stop.png");
	RMI.load(Textures::UlfrPickup, "assets/images/ulfr/character_ulfr_pickup.png");

	mPlayerAnimation.flip(false);
	mPlayerAnimation.load(RMI.getTexture(Textures::UlfrIdle), Frames(6, 3), sf::milliseconds(1300), sf::seconds(7), true);
	mPlayerAnimation.setIndex(3);
	mPlayerAnimation.setProportions(mProportions);

	mWidth = mPlayerAnimation.getSprite().getTextureRect().width;
	mHeight = mPlayerAnimation.getSprite().getTextureRect().height;
}

void Player::unload()
{
	mInventory.unload();
	RMI.unload(Textures::UlfrBack);
	RMI.unload(Textures::UlfrFront);
	RMI.unload(Textures::UlfrWalk);
	RMI.unload(Textures::UlfrIdle);
	RMI.unload(Textures::UlfrTalkToNpc);
	RMI.unload(Textures::UlfrTalkToPlayer);
	RMI.unload(Textures::UlfrStop);
	RMI.unload(Textures::UlfrPickup);
}

bool Player::addItemToInventory(std::string objID)
{
	return mInventory.addItemToInventory(objID);
}

bool Player::hasItemInInventory(std::string objID)
{
	return mInventory.hasItemInInventory(objID);
}

bool Player::removeItemFromInventory(std::string objID)
{
	return mInventory.removeItemFromInventory(objID);
}

void Player::saveInventory()
{
	mInventory.saveInventoryToFile();
}
void Player::refreshInventory()
{
	mInventory.unloadObjects();
	mInventory.loadObjects();
}
void Player::clearInventory()
{
	mInventory.clearInventory();
}

void Player::update(sf::Time &frameTime)
{
	if (KeyboardState::isPressed(sf::Keyboard::I))
		mInventory.toggleInventory();

	mInventory.update(frameTime);

	if (mAnimationStyle == AnimationStyle::PlayerPickup && mPlayerAnimation.getStopped())
	{
		std::cout << "PICK IT  UP!!" << std::endl;
		setAnimationStyle(AnimationType::Idle);
	}
	if (mAnimationStyle == AnimationStyle::PlayerStop && mPlayerAnimation.getStopped())
	{
		setAnimationStyle(AnimationType::Idle);
	}
	// Animate the player
	mPlayerAnimation.animate(frameTime);
	mPlayerAnimation.setIndex(PathFinderI.getIndexAt(mPosition));

	// Set player alpha
	float newAlpha = PathFinderI.getAlphaAt(mPosition);
	if (newAlpha > 0)
		mCurrentAlpha = newAlpha;

	// Update the player scale
	mScale.x = ((0.35 / 120.f) * mCurrentAlpha);
	mScale.y = (0.35 / 120.f) * mCurrentAlpha;
}

void Player::render(IndexRenderer &iRenderer)
{
	mPlayerAnimation.getSprite().setOrigin(abs(mPlayerAnimation.getSprite().getTextureRect().width / 2), mPlayerAnimation.getSprite().getTextureRect().height);
	mPlayerAnimation.setScaleFromHeight(mProportions.y * mScale.y);
	mPlayerAnimation.setPosition(mPosition);
	mPlayerAnimation.render(iRenderer);
	mInventory.render(iRenderer);
}

void Player::walkPath(Path &path)
{
	mCurrentPath.clear();
	if (path.size() > 2)
	{
		mCurrentPath = path;

		mLastTarget = mCurrentPath.at(mCurrentPath.size() - 1);
		mCurrentPath.pop_back();

		mDestinationReached = false;
		mTargetReached = true;
	}
	else
	{
		mDestinationReached = true;
		mVelocity = sf::Vector2f(0, 0);
	}
}

void Player::move(sf::Time &frameTime)
{
	if (MouseState::isReleased(sf::Mouse::Left, 0.5) && !mInventory.isActive())
		walkPath(PathFinderI.getPath(getPosition(), sf::Vector2f(MouseState::getMousePosition())));

	if (!mTargetReached && !mDestinationReached)
	{
		mVelocity = mVelocity - (mVelocity * mAcceleration);

		mPosition += mVelocity;
		mDistanceTraveled += sqrt((mVelocity.x * mVelocity.x) + (mVelocity.y * mVelocity.y));

		if (mDistanceTraveled >= mTotalDistance)
		{
			mTargetReached = true;
			mVelocity = sf::Vector2f(0, 0);
		}
	}

	if (mTargetReached && !mDestinationReached)
	{
		if (!mCurrentPath.empty())
		{
			mCurrentTarget = mCurrentPath.at(mCurrentPath.size() - 1);
			sf::Vector2f distanceToTarget;
			distanceToTarget.x = mCurrentTarget.position.x - mPosition.x;
			distanceToTarget.y = mCurrentTarget.position.y - mPosition.y + 10;
			float targetAngle = (float)atan2(distanceToTarget.y, distanceToTarget.x);
			mTotalDistance = sqrt((distanceToTarget.x * distanceToTarget.x) + (distanceToTarget.y * distanceToTarget.y));

			mCurrentSpeed = ((mSpeed * mLastTarget.color.a) / 255);
			mTargetSpeed = ((mSpeed * mCurrentTarget.color.a) / 255);
			float deltaSpeed = mCurrentSpeed - mTargetSpeed;
			mAcceleration = deltaSpeed / mTotalDistance;
			mVelocity = sf::Vector2f(cos(targetAngle), sin(targetAngle)) * mCurrentSpeed;

			mDistanceTraveled = 0;

			mLastTarget = mCurrentTarget;
			mTargetReached = false;
			mCurrentPath.pop_back();
		}
		else
		{
			mDestinationReached = true;
			mVelocity = sf::Vector2f(0, 0);
		}
	}
	setAnimationStyle(AnimationType::Movement);
}

sf::Sprite Player::getSprite()
{
	return mPlayerAnimation.getSprite();
}
sf::Vector2f Player::getPosition()
{
	return mPosition;
}
std::string Player::getDroppedObjectID()
{ 
	return mInventory.getDroppedObjectID();
}

Intention::ID Player::getIntention()
{
	return mIntention;
}
bool Player::isDestinationReached()
{
	return mDestinationReached;
}

void Player::setIndex(int index)
{
	mPlayerAnimation.setIndex(index);
}

void Player::setPosition(sf::Vector2f &position)
{
	mPosition = position;
}

void Player::setIntention(Intention::ID intention)
{
	mIntention = intention;
}

void Player::setAnimationStyle(AnimationType::ID type)
{
	if (type == AnimationType::Movement && !mDestinationReached && mVelocity.x > 0.4 && mAnimationStyle != AnimationStyle::Right)
	{
		mPlayerAnimation.flip(true);
		mPlayerAnimation.load(RMI.getTexture(Textures::UlfrWalk), Frames(5, 5), sf::milliseconds(1200), sf::seconds(0), true);
		mAnimationStyle = AnimationStyle::Right;
	}
	else if (type == AnimationType::Movement && !mDestinationReached && mVelocity.x < -0.4 && mAnimationStyle != AnimationStyle::Left)
	{
		mPlayerAnimation.flip(false);
		mPlayerAnimation.load(RMI.getTexture(Textures::UlfrWalk), Frames(5, 5), sf::milliseconds(1200), sf::seconds(0), true);
		mAnimationStyle = AnimationStyle::Left;
	}
	else if (type == AnimationType::Movement && mDestinationReached && mAnimationStyle != AnimationStyle::PlayerStop && mAnimationStyle != AnimationStyle::PlayerIdle && mAnimationStyle != AnimationStyle::PlayerPickup)
	{
		mPlayerAnimation.load(RMI.getTexture(Textures::UlfrStop), Frames(5, 5), sf::milliseconds(1300), sf::Time::Zero, false);
		mAnimationStyle = AnimationStyle::PlayerStop;
	}
	else if (type == AnimationType::Idle && (mAnimationStyle != AnimationStyle::PlayerIdle))
	{
		mPlayerAnimation.load(RMI.getTexture(Textures::UlfrIdle), Frames(6, 3), sf::milliseconds(1300), sf::seconds(7), true);
		mAnimationStyle = AnimationStyle::PlayerIdle;
	}
	else if (type == AnimationType::Movement && !mDestinationReached && (mVelocity.x < 0 && mVelocity.x > -0.3 || mVelocity.x > 0 && mVelocity.x < 0.3) && mVelocity.y < 0 && mAnimationStyle != AnimationStyle::Up)
	{
		mPlayerAnimation.load(RMI.getTexture(Textures::UlfrWalk), Frames(5, 5), sf::milliseconds(1200), sf::seconds(0), true);
		mAnimationStyle = AnimationStyle::Up;
	}
	else if (type == AnimationType::Movement && !mDestinationReached && (mVelocity.x < 0 && mVelocity.x > -0.3 || mVelocity.x > 0 && mVelocity.x < 0.3) && mVelocity.y > 0 && mAnimationStyle != AnimationStyle::Down)
	{
		
		mPlayerAnimation.load(RMI.getTexture(Textures::UlfrWalk), Frames(5, 5), sf::milliseconds(1200), sf::seconds(0), true);
		mAnimationStyle = AnimationStyle::Down;
	}
	else if (type == AnimationType::TalkToNpc && mAnimationStyle != AnimationStyle::PlayerTalk)
	{
		mPlayerAnimation.flip(mFlip);
		mPlayerAnimation.load(RMI.getTexture(Textures::UlfrTalkToNpc), Frames(5, 2), sf::milliseconds(800), sf::Time::Zero, true);
		mAnimationStyle = AnimationStyle::PlayerTalk;
	}
	else if (type == AnimationType::TalkToPlayer && mAnimationStyle != AnimationStyle::PlayerMonolog)
	{
		mPlayerAnimation.flip(false);
		mPlayerAnimation.load(RMI.getTexture(Textures::UlfrFront), Frames(4, 1), sf::milliseconds(600), sf::seconds(0), true);
		mAnimationStyle = AnimationStyle::PlayerMonolog;
	}
	else if (type == AnimationType::Pickup && mAnimationStyle != AnimationStyle::PlayerPickup)
	{
		mPlayerAnimation.load(RMI.getTexture(Textures::UlfrPickup), Frames(5, 5), sf::milliseconds(1400), sf::seconds(0), false);
		mAnimationStyle = AnimationStyle::PlayerPickup;
	}
}

std::string & Player::getName()
{
	return mName;
}

float & Player::getCurrentAlpha()
{
	return mCurrentAlpha;
}

void Player::setFlip(bool value)
{
	mFlip = value;
}
Animation &Player::getAnimation()
{
	return mPlayerAnimation;
}
