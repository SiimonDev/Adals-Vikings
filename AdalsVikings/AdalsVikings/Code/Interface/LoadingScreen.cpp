#include "LoadingScreen.h"
#include "..\Logics\MouseState.h"
#include "..\Logics\KeyboardState.h"
#include "..\Logics\ResourceManager.h"
#include <iostream>
#include "..\Levels\LevelManager.h"

LoadingScreen::LoadingScreen()
: mIsDone(false)
, mStart(false)
{
	RMI.load(Fonts::DialogWindow, "assets/fonts/font1.ttf");
	
}
LoadingScreen & LoadingScreen::getInstance()
{
	static LoadingScreen instance;
	return instance;
}
void LoadingScreen::render(IndexRenderer &iRenderer)
{
	mLoadingText.setFont(RMI.getFont(Fonts::DialogWindow));
	mLoadingText.setString("Loading Resources");
	mLoadingText.setPosition(1920 / 2.f, 1080 / 2.f + 50.f);
	iRenderer.addText(mLoadingText, 99999);
}

bool LoadingScreen::update(sf::Time)
{
	// Update the progress bar from the remote task or finish it
	if (mLoadingTask.isFinished())
	{
		mIsDone = true;
		return true;
	}
	else
	{
		mIsDone = false;
		return false;
	}
}

bool LoadingScreen::handleEvent(const sf::Event& event)
{
	return true;
}

bool &LoadingScreen::getIsDone()
{
	return mIsDone;
}

bool &LoadingScreen::getIsStarted()
{
	return mStart;
}

void LoadingScreen::initialize()
{
}

void LoadingScreen::setDone(bool value)
{
	mIsDone = value;

}

void LoadingScreen::setStarted(bool value)
{
	mStart = value;
}

void LoadingScreen::startLoading(std::string task)
{
	mStart = true;
	mLoadingTask.execute(task);
}
