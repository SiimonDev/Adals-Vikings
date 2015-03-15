#pragma once
#include <SFML\Graphics.hpp>
#include "..\Logics\IndexRenderer.h"
#include "..\Interface\Menus\MenuHandler.h"
#include <thread>

#define LSI LoadingScreen::getInstance()

typedef std::unique_ptr<std::thread> ThreadPtr;

enum LoadTask
{
	StartGame,
	LoadGame,
	LoadBoat,
	LoadAct1,
	LoadTest,
	LoadMenu,
	None,
	LoadNearbyLevels,
	Finished,
};

class LoadingScreen
{
public:
	static LoadingScreen &getInstance();

	~LoadingScreen();

	void initialize();
	void render(IndexRenderer &iRenderer);
	bool update(sf::Time dt);

	void startLoading(LoadTask task);
	void loadNearbyLevels();
	void terminate();

	bool &getIsDone();
	bool &getIsStarted();

private:
	void runTask();

	LoadingScreen();
	LoadingScreen(LoadingScreen&);
	void operator=(LoadingScreen&);

	sf::Text mLoadingText;
	sf::Sprite mBackground;
	Animation mLoadAnimation;

	ThreadPtr mThread;
	LoadTask mTask;
	bool mFinished, mStarted;
	bool mIsDone, mStart;
};