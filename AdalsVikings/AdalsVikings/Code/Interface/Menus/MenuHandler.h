#pragma once
#include "MainMenuPanel.h"
#include "PauseMenuPanel.h"

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

	MenuEvent getEvent();

private:
	MenuHandler();
	MenuHandler(MenuHandler&);
	void operator=(MenuHandler&);

	MenuID mCurrentID;

	MenuPanels mActiveMenuPanels;
	MenuPanels mMainMenuPanels;
	MenuPanels mPauseMenuPanels;

	// All the meny Panels
	MainMenuPanel* mMainMenuPanel;
	PauseMenuPanel* mPauseMenuPanel;
	MenuEvent mCurrentEvent;
};