#include "DialogueTree.h"
#include<cmath>
#include <cassert>
#include <ctype.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include "..\Logics\ResourceManager.h"
#include "..\Logics\KeyboardState.h"


DialogueTree::DialogueTree()
	: mActiveConversation(false)
	, mStart(false)
	, mWait(false)
	, mOptionSelected(false)
	, mGoneDeep(false)
	, mIsTalking(false)
	, mFaceWay(false)
	, mStopConversation(false)
	, mDraw(false)
	, mEndConversation(false)
	, mFacePlayer(false)
{
	mDialogueRectangle.setFillColor(sf::Color(0, 0, 0, 100));
}
void DialogueTree::load()
{
	mParser = mDialogue.load_file(mFilePath.c_str());
	std::string copyFolder = "copy/";
	if (mFilePath.find(copyFolder) == std::string::npos)
	{
		std::string copyStr = "_copy.xml";
		std::string segment = "";
		std::string container;
		container = mFilePath.substr(0, mFilePath.find("Dialogue", 0));
		std::stringstream linestream;
		linestream << mFilePath;

		while (std::getline(linestream, segment, '/')) //splits the  line at ;
		{
		}
		mFilePath = container + copyFolder + segment;
		if (mFilePath.find(copyStr) == std::string::npos)
		{
			std::string mystr = mFilePath.substr(0, mFilePath.find(".", 0));
			std::string tempStr = mystr + "_copy.xml";
			mFilePath = tempStr;
		}
		mDialogue.save_file(mFilePath.c_str());
		mParser = mDialogue.load_file(mFilePath.c_str());
	}
	getUseText();
	getLookText();
}
//Praise the graphical people!!
void DialogueTree::render(IndexRenderer &iRenderer)
{
	for (int i = 0; i < mRectangleVector.size(); i++)
		iRenderer.addRectangle(mRectangleVector[i], 99999);

	if (mActiveConversation == true)
	{
		for (int i = 0; i < mOptionsVector.size(); i++)
			iRenderer.addText(mOptionsVector[i], 99999);

		if (mWait)
		{
			iRenderer.addText(mPrintText, 99999);
			mDialogueRectangle.setSize(sf::Vector2f(mPrintText.getGlobalBounds().width + 4, mPrintText.getGlobalBounds().height + 10));
			mDialogueRectangle.setPosition(mPrintText.getGlobalBounds().left - 2, mPrintText.getGlobalBounds().top - 5);
			iRenderer.addRectangle(mDialogueRectangle, 9999);
		}
	}
}
void DialogueTree::update(sf::Time &frameTime)
{
	if (KeyboardState::isPressed(sf::Keyboard::Z))
	{
		mWait = false;
	}
	if (mActiveConversation == true)
	{
		if (mStart == false)
			startDialogue();

		wait(frameTime);
		selectOption();
		startConverstation();
	}
}
void DialogueTree::setTextColor(sf::Color color)
{
	mPrintText.setColor(color);
}
void DialogueTree::setDialogue(std::string filepath)
{
	mFilePath = filepath;
}
void DialogueTree::startDialogue()
{
	mActiveConversation = true;
	mStopConversation = false;

	if (as_utf8(mNode.name()) == "conversation")
		mNode = mNode.first_child();

	if (mWait == false && mStart == false)
	{
		if ((as_utf8(mNode.name()) != "option_container"))
		{
			if (!mNode.attribute("disabled").as_bool() && as_utf8(mNode.name()) == "text")
			{
				mName = as_utf8(mNode.attribute("character").as_string());
				mPrintText.setFont(RMI.getFont(Fonts::DialogWindow));
				mPrintText.setCharacterSize(30);

				if (as_utf8(mNode.attribute("turned").as_string()) == "true")
				{
					mFaceWay = true;
				}
				else if (as_utf8(mNode.attribute("turned").as_string()) == "false")
				{
					mFaceWay = false;
				}
				if (as_utf8(mNode.attribute("turnedPlayer").as_string()) == "true")
				{
					mFacePlayer = true;
				}
				else if (as_utf8(mNode.attribute("turnedPlayer").as_string()) == "")
				{
					mFacePlayer = false;
				}

				std::string tmpStr = mNode.attribute("say").as_string();
				std::string tmpStr2 = mNode.attribute("say").as_string();
				mPrintText.setString(as_utf8(mNode.attribute("say").as_string()));

				if (mPrintText.getGlobalBounds().left + mPrintText.getGlobalBounds().width > 1920)
				{
					int index = 0;
					int cnt = 0;
					for (int i = 0; i < tmpStr.size(); i++)
					{
						char c = tmpStr[i];
						if (isspace(tmpStr[i]))
							cnt++;
					}
					if (cnt <= 5)
					{
						for (int i = 0; i < cnt - 2; i++)
							index = tmpStr.find_first_of(' ', index + 1);
					}
					else
					{
						for (int i = 0; i < cnt / 2; i++)
							index = tmpStr.find_first_of(' ', index + 1);
					}
					size_t found = tmpStr2.find(tmpStr.substr(index));
					if (found != std::string::npos)
					{
						tmpStr2 = tmpStr2.substr(0, found);
					}
					mPrintText.setString(tmpStr2 + '\n' + tmpStr.substr(index));
				}
				mTimer = mNode.attribute("timer").as_float();
				mWait = true;
			}
			if (mNode.attribute("default").as_bool() == false && as_utf8(mNode.name()) == "text")
			{
				mNode.attribute("disabled").set_value(true);
				mDialogue.save_file(mFilePath.c_str());
			}
			if (mNode.attribute("default").as_bool() == true && as_utf8(mNode.name()) == "text")
			{
				mNode.attribute("disabled").set_value(false);
				mDialogue.save_file(mFilePath.c_str());
			}
			if (as_utf8(mNode.name()) == "stopConversation")
			{
				stopConversation();
				return;
			}
			if (as_utf8(mNode.next_sibling().name()) != "")
			{
				mNode = mNode.next_sibling();
			}
		}
		else if ((as_utf8(mNode.name()) == "option_container"))
		{
			find_AllOptions();
			mStart = true;
			return;
		}
	}
}
//MAKE GAMES!!!
void DialogueTree::find_FirstOptionContainer()
{
	if (as_utf8(mNode.name()) != "conversation")
		mNode = mDialogue.first_child();
	
	if (as_utf8(mNode.name()) == "conversation")
		mNode = mNode.first_child();
	
	while (mNode.attribute("disabled").as_bool() != false || as_utf8(mNode.name()) != "option_container")
	{
		if (as_utf8(mNode.next_sibling().name()) != "")
			mNode = mNode.next_sibling();
		
		else if (as_utf8(mNode.first_child().name()) != "")
			mNode = mNode.first_child();
		
		if (as_utf8(mNode.name()) == "stopConversation")
		{
			stopConversation();
			return;
		}
	}
}
void DialogueTree::find_FirstOption()
{
	find_FirstOptionContainer();
	mNode = mNode.first_child();
	while (mNode.attribute("disabled").as_bool() != false || as_utf8(mNode.name()) == "option")
	{
		if (mNode.attribute("disabled").as_bool() == false && as_utf8(mNode.name()) == "option")
			break;
		
		if (mNode.attribute("disabled").as_bool() != false || as_utf8(mNode.name()) == "option")
			mNode = mNode.next_sibling();
		
		if (as_utf8(mNode.name()) == "stopConversation")
		{
			stopConversation();
			return;
		}
	}
}
void DialogueTree::find_AllOptions()
{
	if (as_utf8(mNode.name()) != "option_container")
		find_FirstOptionContainer();
	if (as_utf8(mNode.name()) == "option_container")
		mNode = mNode.first_child();

	int cnt = 1;
	sf::RectangleShape rectangle;
	while (mNode.attribute("disabled").as_bool() != false || as_utf8(mNode.name()) == "option")
	{
		if (mNode.attribute("disabled").as_bool() == false && as_utf8(mNode.name()) == "option")
		{
			sf::Text text;
			text.setString(mNode.attribute("choice_text").as_string());
			text.setFont(RMI.getFont(Fonts::DialogWindow));
			text.setCharacterSize(30);
			text.setPosition(100.f, 700.f + 30 * cnt);
			rectangle.setFillColor(sf::Color(0, 0, 0, 100));
			rectangle.setPosition(100.f - 2, 705.f + 30 * cnt);
			rectangle.setSize(sf::Vector2f(text.getGlobalBounds().width + 4, 30));

			mOptionsVector.push_back(text);
			mRectangleVector.push_back(rectangle);
			cnt++;
		}
		if (mNode.attribute("disabled").as_bool() != false || as_utf8(mNode.name()) == "option")
			mNode = mNode.next_sibling();

		if (as_utf8(mNode.name()) == "stopOption")
		{
			if (mOptionsVector.size() == 0)
			{
				stopConversation();
			}
			break;
		}
	}
	mName = "";
}

void DialogueTree::reloadConverstaion()
{
	mParser = mDialogue.load_file(mFilePath.c_str());
	mNode = mDialogue.first_child();
}
void DialogueTree::selectOption()
{
	for (int i = 0; i < mRectangleVector.size(); i++)
	{
		if (MouseState::getMousePosition().x < mRectangleVector[i].getGlobalBounds().left + mRectangleVector[i].getGlobalBounds().width
			&& MouseState::getMousePosition().x > mRectangleVector[i].getGlobalBounds().left
			&& MouseState::getMousePosition().y > mRectangleVector[i].getGlobalBounds().top
			&& MouseState::getMousePosition().y < mRectangleVector[i].getGlobalBounds().top + mRectangleVector[i].getGlobalBounds().height)
		{
			mOptionsVector[i].setColor(sf::Color::Red);
			if (MouseState::isReleased(sf::Mouse::Left))
			{
				mOptionSelected = true;

				if (as_utf8(mNode.name()) == "stopOption")
					mNode = mNode.parent();

				if (as_utf8(mNode.name()) == "option_container")
					mNode = mNode.first_child();

				while (mNode.attribute("disabled").as_bool() != false || mOptionsVector[i].getString() != mNode.attribute("choice_text").as_string())
				{
					if (mNode.attribute("disabled").as_bool() == false && mOptionsVector[i].getString() == mNode.attribute("choice_text").as_string() && as_utf8(mNode.name()) == "option")
					{
						disablePrevious();
						mNode = mNode.first_child();
					}
					if (mOptionsVector[i].getString() != mNode.attribute("choice_text").as_string())
						mNode = mNode.next_sibling();

					if (as_utf8(mNode.name()) == "stopConversation")
					{
						stopConversation();
						return;
					}
				}
				if (mNode.attribute("disabled").as_bool() == false && mOptionsVector[i].getString() == mNode.attribute("choice_text").as_string() && as_utf8(mNode.name()) == "option")
				{
					disablePrevious();
					mNode = mNode.first_child();
				}
			}
		}
		else
		{
			mOptionsVector[i].setColor(sf::Color::White);
		}
	}
}
//there should be more for-loops!!
void DialogueTree::startConverstation()
{
	if (mOptionSelected == true)
	{
		mRectangleVector.clear();
		mOptionsVector.clear();
		if (mWait == false)
		{
			if (as_utf8(mNode.name()) == "text")
			{
				if (mNode.attribute("enable").as_string() != "")
					mEnable = as_utf8(mNode.attribute("enable").as_string());

				mName = mNode.attribute("character").as_string();
				disablePrevious();
				mTimer = mNode.attribute("timer").as_float();
				mPrintText.setFont(RMI.getFont(Fonts::ActionWheelDescription));
				mPrintText.setCharacterSize(30);
				if (as_utf8(mNode.attribute("turned").as_string()) == "true")
				{
					mFaceWay = true;
				}
				else if (as_utf8(mNode.attribute("turned").as_string()) == "false")
				{
					mFaceWay = false;
				}
				if (as_utf8(mNode.attribute("turnedPlayer").as_string()) == "true")
				{
					mFacePlayer = true;
				}
				else if (as_utf8(mNode.attribute("turnedPlayer").as_string()) == "false" || as_utf8(mNode.attribute("turnedPlayer").as_string()) == "")
				{
					mFacePlayer = false;
				}
				std::string tmpStr = mNode.attribute("say").as_string();
				std::string tmpStr2 = mNode.attribute("say").as_string();
				mPrintText.setString(as_utf8(mNode.attribute("say").as_string()));
				if (mPrintText.getGlobalBounds().left + mPrintText.getGlobalBounds().width > 1920)
				{
					int index = 0;
					int cnt = 0;
					for (int i = 0; i < tmpStr.size(); i++)
					{
						char c = tmpStr[i];
						if (isspace(tmpStr[i]))
							cnt++;
					}
					if (cnt <= 5)
					{
						for (int i = 0; i < cnt - 2; i++)
							index = tmpStr.find_first_of(' ', index + 1);
					}
					else
					{
						for (int i = 0; i < cnt / 2; i++)
							index = tmpStr.find_first_of(' ', index + 1);
					}
					size_t found = tmpStr2.find(tmpStr.substr(index));
					if (found != std::string::npos)
					{
						tmpStr2 = tmpStr2.substr(0, found);
					}
					mPrintText.setString(tmpStr2 + '\n' + tmpStr.substr(index));
				}
				mWait = true;
				if (as_utf8(mNode.next_sibling().name()) == "text" || as_utf8(mNode.next_sibling().name()) == "gotoBaseContainer"
					|| as_utf8(mNode.next_sibling().name()) == "gotoContainer" || as_utf8(mNode.next_sibling().name()) == "option_container" || as_utf8(mNode.next_sibling().name()) == "stopConversation")
				{
					mNode = mNode.next_sibling();
				}
			}
			else if (as_utf8(mNode.name()) == "gotoBaseContainer")
			{
				find_FirstOptionContainer();
				enable();
				find_AllOptions();
				mOptionSelected = false;
			}
			else if (as_utf8(mNode.name()) == "gotoContainer")
			{
				while (as_utf8(mNode.name()) != "option_container")
					mNode = mNode.parent();

				enable();
				find_AllOptions();
				mOptionSelected = false;
			}
			else if (as_utf8(mNode.name()) == "option_container")
			{
				enable();
				find_AllOptions();
				mOptionSelected = false;
			}
			else if (as_utf8(mNode.name()) == "stopConversation")
			{
				stopConversation();
				return;
			}
		}
	}
}
//maybe add a gun shot function?!?!?

bool &DialogueTree::wait(sf::Time &frameTime)
{
	if (mWait)
	{
		mTimer -= frameTime.asSeconds();
		if (mTimer <= 0)
		{
			mTimer = 0;
			mWait = false;
		}
	}
	return mWait;

}
void DialogueTree::disableOption(int index)
{
	if (as_utf8(mNode.name()) != "option_container")
		find_FirstOptionContainer();
	
	if (as_utf8(mNode.name()) == "option_container")
		mNode = mNode.first_child();

	int cnt = 1;
	while (mNode.attribute("disabled").as_bool() != false || as_utf8(mNode.name()) == "option")
	{
		if (as_utf8(mNode.name()) == "option")
		{
			if (cnt == index)
			{
				mNode.attribute("disabled").set_value(true);
				mDialogue.save_file(mFilePath.c_str());
				mParser = mDialogue.load_file(mFilePath.c_str());
				mNode = mDialogue.first_child();
				mStart = false;
				return;
			}
			cnt++;
			mNode = mNode.next_sibling();
		}
	}
	mNode = mDialogue.first_child();
}
void DialogueTree::enableOption(int index)
{
	if (as_utf8(mNode.name()) != "option_container")
		find_FirstOptionContainer();

	if (as_utf8(mNode.name()) == "option_container")
		mNode = mNode.first_child();

	int cnt = 1;
	while (mNode.attribute("disabled").as_bool() != false || as_utf8(mNode.name()) == "option")
	{
		if (as_utf8(mNode.name()) == "option")
		{
			if (cnt == index)
			{
				mNode.attribute("disabled").set_value(false);
				mDialogue.save_file(mFilePath.c_str());
				mParser = mDialogue.load_file(mFilePath.c_str());
				mNode = mDialogue.first_child();
				mStart = false;
				return;
			}
			cnt++;
			mNode = mNode.next_sibling();
		}
	}
	mNode = mDialogue.first_child();
}

std::string &DialogueTree::getText()
{
	return mText;
}
std::string &DialogueTree::getCharacter()
{
	return mName;
}
float &DialogueTree::getTimer()
{
	return mTimer;
}
std::string &DialogueTree::getUseText()
{
	mNode = mDialogue.first_child();
	assert(as_utf8(mNode.name()) == "conversation");
	if (as_utf8(mNode.name()) == "conversation")
		mNode = mNode.first_child();
	
	while (as_utf8(mNode.name()) != "useText")
		mNode = mNode.next_sibling();

	mUseText = as_utf8(mNode.attribute("useText").as_string());
	return mUseText;
}
//^use dat text!!
std::string &DialogueTree::getLookText()
{
	mNode = mDialogue.first_child();
	assert(as_utf8(mNode.name()) == "conversation");
	if (as_utf8(mNode.name()) == "conversation")
		mNode = mNode.first_child();
	
	while (as_utf8(mNode.name()) != "lookText")
		mNode = mNode.next_sibling();

	mLookText = as_utf8(mNode.attribute("lookText").as_string());
	return mLookText;
}
bool DialogueTree::getHasStopped()
{
	return mStopConversation;
}
bool DialogueTree::getIsOptionDisabled(int index)
{
	xml_node tmpNode;
	if (as_utf8(tmpNode.name()) != "option_container")
	{
		if (as_utf8(tmpNode.name()) != "conversation")
			tmpNode = mDialogue.first_child();

		if (as_utf8(tmpNode.name()) == "conversation")
			tmpNode = tmpNode.first_child();

		while (tmpNode.attribute("disabled").as_bool() != false || as_utf8(tmpNode.name()) != "option_container")
		{
			if (as_utf8(tmpNode.next_sibling().name()) != "")
				tmpNode = tmpNode.next_sibling();

			else if (as_utf8(tmpNode.first_child().name()) != "")
				tmpNode = tmpNode.first_child();
		}
	}

	if (as_utf8(tmpNode.name()) == "option_container")
		tmpNode = tmpNode.first_child();

	int cnt = 1;
	while (tmpNode.attribute("disabled").as_bool() != false || as_utf8(tmpNode.name()) == "option")
	{
		if (as_utf8(tmpNode.name()) == "option")
		{
			if (cnt == index)
			{
				return tmpNode.attribute("disabled").as_bool();
			}
			cnt++;
			tmpNode = tmpNode.next_sibling();
		}
		if (as_utf8(tmpNode.name()) == "stopOption")
			stopConversation();
	}
	return false;
}
std::vector<sf::Text> &DialogueTree::getOptions()
{
	return mOptionsVector;
}
std::vector<sf::RectangleShape> &DialogueTree::getRectangle()
{
	return mRectangleVector;
}

void DialogueTree::disablePrevious()
{
	if (mNode.attribute("disablePrevious").as_bool() == true)
	{
		mNode.parent().attribute("disabled").set_value(true);
		mDialogue.save_file(mFilePath.c_str());
	}
}
//make it first person!!

void DialogueTree::enable()
{
	if (mEnable != "")
	{
		xml_node node = mNode;
		if (as_utf8(mNode.name()) == "option")
			node = mNode.parent();
		
		else if (as_utf8(node.name()) == "option_container")
			mNode = mNode.first_child();
		
		while (mNode.attribute("choice_text").as_string() != mEnable || mEnable != "")
		{
			if (as_utf8(mNode.attribute("choice_text").as_string()) == mEnable)
			{
				mNode.attribute("disabled").set_value(false);
				mDialogue.save_file(mFilePath.c_str());
				mEnable = "";
				mNode = node;
			}
			if (as_utf8(mNode.next_sibling().name()) != "")
				mNode = mNode.next_sibling();
		}
	}
}
void DialogueTree::enableDraw(bool value)
{
	mDraw = value;
}
//OBS! OBS! Remember to add micro transactions OBS! OBS! 
void DialogueTree::unload()
{

}

bool & DialogueTree::getActiveConversation()
{
	return mActiveConversation;
}
bool &DialogueTree::getEndConversation()
{
	return mEndConversation;
}

void DialogueTree::stopConversation()
{
	mActiveConversation = false;
	mOptionsVector.clear();
	mRectangleVector.clear();
	mWait = false;
	mPrintText.setString("");
	mStart = false;
	mOptionSelected = false;
	setEndConversation(true);
	mStopConversation = true;
	mNode = mDialogue.first_child();
}

bool & DialogueTree::getWait()
{
	return mWait;
}

void DialogueTree::setTextPosition(sf::Vector2f position)
{
	std::string string = mPrintText.getString();
	mPrintText.setPosition(position.x - mPrintText.getGlobalBounds().width / 2, position.y - position.y / 10);
}
void DialogueTree::setEndConversation(bool value)
{
	mEndConversation = value;
}
sf::Text &DialogueTree::getPrintText()
{
	return mPrintText;
}

bool &DialogueTree::getFacing()
{
	return mFaceWay;
}

bool & DialogueTree::getFacePlayer()
{
	return mFacePlayer;
}

//Notes makes code easier to read, not this one though