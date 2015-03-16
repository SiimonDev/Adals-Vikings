#pragma once
#include "MenuPanel.h"
#include "..\Button.h"

class PlayPanel : public MenuPanel
{
public:
	PlayPanel();

	virtual void load();
	virtual void unload();

	virtual void update(sf::Time frameTime);
	virtual void render(IndexRenderer &iRenderer);

	virtual MenuEvent getEvent();

private:
	Button newGameButton;
	Button loadButton;
	Button menuButton;

	MenuEvent mCurrentEvent;

	sf::Sprite mBackground;

	int mIndex;
};