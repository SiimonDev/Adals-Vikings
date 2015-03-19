#pragma once
#include <SFML\Graphics.hpp>
#include "..\Logics\IndexRenderer.h"
#include "..\Logics\VideoFile.h"
#include "..\Interface\Menus\MenuHandler.h"
#include <thread>

#define LSI LoadingScreen::getInstance()

typedef std::unique_ptr<std::thread> ThreadPtr;

enum LoadTask
{
	BootGame,
	StartGame,
	LoadGame,
	LoadBoat,
	LoadAct1,
	LoadTest,
	LoadMainMenu,
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
	void update(sf::Time frameTime);

	void startLoading(LoadTask task, sf::VideoFile* videoFile = NULL);
	void loadNearbyLevels();
	void terminate();
	void setIsWorking(bool value);

	bool &getIsDone();
	bool &getIsStarted();

private:
	void runTask();

	LoadingScreen();
	LoadingScreen(LoadingScreen&);
	void operator=(LoadingScreen&);

	sf::VideoFile* mCurrentVideo;
	sf::Text mLoadingText;
	sf::Sprite mBackground;
	Animation mLoadAnimation;

	ThreadPtr mThread;
	LoadTask mTask;
	bool mFinished;
	bool mIsDone, mStart;
};