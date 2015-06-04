#pragma once
#include <SFML/Graphics.hpp>
#include "..\..\Logics\IndexRenderer.h"
#include <vector>

enum MenuEvent
{
	NONE,
	PlayPressed,
	NewGamePressed,
	ExitGamePressed,
	ExitMainMenuPressed,
	MainMenuPressed,
	BackToMenuPressed,
	ResumePressed,
	SavePressed,
	OptionsPressed,
	LoadGamePressed
};

class MenuPanel;
typedef std::vector<MenuPanel*> MenuPanels;

class MenuPanel
{
public:
	MenuPanel();

	virtual void load() = 0;
	virtual void unload() = 0;

	virtual void update(sf::Time frameTime) = 0;
	virtual void render(IndexRenderer &iRenderer) = 0;

	virtual MenuEvent getEvent() = 0;
};
