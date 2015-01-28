#include "Game.h"
#include "..\Objects\Player.h"
#include "..\Levels\TileMap.h"
#include "Node.h"
#include "PathFinder.h"
#include "MouseState.h"
#include "IndexRenderer.h"

sf::Time frameTime = sf::seconds(1.f / 60.f);

int mWidth = 1280;
int mHeight = 720;

IndexRenderer indexRenderer;

Game::Game()
	:mWindow(sf::VideoMode(mWidth, mHeight), "Adal’s Vikings")
	, mLevelManager()
{
	mWindow.setView(sf::View(sf::FloatRect(0, 0, 1920, 1080)));
	MouseState::getInstance().initialize(mWindow);
	indexRenderer.setWindow(mWindow);
}

Game::~Game()
{

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
			processEvents();
			update(frameTime);
		}
		render();
	}
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
	}
}

void Game::resize(int width, int height)
{
	mWidth = width;
	mHeight = height;

	cout << "---- Window Resized! ----" << endl;
	cout << "Width: " << mWidth << endl;
	cout << "Height: " << mHeight << endl;
}

void Game::update(sf::Time frameTime)
{
	mLevelManager.update(frameTime);

}

void Game::render()
{
	mWindow.clear(sf::Color::Black);
	mLevelManager.render(indexRenderer);
	indexRenderer.display();
	mWindow.display();
}