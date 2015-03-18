#include "PlayerMonologue.h"
#include "..\Logics\RoundedRectangleShape.h"

PlayerMonologue::PlayerMonologue()
{

}

PlayerMonologue &PlayerMonologue::getInstance()
{
	static PlayerMonologue instance;
	return instance;
}

void PlayerMonologue::setPosition(sf::Vector2f pos)
{
	mPosition = sf::Vector2f(pos.x - (mText.getGlobalBounds().width / 2), pos.y - (pos.y / 10));
}

void PlayerMonologue::setText(std::string text)
{
	mText.setString(text);
}

void PlayerMonologue::setOutlineColor(sf::Color &color)
{
	mTextRect.setOutlineColor(color);
}

void PlayerMonologue::load()
{
	RMI.loadResource(Font::Skranji_regular);
	mText.setFont(RMI.getResource(Font::Skranji_regular));

	mTextRect.setFillColor(sf::Color(0, 0, 0, 200));
	mTextRect.setOutlineColor(sf::Color(255, 255, 255, 200));

	mTextRect.setCornerPointCount(40);
	mTextRect.setCornersRadius(10);
	mTextRect.setOutlineThickness(3);
}

void PlayerMonologue::unload()
{
	RMI.unloadResource(Font::Skranji_regular);
}

void PlayerMonologue::displayDialog(Dialog &dialog)
{
	mCurrentDialog = dialog;
	std::string tmpStr = dialog.mDialog;
	std::string tmpStr2 = dialog.mDialog;

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
		setText(tmpStr2 + '\n' + tmpStr.substr(index));
	}
	else
	{
		setText(dialog.mDialog);
	}
	mTimePassed = sf::Time::Zero;
	mDisplay = true;
}

void PlayerMonologue::update(sf::Time &frameTime)
{
	if (mDisplay)
	{
		mTimePassed += frameTime;
		if (mTimePassed.asSeconds() >= mCurrentDialog.mTimer)
		{
			mTimePassed = sf::seconds(0);
			mDisplay = false;
		}

		mText.setPosition(mPosition);
		mTextRect.setSize(sf::Vector2f(mText.getGlobalBounds().width + 20, mText.getGlobalBounds().height + 16));
		mTextRect.setPosition(mPosition.x - 10, mPosition.y + (mTextRect.getSize().y));

		if (mTextRect.getPosition().x <= 5)
		{
			mTextRect.setPosition(5, mTextRect.getPosition().y);
			mText.setPosition(mTextRect.getPosition().x + 15, mText.getPosition().y);
		}
		else if (mTextRect.getPosition().x + (mTextRect.getSize().x) >= 1915)
		{
			mTextRect.setPosition(1915 - (mTextRect.getSize().x), mTextRect.getPosition().y);
			mText.setPosition(mTextRect.getPosition().x + 15, mText.getPosition().y);
		}
	}
}

void PlayerMonologue::render(IndexRenderer &iRenderer)
{
	if (mDisplay)
	{
		iRenderer.addText(mText, 9900000 + 1);
		iRenderer.addShape(mTextRect, 9900000);
	}
}

void PlayerMonologue::setDisplay(bool value)
{
	mDisplay = value;
}

bool & PlayerMonologue::getDisplay()
{
	return mDisplay;
}
