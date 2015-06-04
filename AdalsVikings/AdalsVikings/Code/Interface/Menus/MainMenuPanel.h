#pragma once
#include "MenuPanel.h"
#include "..\Button.h"
#include "..\..\Logics\Animation.h"

class MainMenuPanel : public MenuPanel
{
public:
	MainMenuPanel();

	virtual void load();
	virtual void unload();

	virtual void update(sf::Time frameTime);
	virtual void render(IndexRenderer &iRenderer);

	virtual MenuEvent getEvent();

private:
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
	bool mPlaySound;
	bool mRestartSounds;
};