#include "Game.h"
#include "..\Objects\ObjectHandler.h"
#include "..\Levels\LevelManager.h"
#include "..\Logics\Fade.h"
#include "..\Logics\WindowState.h"
#include "..\Interface\Menus\MenuHandler.h"
#include "..\Interface\LoadingScreen.h"
#include "BoatEvents.h"
#include "MouseState.h"
#include "KeyboardState.h"
#include "IndexRenderer.h"
#include "AudioPlayer.h"

int mWidth = 1280;
int mHeight = 720;

IndexRenderer iRenderer;

bool debugMode = false;
bool runGame = false;

Game::Game()
	:mWindow(sf::VideoMode(mWidth, mHeight), "Adal’s Vikings")
{
	mWindow.setView(sf::View(sf::FloatRect(0, 0, 1920, 1080)));
	mWindow.setVerticalSyncEnabled(false);
	mWindow.setMouseCursorVisible(false);

	WinState.initialize(mWindow);
	OBHI.initialize();
	FadeI.initialize();
	KeyboardState::initialize();
	MouseState::initialize();
}

Game::~Game()
{

}

void Game::resize(int width, int height)
{
	mWidth = width;
	mHeight = height;

	iRenderer.resize(width, height);

	cout << "---- Window Resized! ----" << endl;
	cout << "Width: " << mWidth << endl;
	cout << "Height: " << mHeight << endl;
}

void Game::update(sf::Time frameTime)
{
	if (!LSI.getIsDone() && LSI.getIsStarted())
		LSI.update(frameTime);
	else
	{
		AudioPlayer::update(frameTime);
		KeyboardState::update(frameTime);
		MouseState::update(frameTime);

		if (KeyboardState::isPressed(sf::Keyboard::F1))
			debugMode = (!debugMode);

		MHI.update(frameTime);
		if (runGame)
		{
			if (!MHI.hasActiveMenu())
				LVLMI.update(frameTime);

			// Check for pause menu events
			if (MHI.getEvent() == MenuEvent::MainMenuPressed)
			{
				LSI.startLoading(LoadTask::LoadMenu);
				runGame = false;
			}
			else if (MHI.getEvent() == MenuEvent::ResumePressed)
			{
				MHI.popMenu();
			}
		}

		// Check for main menu events
		if (MHI.getEvent() == MenuEvent::NewGamePressed)
		{
			LSI.startLoading(LoadTask::StartGame);
			runGame = true;
		}
		else if (MHI.getEvent() == MenuEvent::ExitGamePressed)
		{
			mWindow.close();
		}
	}
}

void Game::render()
{
	mWindow.clear(sf::Color::Black);
	iRenderer.clear();
	if (!LSI.getIsDone() && LSI.getIsStarted())
	{
		LSI.render(iRenderer);
		iRenderer.display();
	}
	else
	{
		MHI.render(iRenderer);
		if (runGame){
			LVLMI.render(iRenderer);
		}
		iRenderer.display();
		if (debugMode){
			PathFinderI.getCurrentTileMap().render(iRenderer);
		}
	}
	MouseState::render();
	mWindow.display();
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			mWindow.close();
			break;

		case sf::Event::Resized:
			resize(event.size.width, event.size.height);
			break;

		default:
			break;
		}
		MouseState::checkEvents(event.type);
		KeyboardState::checkEvents(event.type);
	}
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time frameTime = sf::seconds(1.f / 60.f);
	while (mWindow.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate >= frameTime)
		{
			timeSinceLastUpdate -= frameTime;
			update(frameTime);
			processEvents();
		}
		render();
	}
	AudioPlayer::unload();
}