#include "NPC.h"
#include "..\Dialog\DialogHandler.h"
#include <iostream>

Npc::Npc()
: mName("Hero")
, mPosition(sf::Vector2f(0, 0))
, mFlip(false)
{
}

void Npc::render(IndexRenderer &iRenderer)
{
	mNpcAnimation.getSprite().setOrigin(sf::Vector2f(mSize.x / 2, mSize.y));
	mNpcAnimation.setScaleFromHeight(mProportions.y * mScale.y);
	mNpcAnimation.setPosition(mPosition);
	mNpcAnimation.render(iRenderer);
}

void Npc::update(sf::Time &frametime)
{
	mNpcAnimation.animate(frametime);
}

void Npc::load()
{
	RMI.loadResource(mIdleTexture, mIdlePath);
	RMI.loadResource(mTalkTexture, mTalkPath);
	mNpcAnimation.flip(mFlip);
	mNpcAnimation.load(RMI.getResource(mIdleTexture), mIdleFrames, mIdleDuration, mIdleWaitTime, true);
	mSize.x = mNpcAnimation.getSpriteSize().x;
	mSize.y = mNpcAnimation.getSpriteSize().y;
	mNpcAnimation.setProportions(mProportions);

	float npcWith = float(mSize.x * mScale.x);
	float npcHeight = float(mSize.y * mScale.y);
	float xPos = mPosition.x - (npcWith / 2);
	float yPos = mPosition.y - ((npcHeight * 0.2f) / 2);
	mCollisionRect = sf::IntRect(xPos, yPos, npcWith, npcHeight * 0.2f);

	yPos = mPosition.y - (npcHeight * 1.2f);
	xPos = mPosition.x - ((npcWith * 1.5f) / 2);
	mIndexRect = sf::IntRect(xPos, yPos, npcWith * 1.5f, npcHeight * 1.2f);

	setAnimationStyle("Idle");
}

void Npc::unload()
{
	RMI.unloadResource(mIdleTexture);
	RMI.unloadResource(mTalkTexture);
}

bool Npc::getActiveConversation()
{
	return DialogHandler::getDialogue(mDialogue).getActiveConversation();
}

bool Npc::isInside(sf::Vector2i &pos)
{
	return
		(pos.x >= mPosition.x - mNpcAnimation.getSprite().getGlobalBounds().width / 2 &&
		pos.x <= mPosition.x + mNpcAnimation.getSprite().getGlobalBounds().width / 2 &&
		pos.y >= mPosition.y - mNpcAnimation.getSprite().getGlobalBounds().height &&
		pos.y <= mPosition.y);
}

int Npc::getIndex()
{
	return mNpcAnimation.getIndex();
}

std::string & Npc::getUseText()
{
	return DialogHandler::getDialogue(mDialogue).getUseText();
}

std::string & Npc::getLookText()
{
	return DialogHandler::getDialogue(mDialogue).getLookText();
}

void Npc::startConversation()
{
	DialogHandler::getDialogue(mDialogue).startDialogue();
}

void Npc::setName(std::string name)
{
	mName = name;
}
void Npc::setColor(sf::Color color)
{
	mColor = color;
}
void Npc::setIndex(int index)
{
	mNpcAnimation.setIndex(index);
}
void Npc::setInteractionPosition(sf::Vector2f &interPos)
{
	mInteractionPosition = interPos;
}
void Npc::setPosition(sf::Vector2f position)
{
	mPosition = position;
}
void Npc::setProportions(sf::Vector2f proportions)
{
	mProportions = proportions;
}
void Npc::setRightWay(bool value)
{
	mFlip = value;
}
void Npc::setIdleAnimation(Textures::ID id, std::string idlePath, sf::Vector2i &idleFrames, sf::Time duration, sf::Time idleDuration)
{
	mIdleTexture = id;
	mIdlePath = idlePath;
	mIdleFrames = idleFrames;
	mIdleDuration = duration;
	mIdleWaitTime = idleDuration;
}

void Npc::SetTalkAnimation(Textures::ID id, std::string talkPath, sf::Vector2i &talkFrames, sf::Time duration, sf::Time talkduration)
{
	mTalkTexture = id;
	mTalkPath = talkPath;
	mTalkFrames = talkFrames;
	mTalkDuration = duration;
	mTalkWaitTime = talkduration;
}
void Npc::setscale(sf::Vector2f scale)
{
	mScale = scale;
}
void Npc::setCollisionRect(sf::IntRect &rect)
{
	mCollisionRect = rect;
}
void Npc::setIndexRect(sf::IntRect &rect)
{
	mIndexRect = rect;
}

void Npc::setAnimationStyle(std::string type)
{
	if (type == "Npc" && mAnimation != AnimationState::Talking)
	{
		mNpcAnimation.flip(mFlip);
		mNpcAnimation.load(RMI.getResource(mTalkTexture), mTalkFrames, mTalkDuration, mTalkWaitTime, true);
		mSize.x = abs(mNpcAnimation.getSprite().getTextureRect().width);
		mSize.y = abs(mNpcAnimation.getSprite().getTextureRect().height);
		mAnimation = AnimationState::Talking;
	}
	else if (type == "Player" &&  mAnimation != AnimationState::PlayerTalking)
	{
		mNpcAnimation.flip(mFlip);
		mNpcAnimation.load(RMI.getResource(mIdleTexture), mIdleFrames, mIdleDuration, mIdleWaitTime, true);
		mSize.x = abs(mNpcAnimation.getSprite().getTextureRect().width);
		mSize.y = abs(mNpcAnimation.getSprite().getTextureRect().height);
		mAnimation = AnimationState::PlayerTalking;
	}
	else if (type == "Idle" && mAnimation != AnimationState::Idle)
	{
		mNpcAnimation.flip(mFlip);
		mNpcAnimation.load(RMI.getResource(mIdleTexture), mIdleFrames, mIdleDuration, mIdleWaitTime, true);
		mSize.x = abs(mNpcAnimation.getSprite().getTextureRect().width);
		mSize.y = abs(mNpcAnimation.getSprite().getTextureRect().height);
		mAnimation = AnimationState::Idle;
	}
}

std::string &Npc::getName()
{
	return mName;
}

sf::Vector2f &Npc::getPosition()
{
	return mPosition;
}
sf::Vector2f &Npc::getInteractionPosition()
{
	return mInteractionPosition;
}

Animation &Npc::getAnimation()
{
	return mNpcAnimation;
}
sf::IntRect &Npc::getCollisionRect()
{
	float npcWith = float(mSize.x * mScale.x);
	float npcHeight = float(mSize.y * mScale.y);
	float xPos = mPosition.x - (npcWith / 2);
	float yPos = mPosition.y - ((npcHeight * 0.2f) / 2);
	mCollisionRect = sf::IntRect(xPos, yPos, npcWith, npcHeight * 0.2f);

	return mCollisionRect;
}
sf::IntRect &Npc::getIndexRect()
{
	float npcWith = float(mSize.x * mScale.x);
	float npcHeight = float(mSize.y * mScale.y);
	float yPos = mPosition.y - (npcHeight * 1.2f);
	float xPos = mPosition.x - ((npcWith * 1.5f) / 2);
	mIndexRect = sf::IntRect(xPos, yPos, npcWith * 1.5f, npcHeight * 1.2f);

	return mIndexRect;
}
sf::Color &Npc::getColor()
{
	return mColor;
}
void Npc::setDialogue(std::string dialogue)
{
	mDialogue = dialogue;
}
std::string Npc::getDialogueString()
{
	std::string string = DialogHandler::getDialogue(mDialogue).getPrintText().getString();
	return string;
}

void Npc::UpdateAnimation()
{
	mAnimation = AnimationState::Update;
}
