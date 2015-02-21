#include "Game.h"
#include "..\Objects\ObjectHandler.h"
#include "..\Levels\LevelManager.h"
#include "..\Logics\Fade.h"
#include "..\Interface\Menus\MenuHandler.h"
#include "BoatEvents.h"
#include "MouseState.h"
#include "KeyboardState.h"
#include "IndexRenderer.h"
#include "AudioPlayer.h"

sf::Time frameTime = sf::seconds(1.f / 60.f);

int mWidth = 1280;
int mHeight = 720;

IndexRenderer indexRenderer;
MenuHandler menuHandler;

bool debugMode = false;
bool runGame = false;

Game::Game()
	:mWindow(sf::VideoMode(mWidth, mHeight), "Adal’s Vikings")
{
	mWindow.setView(sf::View(sf::FloatRect(0, 0, 1920, 1080)));
	indexRenderer.setWindow(mWindow);
	mWindow.setVerticalSyncEnabled(false);

	OBHI.initialize();
	KeyboardState::initialize();
	MouseState::initialize(mWindow);
	Fade::getInstance().initialize();
}

Game::~Game()
{

}

void Game::resize(int width, int height)
{
	mWidth = width;
	mHeight = height;

	indexRenderer.resize(width, height);

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
		if (KeyboardState::isPressed(sf::Keyboard::F1))
			debugMode = (!debugMode);

		if (menuHandler.getEvent() == MenuEvent::NewGamePressed)
		{
			LSI.startLoading("StartGame");
			menuHandler.unload(MenuID::MainMenu);
			menuHandler.load(MenuID::PauseMenu);
			runGame = true;
		}
		else if (menuHandler.getEvent() == MenuEvent::ExitGamePressed)
		{
			mWindow.close();
		}

		menuHandler.update(frameTime);
		if (runGame)
		{
			if (menuHandler.getEvent() == MenuEvent::MainMenuPressed)
			{
				LVLMI.unload();
				menuHandler.unload(MenuID::PauseMenu);

				/* ==== Quick fix for bad unloads ===== */
				RMI.truncateTextures();
				RMI.truncateImages();
				RMI.truncateSounds();
				RMI.truncateFolders();
				RMI.truncateFonts();
				/* ==================================== */
				menuHandler.load(MenuID::MainMenu);
				runGame = false;
				LSI.setDone(false);
				LSI.setStarted(false);
				LVLMI.setActivate(false);
			}
			else if (menuHandler.getEvent() == MenuEvent::ResumePressed)
			{
				menuHandler.popMenu();
			}

			if (!menuHandler.hasActiveMenu())
				LVLMI.update(frameTime);
		}

		// Always Last
		AudioPlayer::update(frameTime);
		KeyboardState::update(frameTime);
		MouseState::update(frameTime);
	}
}

void Game::render()
{
	mWindow.clear(sf::Color::Black);
	indexRenderer.clear();
	if (!LSI.getIsDone() && LSI.getIsStarted())
	{
		LSI.render(indexRenderer);
		indexRenderer.display();
	}
	else
	{
		menuHandler.render(indexRenderer);
		if (runGame){
			LVLMI.render(indexRenderer);
		}
		indexRenderer.display();
		if (debugMode){
			PathFinder::getCurrentTileMap().render(indexRenderer);
		}
	}
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
}