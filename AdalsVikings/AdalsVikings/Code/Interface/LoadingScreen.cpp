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

void LoadingScreen::initialize()
{
	mThread = ThreadPtr(new std::thread(&LoadingScreen::runTask, this));
	mThread->detach();
}

LoadingScreen::~LoadingScreen()
{
	terminate();
	//mThread->join();
}

bool LoadingScreen::update(sf::Time frameTime)
{
	if (mFinished)
		mIsDone = true;
	else
		mIsDone = false;
	return mIsDone;
}

void LoadingScreen::render(IndexRenderer &iRenderer)
{
	mLoadingText.setFont(mFont);
	mLoadingText.setString("Loading Resources");
	mLoadingText.setPosition(1920 / 2.f, 1080 / 2.f + 50.f);
	iRenderer.addText(mLoadingText, 99999);
}

void LoadingScreen::startLoading(LoadTask task)
{
	mTask = task;
	if (mTask != LoadTask::LoadNearbyLevels)
	{
		mStart = true;
		mFinished = false;
	}
}

void LoadingScreen::terminate()
{
	mTask = LoadTask::Finished;
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

			}
			else if (mTask == LoadTask::LoadNearbyLevels)
			{
				LVLMI.unloadCacheLevels();
				LVLMI.loadNearbyLevels();
			}
			else if (mTask == LoadTask::StartGame)
			{
				MHI.unload(MenuID::MainMenu);
				MHI.load(MenuID::PauseMenu);
				LVLMI.load();
				LVLMI.loadAct1();
			}
			else if (mTask == LoadTask::LoadMenu)
			{
				LVLMI.unload();
				MHI.unload(MenuID::PauseMenu);
				MHI.load(MenuID::MainMenu);
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
				/*LVLMI.unloadCurrentAct();
				LVLMI.loadBoatScene();*/
			}
			mTask = LoadTask::None;

			mStart = false;
			mFinished = true;
		}
	}
}

void LoadingScreen::loadNearbyLevels()
{

}
