#include "MenuHandler.h"
#include "..\..\Logics\KeyboardState.h"

MenuHandler::MenuHandler()
{
	mMainMenuPanel = new MainMenuPanel(mActiveMenuPanels);
	mPauseMenuPanel = new PauseMenuPanel(mActiveMenuPanels);

	// Main Menu Section
	mMainMenuPanels.push_back(mMainMenuPanel);

	// Pause Menu Section
	mPauseMenuPanels.push_back(mPauseMenuPanel);

	load(MenuID::MainMenu);
	mActiveMenuPanels.push_back(mMainMenuPanel);
}

void MenuHandler::load(MenuID menuID)
{
	mCurrentID = menuID;
	mActiveMenuPanels.clear();
	if (menuID == MenuID::MainMenu){
		for each (MenuPanel* panel in mMainMenuPanels){
			panel->load();
		}
		mActiveMenuPanels.push_back(mMainMenuPanel);
	}
	if (menuID == MenuID::PauseMenu){
		for each (MenuPanel* panel in mPauseMenuPanels){
			panel->load();
		}
	}
}
void MenuHandler::unload(MenuID menuID)
{
	if (menuID == MenuID::MainMenu){
		for each (MenuPanel* panel in mMainMenuPanels){
			panel->unload();
		}
	}
	if (menuID == MenuID::PauseMenu){
		for each (MenuPanel* panel in mPauseMenuPanels){
			panel->unload();
		}
	}
	mActiveMenuPanels.clear();
}

void MenuHandler::update(sf::Time frameTime)
{
	mCurrentEvent = MenuEvent::NONE;
	if (hasActiveMenu())
	{
		mActiveMenuPanels.at(mActiveMenuPanels.size() - 1)->update(frameTime);
		mCurrentEvent = mActiveMenuPanels.at(mActiveMenuPanels.size() - 1)->getEvent();

		if (KeyboardState::isPressed(sf::Keyboard::Escape))
		{
			popMenu();
		}
	}
	else if (KeyboardState::isPressed(sf::Keyboard::Escape) && mCurrentID == MenuID::PauseMenu)
	{
		mActiveMenuPanels.push_back(mPauseMenuPanel);
	}
}
void MenuHandler::render(IndexRenderer &iRenderer)
{
	for each (MenuPanel* panel in mActiveMenuPanels){
		panel->render(iRenderer);
	}
}

void MenuHandler::popMenu()
{
	if (!hasActiveMenu() || mCurrentID == MenuID::PauseMenu)
		mActiveMenuPanels.pop_back();
}

MenuEvent MenuHandler::getEvent()
{
	return mCurrentEvent;
}

bool MenuHandler::hasActiveMenu()
{
	return !mActiveMenuPanels.empty();
}