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
	LoadBoat,
	LoadAct1,
	LoadTest,
	LoadMenu,
	None,
	Finished,
};

class LoadingScreen
{
public:
	static LoadingScreen &getInstance();

	void initialize();
	void render(IndexRenderer &iRenderer);
	bool update(sf::Time dt);

	void startLoading(LoadTask task);

	bool &getIsDone();
	bool &getIsStarted();

private:
	void runTask();

	LoadingScreen();
	LoadingScreen(LoadingScreen&);
	void operator=(LoadingScreen&);

	sf::Text mLoadingText;
	sf::Font mFont;

	ThreadPtr mThread;
	LoadTask mTask;
	bool mFinished, mStarted;
	bool mIsDone, mStart;
};