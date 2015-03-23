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
#include "..\Logics\WindowState.h"


DialogueTree::DialogueTree(Font::ID fontID, Player &player)
	: mActiveConversation(false)
	, mPlayer(&player)
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
	, mFontID(fontID)
{
	mDialogueRectangle.setFillColor(sf::Color(0, 0, 0, 200));
	mDialogueRectangle.setOutlineColor(sf::Color(255, 255, 255, 200));

	mDialogueRectangle.setCornerPointCount(40);
	mDialogueRectangle.setCornersRadius(10);
	mDialogueRectangle.setOutlineThickness(3);

	mOptionsRectangle.setCornerPointCount(40);
	mOptionsRectangle.setCornersRadius(10);
	mOptionsRectangle.setOutlineThickness(3);
	mOptionsRectangle.setOutlineColor(sf::Color::White);
	mOptionsRectangle.setFillColor(sf::Color(0, 0, 0, 100));
	mOptionsRectangle.setPosition(100.f - 2, 705.f + 30);
	mPosition.x = 1920;
}
void DialogueTree::load(bool reset)
{
	std::cout << "Loading: " + mFilePath << std::endl;
	mDialogue.load_file(mFilePath.c_str());
	std::string copyFolder = "copy/";
	mPrintText.setFont(RMI.getResource(mFontID));
	if (mFilePath.find(copyFolder) == std::string::npos)
	{
		std::string copyStr = "_copy.xml";
		std::string segment = "";
		std::string container;

		std::transform(mFilePath.begin(), mFilePath.end(), mFilePath.begin(), ::tolower);

		container = mFilePath.substr(0, mFilePath.find("dialogue", 0));

		std::stringstream linestream;
		linestream << mFilePath;

		while (std::getline(linestream, segment, '/')) //splits the  line at ;
		{}
		mFilePath = container + copyFolder + segment;
		if (mFilePath.find(copyStr) == std::string::npos)
		{
			std::string mystr = mFilePath.substr(0, mFilePath.find(".", 0));
			std::string tempStr = mystr + "_copy.xml";
			mFilePath = tempStr;
		}
		if (reset)
			mDialogue.save_file(mFilePath.c_str());
		mDialogue.load_file(mFilePath.c_str());
	}
	getUseText();
	getLookText();
}
//OBS! OBS! Remember to add micro transactions OBS! OBS! 
void DialogueTree::unload()
{

}
//Praise the graphical people!!
void DialogueTree::render(IndexRenderer &iRenderer)
{
	/*for (int i = 0; i < mRectangleVector.size(); i++)
		iRenderer.addShape(mRectangleVector[i], 9999);*/

	if (mActiveConversation == true)
	{
		/* This will probably work... maby? */
		if (mPrintText.getPosition().x <= 5)
		{
			mDialogueRectangle.setPosition(5, mDialogueRectangle.getPosition().y);
			mPrintText.setPosition(mDialogueRectangle.getPosition().x + 15, mPrintText.getPosition().y);
		}
		else if (mDialogueRectangle.getPosition().x + (mDialogueRectangle.getSize().x) >= 1910)
		{
			mDialogueRectangle.setPosition(1910 - (mDialogueRectangle.getSize().x), mDialogueRectangle.getPosition().y);
			mPrintText.setPosition(mDialogueRectangle.getPosition().x + 10, mPrintText.getPosition().y);
		}
		/* ================================ */

		for (int i = 0; i < mOptionsVector.size(); i++)
			iRenderer.addText(mOptionsVector[i], 99999);

		if (!mOptionsVector.empty())
			iRenderer.addShape(mOptionsRectangle, 9999);

		if (mWait)
		{
			iRenderer.addText(mPrintText, 9999 + 1);
			if (mPrintText.getString() != "")
			{
				mDialogueRectangle.setSize(sf::Vector2f(mPrintText.getGlobalBounds().width + 10, mPrintText.getGlobalBounds().height + 10));
				mDialogueRectangle.setPosition(mPrintText.getGlobalBounds().left - 5, mPrintText.getGlobalBounds().top + (mDialogueRectangle.getSize().y) - 5);
				iRenderer.addShape(mDialogueRectangle, 9999);
			}
		}
	}
}
void DialogueTree::update(sf::Time &frameTime)
{
	if (MouseState::isClicked(sf::Mouse::Right))
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

		if (!mOptionsVector.empty())
		{
			float sizeX = 0;
			float sizeY = 0;
			for (int i = 0; i < mOptionsVector.size(); i++)
			{
				if (sizeX < mOptionsVector[i].getGlobalBounds().width)
				{
					sizeX = mOptionsVector[i].getGlobalBounds().width;
				}
				if (mPosition.x > mOptionsVector[i].getPosition().x)
					mPosition.x = mOptionsVector[i].getPosition().x;

				mPosition.y = mOptionsVector[i].getPosition().y;
				sizeY += mOptionsVector[i].getGlobalBounds().height;
				mSize.x = sizeX + 50;
				mSize.y = sizeY + 20;
			}
		}

		if (!mOptionsVector.empty())
		{

			mOptionsRectangle.setPosition(mPosition.x - 25, mPosition.y + mOptionsVector[mOptionsVector.size() - 1].getGlobalBounds().height + 15);
			mOptionsRectangle.setSize(mSize);

			if (mOptionsRectangle.getPosition().x <= 5)
			{
				mOptionsRectangle.setPosition(5, mOptionsRectangle.getPosition().y);
				for (int i = 0; i < mOptionsVector.size(); i++)
				{
					mOptionsVector[i].setPosition(mOptionsRectangle.getPosition().x + 25, mOptionsVector[i].getPosition().y);
					mRectangleVector[i].setPosition(mOptionsVector[i].getPosition().x, mRectangleVector[i].getPosition().y);
				}
			}
			else if (mOptionsRectangle.getPosition().x + (mOptionsRectangle.getGlobalBounds().width) >= 1915)
			{
				mOptionsRectangle.setPosition(1915 - (mOptionsRectangle.getGlobalBounds().width), mOptionsRectangle.getPosition().y);
				for (int i = 0; i < mOptionsVector.size(); i++)
				{
					mOptionsVector[i].setPosition(mOptionsRectangle.getPosition().x + 25, mOptionsVector[i].getPosition().y);
					mRectangleVector[i].setPosition(mOptionsVector[i].getPosition().x, mRectangleVector[i].getPosition().y);
				}
			}

			if (mOptionsRectangle.getPosition().y <= 5)
			{
				mOptionsRectangle.setPosition(mOptionsRectangle.getPosition().x, mOptionsRectangle.getPosition().y + 20);
				for (int i = 0; i < mOptionsVector.size(); i++)
				{
					mOptionsVector[i].setPosition(mOptionsVector[i].getPosition().x, mOptionsVector[i].getPosition().y + 20);
					mRectangleVector[i].setPosition(mRectangleVector[i].getPosition().x, mRectangleVector[i].getPosition().y + 20);
				}
			}
			else if (mOptionsRectangle.getPosition().y + (mOptionsRectangle.getGlobalBounds().height) >= 1075)
			{
				float difference = mOptionsRectangle.getPosition().y - 1065;
				mOptionsRectangle.setPosition(mOptionsRectangle.getPosition().x, mOptionsRectangle.getPosition().y - difference);
				for (int i = 0; i < mOptionsVector.size(); i++)
				{
					mOptionsVector[i].setPosition(mOptionsVector[i].getPosition().x, mOptionsVector[i].getPosition().y - difference);
					mRectangleVector[i].setPosition(mRectangleVector[i].getPosition().x, mRectangleVector[i].getPosition().y - difference);
				}
			}
		}
	}
}
void DialogueTree::setTextColor(sf::Color color)
{
	mDialogueRectangle.setOutlineColor(color);
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
		/*if ((as_utf8(mNode.name()) != "option_container"))
		{*/
			if (!mNode.attribute("disabled").as_bool() && as_utf8(mNode.name()) == "text")
			{
				mName = as_utf8(mNode.attribute("character").as_string());
				mPrintText.setCharacterSize(30);
				mPrintText.setCharacterSize(30);

				if (as_utf8(mNode.attribute("turned").as_string()) == "true")
					mFaceWay = true;
				else if (as_utf8(mNode.attribute("turned").as_string()) == "false")
					mFaceWay = false;
				if (as_utf8(mNode.attribute("turnedPlayer").as_string()) == "true")
					mFacePlayer = true;
				else if (as_utf8(mNode.attribute("turnedPlayer").as_string()) == "")
					mFacePlayer = false;

				std::string tmpStr = mNode.attribute("say").as_string();
				std::string tmpStr2 = mNode.attribute("say").as_string();
				mPrintText.setString(as_utf8(mNode.attribute("say").as_string()));

				if (tmpStr.size() >= 60)
				{
					int index = 0;
					int cnt = 0;
					for (int i = 0; i < tmpStr.size(); i++)
					{
						char c = tmpStr[i];
						if (isspace(tmpStr[i]))
							cnt++;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
					}
					if (cnt <= 8)
					{
						for (int i = 0; i < cnt - 2; i++)
							index = tmpStr.find_first_of(' ', index + 1);
						if (index != 0)
							index += 1;
					}
					else
					{
						for (int i = 0; i < cnt / 2 + 1; i++)
							index = tmpStr.find_first_of(' ', index + 1);
						if (index != 0)
							index += 1;
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

				if (mNode.attribute("default").as_bool() == false && as_utf8(mNode.name()) == "text")
				{
					mNode.attribute("disabled").set_value(true);
				}
			}
			else if (mNode.attribute("default").as_bool() == true && as_utf8(mNode.name()) == "text")
			{
				mNode.attribute("disabled").set_value(false);
			}
			else if (as_utf8(mNode.name()) == "stopConversation")
			{
				stopConversation();
				return;
			}
			else if ((as_utf8(mNode.name()) == "option_container"))
			{
				find_AllOptions();
				if (mOptionsVector.empty())
				{
					stopConversation();
					return;
				}
				mStart = true;
				return;
			}

			if (as_utf8(mNode.next_sibling().name()) != "")
			{
				mNode = mNode.next_sibling();
			}
			else
			{
				stopConversation();
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
			mPosition.x = 1920;
			sf::Text text;
			text.setString(mNode.attribute("choice_text").as_string());
			text.setFont(RMI.getResource(mFontID));
			text.setCharacterSize(30);

			text.setPosition(mPlayer->getPosition().x - 100, mPlayer->getPosition().y + 30 * cnt - 50);
			rectangle.setFillColor(sf::Color(0, 0, 0, 100));
			rectangle.setPosition(mPlayer->getPosition().x - 100, mPlayer->getPosition().y + 30 * cnt - 50);
			rectangle.setSize(sf::Vector2f(text.getGlobalBounds().width + 4, 30));

			mOptionsVector.push_back(text);
			mRectangleVector.push_back(rectangle);
			cnt++;
		}
		if (mNode.attribute("disabled").as_bool() != false || as_utf8(mNode.name()) == "option")
			mNode = mNode.next_sibling();

		if (as_utf8(mNode.name()) == "stopOption")
		{
			if (mOptionsVector.empty())
			{
				stopConversation();
				return;
			}
			break;
		}
	}
	mName = "";
}

void DialogueTree::reloadConverstaion()
{
	mDialogue.save_file(mFilePath.c_str());
	mDialogue.load_file(mFilePath.c_str());
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

				if (tmpStr.size() >= 30)
				{
					int index = 0;
					int cnt = 0;
					for (int i = 0; i < tmpStr.size(); i++)
					{
						char c = tmpStr[i];
						if (isspace(tmpStr[i]))
							cnt++;
					}
					if (cnt <= 4)
					{
						for (int i = 0; i < cnt - 2; i++)
							index = tmpStr.find_first_of(' ', index + 1);
						if (index != 0)
							index += 1;
					}
					else
					{
						for (int i = 0; i < cnt / 2 + 1; i++)
							index = tmpStr.find_first_of(' ', index + 1);
						if (index != 0)
							index += 1;
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
				/*mDialogue.save_file(mFilePath.c_str());
				mDialogue.load_file(mFilePath.c_str());*/
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
				/*mDialogue.save_file(mFilePath.c_str());
				mDialogue.load_file(mFilePath.c_str());*/
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

std::string DialogueTree::getText()
{
	std::string text = mPrintText.getString();
	return text;
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

	if (as_utf8(mNode.attribute("timer").as_string()) != "")
		mUseTimer = mNode.attribute("timer").as_float();
	else
		mUseTimer = 2;
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

	if (as_utf8(mNode.attribute("timer").as_string()) != "")
		mLookTimer = mNode.attribute("timer").as_float();
	else
		mLookTimer = 2;
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
		//mDialogue.save_file(mFilePath.c_str());
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
				//mDialogue.save_file(mFilePath.c_str());
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
	mDialogue.save_file(mFilePath.c_str());
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

float & DialogueTree::getLookTimer()
{
	return mLookTimer;
}

float & DialogueTree::getUseTimer()
{
	return mUseTimer;
}

//Notes makes code easier to read, not this one though