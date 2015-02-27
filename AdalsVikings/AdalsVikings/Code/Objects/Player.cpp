#include "Player.h"
#include "..\Logics\ResourceManager.h"
#include "..\Logics\PathFinder.h"
#include "..\Logics\MouseState.h"
#include "..\Logics\KeyboardState.h"
#include "..\Logics\AudioPlayer.h"
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
	mSpeed = 4.f;
	mProportions = sf::Vector2f(285.7f, 512.f);
}

void Player::load()
{
	mInventory.load();

	RMI.loadResource(Texture::UlfrIdle);
	RMI.loadResource(Texture::UlfrWalk);
	RMI.loadResource(Texture::UlfrTalkToNpc);
	RMI.loadResource(Texture::UlfrTalkToPlayer);
	RMI.loadResource(Texture::UlfrStop);
	RMI.loadResource(Texture::UlfrPickup);
	RMI.loadResource(Texture::UlfrWalkUp);
	mPlayerAnimation.flip(false);
	mPlayerAnimation.load(RMI.getResource(Texture::UlfrIdle), Frames(6, 3), sf::milliseconds(1300), sf::seconds(7), true);
	mPlayerAnimation.setIndex(3);
	mPlayerAnimation.setProportions(mProportions);

	mWidth = mPlayerAnimation.getSprite().getTextureRect().width;
	mHeight = mPlayerAnimation.getSprite().getTextureRect().height;
}

void Player::unload()
{
	mInventory.unload();
	RMI.unloadResource(Texture::UlfrWalk);
	RMI.unloadResource(Texture::UlfrIdle);
	RMI.unloadResource(Texture::UlfrTalkToNpc);
	RMI.unloadResource(Texture::UlfrTalkToPlayer);
	RMI.unloadResource(Texture::UlfrStop);
	RMI.unloadResource(Texture::UlfrPickup);
	RMI.unloadResource(Texture::UlfrWalkUp);
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
		//std::cout << "PICK IT  UP!!" << std::endl;
		setAnimationStyle(AnimationType::Idle);
	}
	if (mAnimationStyle == AnimationStyle::PlayerStop && mPlayerAnimation.getStopped())
	{
		setAnimationStyle(AnimationType::Idle);
	}
	// Animate the player
	mPlayerAnimation.animate(frameTime);

	// Set player Index
	float newIndex = PathFinder::getIndexAt(mPosition);
	if (newIndex > 0)
		mPlayerAnimation.setIndex(newIndex);

	// Set player alpha
	float newAlpha = PathFinder::getAlphaAt(mPosition);
	if (newAlpha > 0)
		mCurrentAlpha = newAlpha;

	// Update the player scale
	mScale.x = ((0.35 / 120.f) * mCurrentAlpha);
	mScale.y = (0.35 / 120.f) * mCurrentAlpha;

	playFootstepSound();
}

void Player::render(IndexRenderer &iRenderer)
{
	mPlayerAnimation.getSprite().setOrigin(abs(mPlayerAnimation.getSprite().getTextureRect().width / 2), mPlayerAnimation.getSprite().getTextureRect().height);
	mPlayerAnimation.setScaleFromHeight(mProportions.y * mScale.y);
	mPlayerAnimation.setPosition(mPosition);
	mPlayerAnimation.render(iRenderer);
	mInventory.render(iRenderer);
}

void Player::move(sf::Time &frameTime)
{
	if (MouseState::isReleased(sf::Mouse::Left, 0.5) && !mInventory.isActive())
		walkPath(PathFinder::getPath(getPosition(), sf::Vector2f(MouseState::getMousePosition())));

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

void Player::playFootstepSound()
{
	if (mAnimationStyle == AnimationStyle::Left || mAnimationStyle == AnimationStyle::Right || mAnimationStyle == AnimationStyle::Up || mAnimationStyle == AnimationStyle::Down)
	{
		if (mPlayerAnimation.getCurrentFrame() == 0 || mPlayerAnimation.getCurrentFrame() == 14)
		{
			if (RMI.getResource(mFootsteps).size() > 0)
				AudioPlayer::playRandomSound(mFootsteps);
			else
				AudioPlayer::playRandomSound(Footsteps::Default);
		}
	}
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
Animation &Player::getAnimation()
{
	return mPlayerAnimation;
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
	if (type == AnimationType::Movement && !mDestinationReached && mVelocity.x > 0.4/* && mVelocity.y >= 0*/ && mAnimationStyle != AnimationStyle::Right)
	{
		setFlip(true);
		mPlayerAnimation.flip(mFlip);
		mPlayerAnimation.load(RMI.getResource(Texture::UlfrWalk), Frames(5, 5), sf::milliseconds(1200), sf::seconds(0), true);
		mAnimationStyle = AnimationStyle::Right;
	}
	else if (type == AnimationType::Movement && !mDestinationReached && mVelocity.x < -0.4 /*&& mVelocity.y >= 0*/ && mAnimationStyle != AnimationStyle::Left)
	{
		setFlip(false);
		mPlayerAnimation.flip(mFlip);
		mPlayerAnimation.load(RMI.getResource(Texture::UlfrWalk), Frames(5, 5), sf::milliseconds(1200), sf::seconds(0), true);
		mAnimationStyle = AnimationStyle::Left;
	}
	/*else if (type == AnimationType::Movement && !mDestinationReached && mVelocity.x < -0.4 && mVelocity.y < 0 && mAnimationStyle != AnimationStyle::UpLeft)
	{
		setFlip(false);
		mPlayerAnimation.flip(mFlip);
		mPlayerAnimation.load(RMI.getResource(Texture::UlfrWalkUp), Frames(5, 5), sf::milliseconds(1200), sf::seconds(0), true);
		mAnimationStyle = AnimationStyle::UpLeft;
	}
	else if (type == AnimationType::Movement && !mDestinationReached && mVelocity.x > 0.4 && mVelocity.y < 0 && mAnimationStyle != AnimationStyle::UpRight)
	{
		setFlip(true);
		mPlayerAnimation.flip(mFlip);
		mPlayerAnimation.load(RMI.getResource(Texture::UlfrWalkUp), Frames(5, 5), sf::milliseconds(1200), sf::seconds(0), true);
		mAnimationStyle = AnimationStyle::UpRight;

	}*/
	else if (type == AnimationType::Movement && mDestinationReached && mAnimationStyle != AnimationStyle::PlayerStop && mAnimationStyle != AnimationStyle::PlayerIdle && mAnimationStyle != AnimationStyle::PlayerPickup)
	{
		mPlayerAnimation.flip(mFlip);
		mPlayerAnimation.load(RMI.getResource(Texture::UlfrStop), Frames(5, 5), sf::milliseconds(1300), sf::Time::Zero, false);
		mAnimationStyle = AnimationStyle::PlayerStop;
	}
	else if (type == AnimationType::Idle && (mAnimationStyle != AnimationStyle::PlayerIdle))
	{
		mPlayerAnimation.flip(mFlip);
		mPlayerAnimation.load(RMI.getResource(Texture::UlfrIdle), Frames(6, 3), sf::milliseconds(1300), sf::seconds(7), true);
		mAnimationStyle = AnimationStyle::PlayerIdle;
	}
	else if (type == AnimationType::Movement && !mDestinationReached && (mVelocity.x < 0 && mVelocity.x > -0.3 || mVelocity.x > 0 && mVelocity.x < 0.3) && mVelocity.y < 0 && mAnimationStyle != AnimationStyle::Up)
	{
		mPlayerAnimation.flip(mFlip);
		mPlayerAnimation.load(RMI.getResource(Texture::UlfrWalkUp), Frames(5, 5), sf::milliseconds(1200), sf::seconds(0), true);
		mAnimationStyle = AnimationStyle::Up;
	}
	else if (type == AnimationType::Movement && !mDestinationReached && (mVelocity.x < 0 && mVelocity.x > -0.3 || mVelocity.x > 0 && mVelocity.x < 0.3) && mVelocity.y > 0 && mAnimationStyle != AnimationStyle::Down)
	{
		mPlayerAnimation.flip(mFlip);
		mPlayerAnimation.load(RMI.getResource(Texture::UlfrWalk), Frames(5, 5), sf::milliseconds(1200), sf::seconds(0), true);
		mAnimationStyle = AnimationStyle::Down;
	}
	else if (type == AnimationType::TalkToNpc && mAnimationStyle != AnimationStyle::PlayerTalk)
	{
		mPlayerAnimation.flip(mFlip);
		mPlayerAnimation.load(RMI.getResource(Texture::UlfrTalkToNpc), Frames(5, 2), sf::milliseconds(800), sf::Time::Zero, true);
		mAnimationStyle = AnimationStyle::PlayerTalk;
	}
	else if (type == AnimationType::TalkToPlayer && mAnimationStyle != AnimationStyle::PlayerMonolog)
	{
		setFlip(false);
		mPlayerAnimation.flip(mFlip);
		mPlayerAnimation.load(RMI.getResource(Texture::UlfrTalkToPlayer), Frames(4, 1), sf::milliseconds(600), sf::seconds(0), true);
		mAnimationStyle = AnimationStyle::PlayerMonolog;
	}
	else if (type == AnimationType::Pickup && mAnimationStyle != AnimationStyle::PlayerPickup)
	{
		mPlayerAnimation.flip(mFlip);
		mPlayerAnimation.load(RMI.getResource(Texture::UlfrPickup), Frames(5, 5), sf::milliseconds(1400), sf::seconds(0), false);
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
	mPlayerAnimation.flip(mFlip);
}

void Player::setFootsteps(Footsteps::ID footsteps)
{
	mFootsteps = footsteps;
}

void Player::UpdateAnimationStyle()
{
	mAnimationStyle = AnimationStyle::Update;
	setAnimationStyle(AnimationType::Idle);
}
