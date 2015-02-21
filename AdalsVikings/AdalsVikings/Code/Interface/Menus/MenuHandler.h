#pragma once
#include "MainMenuPanel.h"
#include "PauseMenuPanel.h"

enum MenuID
{
	MainMenu,
	PauseMenu
};

class MenuHandler
{
public:
	MenuHandler();

	void load(MenuID menuID);
	void unload(MenuID menuID);
	void update(sf::Time frameTime);
	void render(IndexRenderer &iRenderer);
	void popMenu();

	bool hasActiveMenu();

	MenuEvent getEvent();

private:
	MenuID mCurrentID;

	MenuPanels mActiveMenuPanels;
	MenuPanels mMainMenuPanels;
	MenuPanels mPauseMenuPanels;

	// All the meny Panels
	MainMenuPanel* mMainMenuPanel;
	PauseMenuPanel* mPauseMenuPanel;
	MenuEvent mCurrentEvent;
};