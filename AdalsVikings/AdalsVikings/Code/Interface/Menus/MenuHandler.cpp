#include "MenuHandler.h"
#include "..\..\Logics\KeyboardState.h"

MenuHandler &MenuHandler::getInstance()
{
	static std::unique_ptr<MenuHandler> instance;

	if (instance == NULL)
		instance = std::unique_ptr<MenuHandler>(new MenuHandler());

	return *instance;
}

MenuHandler::MenuHandler()
{
	// Main Menu Section
	mMainMenuPanels.push_back(new MainMenuPanel());

	// Pause Menu Section
	mPauseMenuPanels.push_back(new PauseMenuPanel());

	load(MenuID::MainMenu);
}

void MenuHandler::load(MenuID menuID)
{
	mCurrentID = menuID;
	mActiveMenuPanels.clear();
	if (menuID == MenuID::MainMenu){
		for each (MenuPanel* panel in mMainMenuPanels)
			panel->load();
		
		mActiveMenuPanels.push_back(mMainMenuPanels[0]);
	}
	if (menuID == MenuID::PauseMenu){
		for each (MenuPanel* panel in mPauseMenuPanels)
			panel->load();
	}
}
void MenuHandler::unload(MenuID menuID)
{
	mActiveMenuPanels.clear();

	if (menuID == MenuID::MainMenu){
		for each (MenuPanel* panel in mMainMenuPanels)
			panel->unload();
	}
	if (menuID == MenuID::PauseMenu){
		for each (MenuPanel* panel in mPauseMenuPanels)
			panel->unload();
	}
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
		mActiveMenuPanels.push_back(mPauseMenuPanels[0]);
	}
}
void MenuHandler::render(IndexRenderer &iRenderer)
{
	for (int i = 0; i < mActiveMenuPanels.size(); i++){
		mActiveMenuPanels[i]->render(iRenderer);
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