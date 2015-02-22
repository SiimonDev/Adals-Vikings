#pragma once
#include "MenuPanel.h"
#include "..\Button.h"
#include "..\..\Logics\Animation.h"

class PauseMenuPanel : public MenuPanel
{
public:
	PauseMenuPanel(MenuPanels &activeMenuPanels);

	virtual void load();
	virtual void unload();

	virtual void update(sf::Time frameTime);
	virtual void render(IndexRenderer &iRenderer);

	virtual MenuEvent getEvent();

private:
	int mIndex;

	MenuPanels* mMenuPanels;

	Button resumeButton;
	Button saveButton;
	Button optionButton;
	Button mainMenuButton;
	Button exitButton;

	MenuEvent mCurrentEvent;

	sf::Sprite mBackground;
};