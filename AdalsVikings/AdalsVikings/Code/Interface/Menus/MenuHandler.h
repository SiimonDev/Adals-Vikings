#pragma once
#include "MainMenuPanel.h"
#include "PauseMenuPanel.h"
#include "PlayPanel.h"

#define MHI MenuHandler::getInstance()

enum MenuID
{
	MainMenu,
	PauseMenu
};

class MenuHandler
{
public:
	static MenuHandler &getInstance();

	void load(MenuID menuID);
	void unload(MenuID menuID);
	void update(sf::Time frameTime);
	void render(IndexRenderer &iRenderer);
	void popMenu();

	bool hasActiveMenu();
	void setActive(bool active);

	MenuEvent getEvent();

private:
	MenuHandler();
	MenuHandler(MenuHandler&);
	void operator=(MenuHandler&);

	MenuID mCurrentID;
	MenuEvent mCurrentEvent;

	MainMenuPanel mMainMenuPanel;
	PlayPanel mPlayPanel;
	PauseMenuPanel mPauseMenuPanel;

	MenuPanels mActiveMenuPanels;
	MenuPanels mMainMenuPanels;
	MenuPanels mPauseMenuPanels;

	bool mActive;
};