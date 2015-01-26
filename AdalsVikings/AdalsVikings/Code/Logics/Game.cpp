#include "Game.h"
#include "..\Objects\Player.h"
#include "..\Levels\TileMap.h"
#include "Node.h"
#include "PathFinder.h"
#include "MouseState.h"

sf::Time frameTime = sf::seconds(1.f / 60.f);

int mWidth = 1280;
int mHeight = 720;

Player player;
TileMap tileMap;

sf::Image image;
sf::Texture bg;
sf::Sprite bgSprite;

Game::Game():
mWindow(sf::VideoMode(mWidth, mHeight), "Adal’s Vikings")
{
	mWindow.setView(sf::View(sf::FloatRect(0, 0, 1920, 1080)));
	LevelManager::getInstance().initialize();
	MouseState::getInstance().initialize(mWindow);

	image.loadFromFile("Assets/MapFiles/Map1RC.png");
	tileMap.setTiles(sf::Vector2i(20, 20), image);
	//bg.loadFromImage(image);
	bg.loadFromFile("Assets/MapFiles/Map1.png");
	bgSprite.setTexture(bg);

	Player::loadContent();
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
	LevelManager::getInstance().update(frameTime);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousePos = PathFinder::getClosestNode(tileMap, MouseState::getInstance().getMousePosition());
		sf::Vector2i playerPos = tileMap.getClosestTile(player.getPosition());

		Path path = PathFinder::getPath(tileMap, playerPos, mousePos);

		//cout << endl;
		//for each (sf::Vertex pos in path){
		//	cout << "X:" << pos.position.x << " Y:" << pos.position.y << endl;
		//	cout << "R:" << float(pos.color.r) << " G:" << float(pos.color.g) << " B:" << float(pos.color.b) << " A:" << float(pos.color.a) << endl;
		//}
		//cout << endl;

		player.walkPath(path);
	}

	player.update(frameTime);
}

void Game::render()
{
	mWindow.clear(sf::Color::Black);

	//LevelManager::getInstance().render(mWindow);
	mWindow.draw(bgSprite);
	tileMap.draw(mWindow);
	player.render(mWindow);

	mWindow.display();
}