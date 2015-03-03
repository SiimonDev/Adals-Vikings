#pragma once
#include "..\Logics\ResourceManager.h"
#include "..\Logics\IndexRenderer.h"
#include "..\Logics\Animation.h"
#include "..\Logics\RoundedRectangleShape.h"
using namespace pugi;

namespace AnimationState
{
	enum ID
	{
		Idle,
		Talking,
		PlayerTalking,
		Update
	};
}

class Npc
{
public:
	Npc(Font::ID id, Font::ID Oid);
	
	virtual void render(IndexRenderer &iRenderer);
	virtual void update(sf::Time &frametime);

	void load();
	void unload();
	void startConversation();

	void setName(std::string name);
	void setIdleAnimation(Texture::ID id, sf::Vector2i &idleFrames, sf::Time duration, sf::Time idleDuration);
	void SetTalkAnimation(Texture::ID id, sf::Vector2i &talkFrames, sf::Time duration, sf::Time idleDuration);
	void setPosition(sf::Vector2f position);
	void setFlip(bool value);
	void setscale(sf::Vector2f scale);
	void setProportions(sf::Vector2f proportions);
	void setIndex(int index);
	void setCollisionRect(sf::IntRect &rect);
	void setIndexRect(sf::IntRect &rect);
	void setAnimationStyle(std::string style);
	void setColor(sf::Color color);
	void setDialogue(std::string dialogue);
	void setDescription(std::string description);
	void enableDescription(bool active);
	void setInteractionPosition(sf::Vector2f &interactpos);
	void updateAnimationStyle();

	bool isInside(sf::Vector2i &pos);
	bool getActiveConversation();
	int getIndex();
	std::string &getUseText();
	std::string &getLookText();
	sf::Vector2f &getPosition();
	sf::Vector2f &getInteractionPosition();
	sf::IntRect &getCollisionRect();
	sf::IntRect &getIndexRect();
	std::string &getName();
	sf::Color &getColor();
	Animation &getAnimation();
	std::string getDialogueString();

private:
	Texture::ID mIdleTexture, mTalkTexture;
	sf::Vector2i mIdleFrames, mTalkFrames;
	sf::Time mIdleDuration, mIdleWaitTime, mTalkDuration, mTalkWaitTime;
	std::string mName, mDialogue;

	Animation mAnimation;
	sf::Vector2f mProportions;
	sf::Vector2f mPosition;
	sf::Vector2f mInteractionPosition;
	sf::Vector2f mScale;
	sf::IntRect mCollisionRect;
	sf::IntRect mIndexRect;
	sf::Text mDescription;
	sf::Text mDescriptionOutline;
	//sf::RectangleShape mTextRect;
	sf::RoundedRectangleShape mTextRect;

	AnimationState::ID mAnimationState;
	sf::Color mColor;

	bool mFlip, mUpdateAnimation;
	bool mDisplayDescription;
};