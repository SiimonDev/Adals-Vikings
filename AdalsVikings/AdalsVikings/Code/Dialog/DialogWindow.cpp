#include "DialogWindow.h"
#include "..\Logics\RoundedRectangleShape.h"

static sf::Time mTimePassed;
static sf::Text mText;
static sf::Vector2f mPosition;

static Dialog mCurrentDialog;

static bool mDisplay;

static sf::RoundedRectangleShape mTextRect;

DialogWindow::DialogWindow()
{

}

void DialogWindow::setPosition(sf::Vector2f &pos)
{
	mPosition = sf::Vector2f(pos.x - mText.getGlobalBounds().width / 2, pos.y - pos.y / 10);
}
void DialogWindow::setFont(Font::ID id)
{
	mText.setFont(RMI.getResource(id));
}
void DialogWindow::setText(std::string text)
{
	mText.setString(text);
}

void DialogWindow::setOutlineColor(sf::Color &color)
{
	mTextRect.setOutlineColor(color);
}

void DialogWindow::load()
{
	RMI.loadResource(Font::Skranji_regular);
	mText.setFont(RMI.getResource(Font::Skranji_regular));

	mTextRect.setFillColor(sf::Color(0, 0, 0, 200));
	mTextRect.setOutlineColor(sf::Color(255, 255, 255, 200));

	mTextRect.setCornerPointCount(40);
	mTextRect.setCornersRadius(10);
	mTextRect.setOutlineThickness(3);
}

void DialogWindow::unload()
{
	RMI.unloadResource(Font::Skranji_regular);
}

void DialogWindow::displayDialog(Dialog &dialog)
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

void DialogWindow::update(sf::Time &time)
{
	if (mDisplay)
	{
		mTimePassed += time;
		if (mTimePassed.asSeconds() >= mCurrentDialog.mTimer)
		{
			mTimePassed = sf::Time::Zero;
			mDisplay = false;
		}

		mText.setPosition(mPosition);
		mTextRect.setSize(sf::Vector2f(mText.getGlobalBounds().width + 20, mText.getGlobalBounds().height + 16));
		mTextRect.setPosition(mPosition.x - 10, mPosition.y + (mTextRect.getSize().y));
	}
}

void DialogWindow::render(IndexRenderer &iRenderer)
{
	if (mDisplay)
	{
		iRenderer.addText(mText, 99999 + 1);
		iRenderer.addShape(mTextRect, 99999);
	}
}