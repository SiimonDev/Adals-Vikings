#pragma once
#include <SFML\Graphics.hpp>
#include "..\Logics\ParallelLoader.h"
#include "..\Logics\IndexRenderer.h"

#define LSI LoadingScreen::getInstance()

class LoadingScreen
{
public:
	static LoadingScreen &getInstance();

	void initialize();
	void finish();
	void render(IndexRenderer &iRenderer);
	bool update(sf::Time dt);
	bool handleEvent(const sf::Event& event);
	void setDone(bool value);
	void setStarted(bool value);
	void startLoading(std::string task);

	bool &getIsDone();
	bool &getIsStarted();

private:
	LoadingScreen();
	sf::Text mLoadingText;
	bool mIsDone, mStart;

	ParallelLoader mLoadingTask;
};