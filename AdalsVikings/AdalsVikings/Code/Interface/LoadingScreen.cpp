#include "LoadingScreen.h"
#include "..\Logics\MouseState.h"
#include "..\Logics\KeyboardState.h"
#include "..\Logics\ResourceManager.h"
#include "..\Levels\LevelManager.h"
#include "..\Levels\PortalLoader.h"
#include <iostream>
#include <memory>

LoadingScreen::LoadingScreen()
: mIsDone(false)
 , mStart(false)
 , mTask(None)
{
	mFont.loadFromFile("Assets/fonts/font1.ttf");
}

LoadingScreen & LoadingScreen::getInstance()
{
	static std::unique_ptr<LoadingScreen> instance;

	if (instance == NULL)
		instance = std::unique_ptr<LoadingScreen>(new LoadingScreen());

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
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time frameTime = sf::seconds(1.f / 60.f);
	while (mTask != LoadTask::Finished)
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate >= frameTime)
		{
			timeSinceLastUpdate -= frameTime;
			if (mTask == LoadTask::None)
			{
				;
			}
			if (mTask == LoadTask::StartGame)
			{
				MHI.unload(MenuID::MainMenu);
				MHI.load(MenuID::PauseMenu);
				LVLMI.load();
				LVLMI.loadAct1();
				mStart = false;
				mFinished = true;
			}
			else if (mTask == LoadTask::LoadMenu)
			{
				LVLMI.unload();
				LVLMI.unloadCurrentAct();
				MHI.unload(MenuID::PauseMenu);

				/* ==== Quick fix for bad unloads ===== */
				RMI.truncateTextures();
				RMI.truncateImages();
				RMI.truncateSounds();
				RMI.truncateFolders();
				RMI.truncateFonts();
				/* ==================================== */

				MHI.load(MenuID::MainMenu);
				mStart = false;
				mFinished = true;
			}
			else if (mTask == LoadTask::LoadAct1)
			{
				LVLMI.unloadCurrentAct();
				LVLMI.loadAct1();
				mStart = false;
				mFinished = true;
			}
			else if (mTask == LoadTask::LoadTest)
			{
				/*LVLMI.setIsActive(false);
				LVLMI.unloadCurrentAct();
				LVLMI.loadBoatScene();
				LVLMI.setIsActive(true);*/
			}
			mTask = LoadTask::None;
		}
	}
}

void LoadingScreen::initialize()
{
	mThread = ThreadPtr(new std::thread(&LoadingScreen::runTask, this));
	mThread->detach();
}
