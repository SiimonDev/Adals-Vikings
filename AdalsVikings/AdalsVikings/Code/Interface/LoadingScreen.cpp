#include "LoadingScreen.h"
#include "..\Logics\MouseState.h"
#include "..\Logics\KeyboardState.h"
#include "..\Logics\ResourceManager.h"
#include "..\Levels\LevelManager.h"
#include <iostream>

LoadingScreen::LoadingScreen()
: mIsDone(false)
 ,mStart(false)
{
	mFont.loadFromFile("Assets/fonts/font1.ttf");
}

LoadingScreen & LoadingScreen::getInstance()
{
	static LoadingScreen* instance;

	if (instance == NULL)
		instance = new LoadingScreen();

	return *instance;
}

void LoadingScreen::render(IndexRenderer &iRenderer)
{
	mLoadingText.setFont(mFont);
	mLoadingText.setString("Loading Resources");
	mLoadingText.setPosition(1920 / 2.f, 1080 / 2.f + 50.f);
	iRenderer.addText(mLoadingText, 99999);
}

bool LoadingScreen::update(sf::Time frameTime)
{

	if (mFinished)
		mIsDone = true;
	else
		mIsDone = false;
	return mIsDone;
}

void LoadingScreen::startLoading(LoadTask task)
{
	mStart = true;
	mFinished = false;
	mTask = task;
	mThread = ThreadPtr(new sf::Thread(&LoadingScreen::runTask, this));
	mThread->launch();
}

bool &LoadingScreen::getIsDone()
{
	return mIsDone;
}

bool &LoadingScreen::getIsStarted()
{
	return mStart;
}

void LoadingScreen::runTask()
{
	if (mTask == LoadTask::StartGame)
	{
		MHI.unload(MenuID::MainMenu);
		MHI.load(MenuID::PauseMenu);
		LVLMI.load();
	}
	else if (mTask == LoadTask::LoadMenu)
	{
		LVLMI.unload();
		MHI.unload(MenuID::PauseMenu);

		/* ==== Quick fix for bad unloads ===== */
		RMI.truncateTextures();
		RMI.truncateImages();
		RMI.truncateSounds();
		RMI.truncateFolders();
		RMI.truncateFonts();
		/* ==================================== */

		MHI.load(MenuID::MainMenu);
	}
	else if (mTask == LoadTask::LoadAct1)
	{
		LVLMI.unloadCurrentAct();
		LVLMI.loadAct1();
	}

	mStart = false;
	mFinished = true;
	mThread->terminate();
}
