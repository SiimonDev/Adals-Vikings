#include "LoadingScreen.h"
#include "..\Logics\MouseState.h"
#include "..\Logics\KeyboardState.h"
#include "..\Logics\ResourceManager.h"
#include "..\Logics\Fade.h"
#include "..\Levels\LevelManager.h"
#include "..\Levels\PortalLoader.h"
#include "..\Logics\WindowState.h"
#include <iostream>
#include <memory>
#include <time.h>

LoadingScreen::LoadingScreen()
: mIsDone(false)
 , mStart(false)
 , mTask(None)
{
	
}
LoadingScreen::~LoadingScreen()
{
	terminate();
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

	mLoadingText.setFont(RMI.getResource(Font::Font1));
	mLoadingText.setPosition(sf::Vector2f(200, 1000));
	mLoadingText.setString("Press [Space] To Skip");
	mLoadingText.setOrigin(mLoadingText.getGlobalBounds().width / 2, mLoadingText.getGlobalBounds().height / 2);

	mBackground.setTexture(RMI.getResource(Texture::LoadingScreenBackground));
	mBackground.setPosition(0, 0);

	mLoadAnimation.load(RMI.getResource(Texture::LoadingThingyAnimation), sf::Vector2i(3, 4), sf::milliseconds(1000), sf::seconds(0), true);
	mLoadAnimation.getSprite().setOrigin(mLoadAnimation.getSpriteSize().x / 2, mLoadAnimation.getSpriteSize().y / 2);
	mLoadAnimation.setPosition(sf::Vector2f(1920 / 2, 1080 / 2));
	mLoadAnimation.setProportions(sf::Vector2f(954, 259));
	mLoadAnimation.setIndex(22);
}

void LoadingScreen::update(sf::Time frameTime)
{
	if (mCurrentVideo != NULL)
		mCurrentVideo->update(frameTime);

	if (mFinished)
	{
		if (mCurrentVideo != NULL)
		{
			if (mCurrentVideo->getStatus() == sf::VideoFile::Paused || KeyboardState::isPressed(sf::Keyboard::Space))
			{
				mIsDone = true;
				mStart = false;
				mCurrentVideo->close();
			}
		}
		else
		{
			mIsDone = true;
			mStart = false;
		}
	}
	else
	{
		if (!mFinished)
			mLoadAnimation.animate(frameTime);
		mIsDone = false;
	}
}
void LoadingScreen::render(IndexRenderer &iRenderer)
{
	if (mCurrentVideo != NULL)
	{
		if (!mFinished)
			mLoadAnimation.render(iRenderer);
		else
			iRenderer.addText(mLoadingText, 22);
		mCurrentVideo->render(CurrentWindow);
	}
	else
	{
		iRenderer.addSprite(mBackground, 20);
		mLoadAnimation.render(iRenderer);
	}
}

void LoadingScreen::startLoading(LoadTask task, sf::VideoFile* videoFile)
{
	mCurrentVideo = videoFile;
	if (mCurrentVideo != NULL)
	{
		if (mCurrentVideo->isLoaded())
		{
			mCurrentVideo->restart();
			mCurrentVideo->play();

			mLoadAnimation.setPosition(sf::Vector2f(200, 1000));
			mLoadAnimation.setScale(sf::Vector2f(0.3f, 0.3f));
		}
		else
		{
			mCurrentVideo = NULL;
			mLoadAnimation.setPosition(sf::Vector2f(1920 / 2, 1080 / 2));
			mLoadAnimation.setScale(sf::Vector2f(1.0f, 1.0f));
		}
	}
	else
	{
		mLoadAnimation.setPosition(sf::Vector2f(1920 / 2, 1080 / 2));
		mLoadAnimation.setScale(sf::Vector2f(1.0f, 1.0f));
	}
	mTask = task;
	if (mTask != LoadTask::LoadNearbyLevels)
	{
		srand(time(NULL));
		int stuff = (rand() % 100) + 1;
		if (stuff == 1)
			mBackground.setTexture(RMI.getResource(Texture::LoadingScreenBackgroundX));
		else
			mBackground.setTexture(RMI.getResource(Texture::LoadingScreenBackground));

		mStart = true;
		mFinished = false;
		mIsDone = false;
	}
	else
	{
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
			if (mTask == LoadTask::BootGame)
			{
				FadeI.initialize();
				OBHI.initialize();
				MHI.load(MenuID::MainMenu);
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
			}
			else if (mTask == LoadTask::LoadGame)
			{
				MHI.unload(MenuID::MainMenu);
				MHI.load(MenuID::PauseMenu);
				LVLMI.load(false);
			}
			else if (mTask == LoadTask::LoadMainMenu)
			{
				LVLMI.unload();
				MHI.unload(MenuID::PauseMenu);
				MHI.load(MenuID::MainMenu);
			}
			else if (mTask == LoadTask::LoadAct1)
			{
				LVLMI.unloadCurrentAct();
				LVLMI.loadAct1(true);
				//mStart = false;
				//mFinished = true;
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
void LoadingScreen::setIsWorking(bool value)
{
	mStart = value;
}
