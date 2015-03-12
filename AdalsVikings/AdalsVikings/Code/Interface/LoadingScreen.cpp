#include "LoadingScreen.h"
#include "..\Logics\MouseState.h"
#include "..\Logics\KeyboardState.h"
#include "..\Logics\ResourceManager.h"
#include "..\Levels\LevelManager.h"
#include "..\Levels\PortalLoader.h"
#include <iostream>
#include <memory>
#include <time.h>

LoadingScreen::LoadingScreen()
: mIsDone(false)
 , mStart(false)
 , mTask(None)
{
	
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

	RMI.loadResource(Texture::LoadingScreenBackground);
	RMI.loadResource(Texture::LoadingScreenBackgroundX);
	RMI.loadResource(Texture::LoadingThingyAnimation);
	RMI.loadResource(Font::Font1);

	mBackground.setTexture(RMI.getResource(Texture::LoadingScreenBackground));
	mBackground.setPosition(0, 0);
	mLoadAnimation.load(RMI.getResource(Texture::LoadingThingyAnimation), sf::Vector2i(3, 4), sf::milliseconds(1000), sf::seconds(0), true);
	mLoadAnimation.getSprite().setOrigin(mLoadAnimation.getSpriteSize().x / 2, mLoadAnimation.getSpriteSize().y / 2);
	mLoadAnimation.setPosition(sf::Vector2f(1920 / 2, 1080 / 2));
	mLoadAnimation.setProportions(sf::Vector2f(954, 259));
	mLoadAnimation.setIndex(22);
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
	{
		mLoadAnimation.animate(frameTime);
		mIsDone = false;
	}
	return mIsDone;
}

void LoadingScreen::render(IndexRenderer &iRenderer)
{
	iRenderer.addSprite(mBackground, 20);
	mLoadAnimation.render(iRenderer);
}

void LoadingScreen::startLoading(LoadTask task)
{
	mTask = task;
	if (mTask != LoadTask::LoadNearbyLevels)
	{
		srand(time(NULL));
		int stuff = (rand() % 2) + 1;
		if (stuff == 1)
			mBackground.setTexture(RMI.getResource(Texture::LoadingScreenBackgroundX));
		else
			mBackground.setTexture(RMI.getResource(Texture::LoadingScreenBackground));

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
				LVLMI.loadBoatScene();
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
