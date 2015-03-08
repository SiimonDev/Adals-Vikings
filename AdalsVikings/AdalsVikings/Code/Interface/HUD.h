#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "..\Logics\IndexRenderer.h"

class HUD
{
public:
	HUD();

	void load();
	void unload();
	void update(sf::Time frameTime);
	void render(IndexRenderer &iRenderer);
	void displayHelp(bool value);

	bool isHelpActive();

	bool isInventoryButtonReleased();
	bool isHelpButtonReleased();

	bool isButtonClicked();
	bool isButtonPressed();
	bool isButtonReleased();

private:
	bool mDisplayHelp;
	bool mOldDisplayHelp;

	Button mInventoryButton;
	Button mHelpButton;
	Button mOKButton;

	sf::Sprite mHelpPanel;
};