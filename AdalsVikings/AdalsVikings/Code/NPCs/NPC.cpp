#include "NPC.h"
#include "..\Dialog\DialogHandler.h"
#include "..\Logics\WindowState.h"
#include <iostream>

Npc::Npc(Font::ID id, Font::ID Oid)
: mName("Hero")
, mPosition(0, 0)
, mScale(0, 0)
, mFlip(false)
, mDisplayDescription(false)
{
	mDescription.setFont(RMI.getResource(id));
	mDescriptionOutline.setFont(RMI.getResource(Oid));
	mDescriptionOutline.setColor(sf::Color(0, 0, 0, 255));

	mTextRect.setFillColor(sf::Color(0, 0, 0, 200));
	mTextRect.setOutlineColor(sf::Color(255, 0, 0, 220));
	mTextRect.setOutlineThickness(5);
	mTextRect.setCornersRadius(5);
}

void Npc::render(IndexRenderer &iRenderer)
{
	mAnimation.getSprite().setOrigin(sf::Vector2f(mAnimation.getSpriteSize().x / 2, mAnimation.getSpriteSize().y));
	mAnimation.setScaleFromHeight(mProportions.y * mScale.y);
	mAnimation.setPosition(mPosition);
	mAnimation.render(iRenderer);

	if (mDisplayDescription)
	{
		//iRenderer.addShape(mTextRect, mAnimation.getIndex() + 1);
		iRenderer.addText(mDescription, mAnimation.getIndex() + 2);
		iRenderer.addText(mDescriptionOutline, mAnimation.getIndex() + 3);
		CurrentWindow.draw(mTextRect);
	}
}

void Npc::update(sf::Time &frametime)
{
	mAnimation.animate(frametime);

	if (mDisplayDescription)
	{
		mDescription.setPosition(sf::Vector2f(mPosition.x - (mDescription.getGlobalBounds().width / 2),
			mPosition.y - (mAnimation.getSpriteSize().y * mScale.y) - (mDescription.getGlobalBounds().height)));
		mDescriptionOutline.setPosition(mDescription.getPosition());

		mTextRect.setSize(sf::Vector2f(mDescription.getGlobalBounds().width + 10, mDescription.getGlobalBounds().height + 10));
		mTextRect.setPosition(sf::Vector2f(mPosition.x - (mTextRect.getGlobalBounds().width / 2),
			mPosition.y - (mTextRect.getGlobalBounds().height / 2) - (mAnimation.getSpriteSize().y * mScale.y)));
	}
}

void Npc::load()
{
	RMI.loadResource(mIdleTexture);
	RMI.loadResource(mTalkTexture);
	mAnimation.flip(mFlip);
	mAnimation.load(RMI.getResource(mIdleTexture), mIdleFrames, mIdleDuration, mIdleWaitTime, true);
	mAnimation.setProportions(mProportions);

	float npcWith = float(mAnimation.getSpriteSize().x * mScale.x);
	float npcHeight = float(mAnimation.getSpriteSize().y * mScale.y);
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
		(pos.x >= mPosition.x - ((mAnimation.getSpriteSize().x / 2) * mScale.x) &&
		pos.x <= mPosition.x + ((mAnimation.getSpriteSize().x / 2) * mScale.x) &&
		pos.y >= mPosition.y - (mAnimation.getSpriteSize().y * mScale.y) &&
		pos.y <= mPosition.y);
}

int Npc::getIndex()
{
	return mAnimation.getIndex();
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
	mAnimation.setIndex(index);
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
void Npc::setFlip(bool value)
{
	mFlip = value;
}
void Npc::setIdleAnimation(Texture::ID id, sf::Vector2i &idleFrames, sf::Time duration, sf::Time idleDuration)
{
	mIdleTexture = id;
	mIdleFrames = idleFrames;
	mIdleDuration = duration;
	mIdleWaitTime = idleDuration;
}

void Npc::SetTalkAnimation(Texture::ID id, sf::Vector2i &talkFrames, sf::Time duration, sf::Time talkduration)
{
	mTalkTexture = id;
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
	if (type == "Npc" && mAnimationState != AnimationState::Talking)
	{
		mAnimation.flip(mFlip);
		mAnimation.load(RMI.getResource(mTalkTexture), mTalkFrames, mTalkDuration, mTalkWaitTime, true);
		mAnimationState = AnimationState::Talking;
	}
	else if (type == "Player" &&  mAnimationState != AnimationState::PlayerTalking)
	{
		mAnimation.flip(mFlip);
		mAnimation.load(RMI.getResource(mIdleTexture), mIdleFrames, mIdleDuration, mIdleWaitTime, true);
		mAnimationState = AnimationState::PlayerTalking;
	}
	else if (type == "Idle" && mAnimationState != AnimationState::Idle)
	{
		mAnimation.flip(mFlip);
		mAnimation.load(RMI.getResource(mIdleTexture), mIdleFrames, mIdleDuration, mIdleWaitTime, true);
		mAnimationState = AnimationState::Idle;
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
	return mAnimation;
}
sf::IntRect &Npc::getCollisionRect()
{
	float npcWith = float(mAnimation.getSpriteSize().x * mScale.x);
	float npcHeight = float(mAnimation.getSpriteSize().y * mScale.y);
	float xPos = mPosition.x - (npcWith / 2);
	float yPos = mPosition.y - ((npcHeight * 0.2f) / 2);
	mCollisionRect = sf::IntRect(xPos, yPos, npcWith, npcHeight * 0.2f);

	return mCollisionRect;
}
sf::IntRect &Npc::getIndexRect()
{
	float npcWith = float(mAnimation.getSpriteSize().x * mScale.x);
	float npcHeight = float(mAnimation.getSpriteSize().y * mScale.y);
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
void Npc::setDescription(std::string description)
{
	mDescription.setString(description);
	mDescriptionOutline.setString(description);
}
void Npc::enableDescription(bool active)
{
	mDisplayDescription = active;
}
std::string Npc::getDialogueString()
{
	std::string string = DialogHandler::getDialogue(mDialogue).getPrintText().getString();
	return string;
}

void Npc::updateAnimationStyle()
{
	mAnimationState = AnimationState::Update;
	setAnimationStyle("Idle");
}
