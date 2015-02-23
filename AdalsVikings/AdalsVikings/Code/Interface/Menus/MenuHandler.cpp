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
	mMainMenuPanel = new MainMenuPanel(mActiveMenuPanels);
	mPauseMenuPanel = new PauseMenuPanel(mActiveMenuPanels);
	// Main Menu Section
	//mMainMenuPanels.push_back(mMainMenuPanel);

	// Pause Menu Section
	//mPauseMenuPanels.push_back(mPauseMenuPanel);

	load(MenuID::MainMenu);
}

void MenuHandler::load(MenuID menuID)
{
	mCurrentID = menuID;
	mActiveMenuPanels.clear();
	if (menuID == MenuID::MainMenu){
		mMainMenuPanel->load();
		mActiveMenuPanels.push_back(mMainMenuPanel);
	}
	if (menuID == MenuID::PauseMenu){
		mPauseMenuPanel->load();
	}
}
void MenuHandler::unload(MenuID menuID)
{
	mActiveMenuPanels.clear();

	if (menuID == MenuID::MainMenu){
		mMainMenuPanel->unload();
	}
	if (menuID == MenuID::PauseMenu){
		mPauseMenuPanel->unload();
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
		mActiveMenuPanels.push_back(mPauseMenuPanel);
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