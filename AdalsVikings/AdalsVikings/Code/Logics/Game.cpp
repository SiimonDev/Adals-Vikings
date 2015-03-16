#include "Game.h"
#include "..\Objects\ObjectHandler.h"
#include "..\Levels\LevelManager.h"
#include "..\Interface\Menus\MenuHandler.h"
#include "BoatEvents.h"
#include "MouseState.h"
#include "KeyboardState.h"
#include "WindowState.h"
#include "Debug.h"
#include "IndexRenderer.h"
#include "AudioPlayer.h"
#include "Fade.h"

sf::Time frameTime = sf::seconds(1.f / 60.f);

int mWidth = 1280;
int mHeight = 720;

IndexRenderer iRenderer;

bool runGame = false;

Game::Game()
	:mWindow(sf::VideoMode(mWidth, mHeight), "Adal’s Vikings"/*, sf::Style::Fullscreen*/)
{
	mWindow.setView(sf::View(sf::FloatRect(0, 0, 1920, 1080)));
	mWindow.setMouseCursorVisible(false);

	icon.loadFromFile("assets/images/interface/icon_32.png");
	mWindow.setIcon(32, 32, icon.getPixelsPtr());

	WinState.initialize(mWindow);
	OBHI.initialize();
	FadeI.initialize();
	LSI.initialize();
	KeyboardState::initialize();
	MouseState::initialize();
}

Game::~Game()
{

}

void Game::update(sf::Time frameTime)
{
	if (!LSI.getIsDone() && LSI.getIsStarted())
	{
		LSI.update(frameTime);
	}
	else
	{
		MHI.update(frameTime);
		if (runGame)
		{
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
		else if (MHI.getEvent() == MenuEvent::LoadGamePressed)
		{
			LSI.startLoading(LoadTask::LoadGame);
			runGame = true;
		}
		else if (MHI.getEvent() == MenuEvent::ExitGamePressed)
		{
			mWindow.close();
		}
		AudioPlayer::update(frameTime);
	}

	// Always Last
	KeyboardState::update(frameTime);
	MouseState::update(frameTime);
	DebugI.update(frameTime);
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
		if (DebugMode){
			PathFinder::getCurrentTileMap().render(iRenderer);
		}
	}
	
	MouseState::render();
	mWindow.display();
}

void Game::processEvents()
{
	sf::Event event;
	if (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			mWindow.close();
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
			/* ======== Prevents the game from freezing ======== */
			if (timeSinceLastUpdate > sf::seconds(4))
				timeSinceLastUpdate = sf::seconds(0);
			/* ================================================= */
			timeSinceLastUpdate -= frameTime;
			update(frameTime);
			processEvents();
		}
		render();
	}
	AudioPlayer::unload();
}