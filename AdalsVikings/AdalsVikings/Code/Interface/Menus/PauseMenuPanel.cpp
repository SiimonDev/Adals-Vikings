#include "PauseMenuPanel.h"
#include "..\..\Logics\AudioPlayer.h"
#include "..\..\Logics\KeyboardState.h"

PauseMenuPanel::PauseMenuPanel(MenuPanels &activeMenuPanels):
mMenuPanels(&activeMenuPanels)
{
	mIndex = 9999999;
	mCurrentEvent = MenuEvent::NONE;
}

void PauseMenuPanel::load()
{
	RMI.load(Fonts::MenuButtons, "assets/fonts/font1.ttf");
	RMI.load(Textures::PauseMenuResumeButton, "assets/Images/interface/pauseManu/button_resume.png");
	RMI.load(Textures::PauseMenuSaveButton, "assets/Images/interface/pauseManu/button_save.png");
	RMI.load(Textures::PauseMenuOptionsButton, "assets/Images/interface/pauseManu/button_options.png");
	RMI.load(Textures::PauseMenuMainMenuButton, "assets/Images/interface/pauseManu/button_main_menu.png");
	RMI.load(Textures::PauseMenuExitButton, "assets/Images/interface/pauseManu/button_exit.png");

	RMI.load(Textures::PauseMenuBackground, "assets/Images/interface/pauseManu/InGame_menu.png");
	mBackground.setTexture(RMI.getTexture(Textures::PauseMenuBackground));
	mBackground.setOrigin(mBackground.getTexture()->getSize().x / 2, mBackground.getTexture()->getSize().y / 2);
	mBackground.setPosition(960, 540);

	resumeButton = Button(Textures::PauseMenuResumeButton, Fonts::MenuButtons, sf::Vector2f(), "Resume the game");
	resumeButton.setPosition(sf::Vector2f(960, 300));
	resumeButton.setOrigin(ButtonOrigin::Center);
	resumeButton.setTextStyle(sf::Text::Bold);
	resumeButton.setDescriptionStyle(sf::Text::Bold);
	resumeButton.setDescriptionPosition(sf::Vector2f(200, 0));
	resumeButton.setIndex(mIndex + 1);

	saveButton = Button(Textures::PauseMenuSaveButton, Fonts::MenuButtons, sf::Vector2f(), "Resume the game");
	saveButton.setPosition(sf::Vector2f(960, 433));
	saveButton.setOrigin(ButtonOrigin::Center);
	saveButton.setTextStyle(sf::Text::Bold);
	saveButton.setDescriptionStyle(sf::Text::Bold);
	saveButton.setDescriptionPosition(sf::Vector2f(200, 0));
	saveButton.setIndex(mIndex + 1);
	saveButton.setEnabled(false);

	optionButton = Button(Textures::PauseMenuOptionsButton, Fonts::MenuButtons, sf::Vector2f(), "Go to options menu");
	optionButton.setPosition(sf::Vector2f(960, 569));
	optionButton.setOrigin(ButtonOrigin::Center);
	optionButton.setTextStyle(sf::Text::Bold);
	optionButton.setDescriptionStyle(sf::Text::Bold);
	optionButton.setDescriptionPosition(sf::Vector2f(200, 0));
	optionButton.setIndex(mIndex + 1);
	optionButton.setEnabled(false);

	mainMenuButton = Button(Textures::PauseMenuMainMenuButton, Fonts::MenuButtons, sf::Vector2f(), "Back to main menu");
	mainMenuButton.setPosition(sf::Vector2f(960, 702));
	mainMenuButton.setOrigin(ButtonOrigin::Center);
	mainMenuButton.setTextStyle(sf::Text::Bold);
	mainMenuButton.setDescriptionStyle(sf::Text::Bold);
	mainMenuButton.setDescriptionPosition(sf::Vector2f(200, 0));
	mainMenuButton.setIndex(mIndex + 1);

	exitButton = Button(Textures::PauseMenuExitButton, Fonts::MenuButtons, sf::Vector2f(), "Exit the game");
	exitButton.setPosition(sf::Vector2f(960, 840));
	exitButton.setOrigin(ButtonOrigin::Center);
	exitButton.setTextStyle(sf::Text::Bold);
	exitButton.setDescriptionStyle(sf::Text::Bold);
	exitButton.setDescriptionPosition(sf::Vector2f(200, 0));
	exitButton.setIndex(mIndex + 1);
}

void PauseMenuPanel::unload()
{
	RMI.unload(Fonts::MenuButtons);
	RMI.unload(Textures::PauseMenuBackground);

	RMI.unload(Textures::PauseMenuResumeButton);
	RMI.unload(Textures::PauseMenuSaveButton);
	RMI.unload(Textures::PauseMenuOptionsButton);
	RMI.unload(Textures::PauseMenuMainMenuButton);
	RMI.unload(Textures::PauseMenuExitButton);
}

void PauseMenuPanel::update(sf::Time frameTime)
{
	mCurrentEvent = MenuEvent::NONE;
	resumeButton.update();
	saveButton.update();
	mainMenuButton.update();
	optionButton.update();
	exitButton.update();

	if (resumeButton.isClicked())
	{
		mCurrentEvent = MenuEvent::ResumePressed;
	}
	else if (mainMenuButton.isClicked())
	{
		mCurrentEvent = MenuEvent::MainMenuPressed;
	}
	else if (exitButton.isClicked())
	{
		mCurrentEvent = MenuEvent::ExitGamePressed;
	}
}

void PauseMenuPanel::render(IndexRenderer &iRenderer)
{
	resumeButton.render(iRenderer);
	saveButton.render(iRenderer);
	mainMenuButton.render(iRenderer);
	optionButton.render(iRenderer);
	exitButton.render(iRenderer);
	iRenderer.addSprite(mBackground, mIndex);
}

MenuEvent PauseMenuPanel::getEvent()
{
	return mCurrentEvent;
}