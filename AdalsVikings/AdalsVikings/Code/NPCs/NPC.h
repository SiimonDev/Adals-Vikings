#pragma once
#include "..\Logics\ResourceManager.h"
#include "..\Logics\IndexRenderer.h"
#include "..\Logics\Animation.h"
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
	Npc();
	
	virtual void render(IndexRenderer &iRenderer);
	virtual void update(sf::Time &frametime);

	void load();
	void unload();
	void startConversation();

	void setName(std::string name);
	void setIdleAnimation(Textures::ID id, sf::Vector2i &idleFrames, sf::Time duration, sf::Time idleDuration);
	void SetTalkAnimation(Textures::ID id, sf::Vector2i &talkFrames, sf::Time duration, sf::Time idleDuration);
	void setPosition(sf::Vector2f position);
	void setRightWay(bool value);
	void setscale(sf::Vector2f scale);
	void setProportions(sf::Vector2f proportions);
	void setIndex(int index);
	void setCollisionRect(sf::IntRect &rect);
	void setIndexRect(sf::IntRect &rect);
	void setAnimationStyle(std::string style);
	void setColor(sf::Color color);
	void setDialogue(std::string dialogue);
	void setInteractionPosition(sf::Vector2f &interactpos);
	void UpdateAnimation();

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
	Textures::ID mIdleTexture, mTalkTexture;
	sf::Vector2i mIdleFrames, mTalkFrames;
	sf::Time mIdleDuration, mIdleWaitTime, mTalkDuration, mTalkWaitTime;
	std::string mName, mDialogue;

	Animation mNpcAnimation;
	sf::Vector2f mProportions;
	sf::Vector2f mPosition;
	sf::Vector2f mInteractionPosition;
	sf::Vector2f mScale;
	sf::Vector2i mSize;
	sf::IntRect mCollisionRect;
	sf::IntRect mIndexRect;

	AnimationState::ID mAnimation;
	sf::Color mColor;

	bool mFlip, mUpdateAnimation;
};

