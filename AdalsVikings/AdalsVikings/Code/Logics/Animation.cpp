#include "Animation.h"
#include <iostream>
#include <math.h>

Animation::Animation()
	: mSprite()
	, mSpriteSize(sf::Vector2i(0, 0))
	, mFrames(0, 0)
	, mCurrentFrame(0)
	, mIdleFrame(1, 1)
	, mPadding(0)
	, mDuration(sf::Time::Zero)
	, mElapsedTime(sf::Time::Zero)
	, mIsRepeated(true)
	, mIsFlipped(false)
	, mIsIdle(false)
	, mIsFinished(false)
	, mStop(false)
{
}

Animation::Animation(sf::Sprite &sprite)
	: mSprite(sprite)
	, mSpriteSize(sf::Vector2i(0, 0))
	, mFrames(0, 0)
	, mCurrentFrame(0)
	, mIdleFrame(1, 1)
	, mPadding(0)
	, mDuration(sf::Time::Zero)
	, mElapsedTime(sf::Time::Zero)
	, mIsRepeated(true)
	, mIsFlipped(false)
	, mIsIdle(false)
	, mIsFinished(false)
	, mStop(false)
{
}

void Animation::load(sf::Texture &texture, sf::Vector2i frames, sf::Time duration, sf::Time idle, bool repeating)
{
	mStop = false;
	setSpriteSize(texture, frames);
	setDuration(duration);
	setRepeating(repeating);
	setIdleDuration(idle);
	mSprite.setTexture(texture);
	mProportions = sf::Vector2f(mSpriteSize);
	mIdleTime = mIdleDuration;
	mIsFinished = false;

	if (mIsFlipped)
		mSprite.setTextureRect(sf::IntRect(mSpriteSize.x, 0, -mSpriteSize.x, mSpriteSize.y));
	else
		mSprite.setTextureRect(sf::IntRect(0, 0, mSpriteSize.x, mSpriteSize.y));
}

void Animation::animate(sf::Time &frameTime)
{
	if (!idle(frameTime))
	{
		if (!mStop)
		{
			sf::Time timePerFrame = mDuration / float(mFrames.x * mFrames.y);
			mElapsedTime += frameTime;

			sf::Vector2i textureBounds(mSprite.getTexture()->getSize());
			sf::IntRect textureRect = sf::IntRect(mSprite.getTextureRect().left - mPadding, mSprite.getTextureRect().top - mPadding,
				mSprite.getTextureRect().width + (mPadding * 2), mSprite.getTextureRect().height + (mPadding * 2));

			if (mCurrentFrame == 0)
			{
				if (mIsFlipped)
				{
					mFlipOffset = mSpriteSize.x;
					textureRect = sf::IntRect(mSpriteSize.x, 0, -mSpriteSize.x, mSpriteSize.y);
				}
				else
				{
					mFlipOffset = 0;
					textureRect = sf::IntRect(0, 0, mSpriteSize.x, mSpriteSize.y);
				}
			}

			while (mElapsedTime >= timePerFrame)
			{
				mElapsedTime -= timePerFrame;

				textureRect.left += abs(textureRect.width);
				if (textureRect.left + abs(textureRect.width) > textureBounds.x + mFlipOffset)
				{
					textureRect.left = mFlipOffset;
					textureRect.top += textureRect.height;
				}

				mCurrentFrame = (mCurrentFrame + 1) % (mFrames.x * mFrames.y);
				if (mCurrentFrame == 0)
				{
					if (mIsFlipped)
						textureRect = sf::IntRect(mSpriteSize.x, 0, -mSpriteSize.x, mSpriteSize.y);
					else
						textureRect = sf::IntRect(0, 0, mSpriteSize.x, mSpriteSize.y);

					mIdleTime = mIdleDuration;

					if (idle(frameTime))
					{
						for (int i = 0; i < ((mIdleFrame.x - 1) * mIdleFrame.y); i++)
						{
							textureRect.left += abs(textureRect.width);
							if (textureRect.left + abs(textureRect.width) > textureBounds.x + mFlipOffset)
							{
								textureRect.left = mFlipOffset;
								textureRect.top += textureRect.height;
							}
						}
					}

					if (!mIsRepeated)
						mStop = true;
				}

				mSprite.setTextureRect(sf::IntRect(textureRect.left + mPadding, textureRect.top + mPadding, textureRect.width - (mPadding * 2), textureRect.height - (mPadding * 2)));
			}
		}
	}
}

void Animation::render(IndexRenderer &iRenderer)
{
	mSprite.setScale(mProportions);
	mSprite.setPosition(mPosition);
	iRenderer.addSprite(mSprite, mIndex);
}

void Animation::restart()
{
	mCurrentFrame = 0;
	mStop = false;
}
void Animation::flip(bool value)
{
	mIsFlipped = value;
}

void Animation::setSpriteSize(const sf::Texture &texture, sf::Vector2i &frames)
{
	mCurrentFrame = 0;
	mRows = frames.y;
	mColumns = frames.x;
	mFrames = frames;

	setTexture(texture);
	mSpriteSize = sf::Vector2i(texture.getSize().x / mFrames.x, texture.getSize().y / mFrames.y);

	if (mIsFlipped)
		mSprite.setTextureRect(sf::IntRect(mSpriteSize.x, 0, -mSpriteSize.x, mSpriteSize.y));
	else
		mSprite.setTextureRect(sf::IntRect(0, 0, mSpriteSize.x, mSpriteSize.y));

	setProportions(sf::Vector2f(mSpriteSize));
}
void Animation::setTexture(const sf::Texture &texture)
{
	mSprite.setTexture(texture);
}
void Animation::setPosition(sf::Vector2f &position)
{
	mPosition = position;
}
void Animation::setFrames(sf::Vector2i frames)
{
	mFrames = frames;
}
void Animation::setIndex(int index)
{
	mIndex = index;
}

void Animation::setRepeating(bool value)
{
	mIsRepeated = value;
}
void Animation::setDuration(sf::Time duration)
{
	mDuration = duration;
}
void Animation::setIdleDuration(sf::Time idleDuration)
{
	mIdleDuration = idleDuration;
}
void Animation::setIdleFrame(sf::Vector2i &frame)
{
	mIdleFrame = frame;
}
void Animation::setProportions(sf::Vector2f proportions)
{
	mProportions.x = ((proportions.x / abs(mSprite.getTextureRect().width)));
	mProportions.y = ((proportions.y / abs(mSprite.getTextureRect().height)));
}
void Animation::setScaleFromHeight(float height)
{
	mProportions.y = ((height / abs(mSprite.getTextureRect().height)));
	mProportions.x = mProportions.y;
}
void Animation::setPadding(float padding)
{
	mPadding = padding;
}

const sf::Vector2i &Animation::getSpriteSize()
{
	return sf::Vector2i(abs(mSprite.getTextureRect().width), abs(mSprite.getTextureRect().height));
}
sf::Sprite &Animation::getSprite()
{
	return mSprite;
}
sf::Vector2i &Animation::getFrames()
{
	return mFrames;
}
int Animation::getCurrentFrame()
{
	return mCurrentFrame;
}
int Animation::getIndex()
{
	return mIndex;
}
bool Animation::isRepeating()
{
	return mIsRepeated;
}

bool Animation::idle(sf::Time &frametime)
{
	if (mIdleTime.asSeconds() > 0.f){
		mIdleTime -= frametime;
		mIsIdle = true;
	}
	else{
		mIsIdle = false;
	}
	return mIsIdle;
}

bool &Animation::getFinished()
{
	return mIsFinished;
}
bool &Animation::getStopped()
{
	return mStop;
}
