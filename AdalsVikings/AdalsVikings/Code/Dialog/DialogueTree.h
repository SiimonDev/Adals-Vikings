#pragma once
#include "pugixml.hpp"
#include "..\Logics\MouseState.h"
#include "..\Logics\IndexRenderer.h"
#include "..\Logics\ResourceManager.h"
#include <string>
#include <vector>

using namespace pugi;
class DialogueTree
{
public:
	DialogueTree();

	void load();
	void unload();
	void render(IndexRenderer &iRenderer);
	void update(sf::Time &frametime);

	void setDialogue(std::string filepath);
	void startDialogue();
	void setTextPosition(sf::Vector2f position);
	void enableDraw(bool value);
	void reloadConverstaion();
	void setTextColor(sf::Color color);
	void setEndConversation(bool value);
	void disableOption(int index);
	void enableOption(int index);
	void stopConversation();

	std::string &getText();
	std::string &getCharacter();
	std::string &getUseText();
	std::string &getLookText();
	bool getHasStopped();
	float &getTimer();
	bool &getActiveConversation();
	bool &getWait();
	bool &getEndConversation();
	bool &getFacing();
	bool &getFacePlayer();
	bool getIsOptionDisabled(int index);

	std::vector<sf::Text> &getOptions();
	std::vector<sf::RectangleShape> &getRectangle();
	sf::Text &getPrintText();

private:
	void find_FirstOptionContainer();
	void find_FirstOption();
	void find_AllOptions();
	void selectOption();
	void startConverstation();
	//Help functions
	std::string as_utf8(const char* str) { return str; }
	std::wstring as_wide(const wchar_t* str) { return str; }
	bool &wait(sf::Time &frametime);
	void disablePrevious();
	void enable();

	std::string mFilePath;
	sf::Text mPrintText;
	sf::Sprite mTextBackground;
	sf::RectangleShape mDialogueRectangle;
	std::vector<sf::RectangleShape> mRectangleVector;
	std::vector<sf::Text> mOptionsVector;
	std::string mName, mText, mUseText, mLookText, mEnable;
	float mTimer;
	bool mActiveConversation, mStart, mWait, mOptionSelected, mGoneDeep, 
		mIsTalking, mStopConversation, mDraw, mEndConversation, mFaceWay, mFacePlayer;

	xml_document mDialogue;
	xml_node mNode;
};

