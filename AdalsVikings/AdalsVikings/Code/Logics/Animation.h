#pragma once
#include <SFML\Graphics.hpp>
#include "IndexRenderer.h"

#define Frames sf::Vector2i

class Animation
{
public:
	Animation();
	Animation(sf::Sprite &sprite);

	void load(sf::Texture&, sf::Vector2i frames, sf::Time duration, sf::Time idle, bool repeating);
	void animate(sf::Time &frameTime);
	void render(IndexRenderer &iRenderer);

	void restart();
	void flip(bool value);

	void setSpriteSize(const sf::Texture &texture, sf::Vector2i &frames);
	void setTexture(const sf::Texture &texture);
	void setPosition(sf::Vector2f &position);
	void setFrames(sf::Vector2i frames);
	void setIndex(int index);
	
	void setRepeating(bool value);
	void setDuration(sf::Time duration);
	void setIdleDuration(sf::Time idleDuration);
	void setIdleFrame(sf::Vector2i &frame);
	void setProportions(sf::Vector2f proportions);
	void setScaleFromHeight(float height);
	void setPadding(float padding);

	const sf::Vector2i &getSpriteSize();
	sf::Sprite &getSprite();
	sf::Vector2i &getFrames();
	bool isRepeating();
	bool &getFinished();
	bool &getStopped();

private:
	bool idle(sf::Time &frametime);

	sf::Sprite mSprite;
	sf::Vector2i mFrames;
	sf::Vector2i mSpriteSize;
	sf::Vector2i mIdleFrame;
	sf::Vector2f mProportions;
	sf::Vector2f mPosition;

	sf::Time mDuration;
	sf::Time mIdleDuration, mIdleTime;
	sf::Time mElapsedTime;
	
	int mCurrentFrame;
	int mRows;
	int mColumns;
	int mIndex;
	
	float mPadding;
	float mFlipOffset;

	bool mIsRepeated;
	bool mIsFlipped;
	bool mIsIdle;
	bool mIsFinished;
	bool mStop;
};
