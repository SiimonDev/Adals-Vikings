#include "DialogWindow.h"

static sf::Time mTimePassed;
static sf::Text mText;
static sf::Vector2f mPosition;

static int mPadding;

static Dialog mCurrentDialog;

static bool mDisplay;

static sf::RectangleShape background;

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
void DialogWindow::setTextSize(int textSize)
{
	mText.setCharacterSize(textSize);
}
void DialogWindow::setTextStyle(sf::Text::Style style)
{
	mText.setStyle(style);
}
void DialogWindow::setTextColor(sf::Color color)
{
	mText.setColor(color);
}

void DialogWindow::setBackgroundSize(sf::Vector2f &size)
{
	background.setSize(sf::Vector2f(size.x + (mPadding * 2), size.y + (mPadding * 2)));
}

void DialogWindow::setBackgroundColor(sf::Color &color)
{
	background.setFillColor(color);
}

void DialogWindow::load()
{
	mPadding = 15;
	setPosition(sf::Vector2f(600, 700));
	setBackgroundSize(sf::Vector2f(700, 250));
	setBackgroundColor(sf::Color(0, 0, 0, 200));

	RMI.loadResource(Font::Font2);
	mText.setFont(RMI.getResource(Font::Font2));
}

void DialogWindow::unload()
{
	RMI.unloadResource(Font::Font2);
}

void DialogWindow::displayDialog(Dialog &dialog)
{
	mCurrentDialog = dialog;
	setText(dialog.mDialog);
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
	}
}

void DialogWindow::render(IndexRenderer &iRenderer)
{
	if (mDisplay)
	{
		mText.setPosition(sf::Vector2f(mPosition.x + mPadding, mPosition.y + mPadding));
		background.setPosition(mPosition);
		iRenderer.addText(mText, 100000);
		//iRenderer.addRectangle(background, 99999);
	}
}