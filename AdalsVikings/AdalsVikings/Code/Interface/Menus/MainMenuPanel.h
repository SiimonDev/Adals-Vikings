#pragma once
#include "MenuPanel.h"
#include "..\Button.h"
#include "..\..\Logics\Animation.h"

class MainMenuPanel : public MenuPanel
{
public:
	MainMenuPanel(MenuPanels &activeMenuPanels);

	virtual void load();
	virtual void unload();

	virtual void update(sf::Time frameTime);
	virtual void render(IndexRenderer &iRenderer);

	virtual MenuEvent getEvent();

private:
	MenuPanels &mMenuPanels;

	Button playButton;
	Button optionButton;
	Button exitButton;

	MenuEvent mCurrentEvent;

	sf::Sprite mBackground;
	sf::Time mTimePassed;
	sf::Time mAnimationTime;
	Animation mAxeAnimation;

	bool mAnimateAxe;
	bool mPlay;
	bool mQuit;
};