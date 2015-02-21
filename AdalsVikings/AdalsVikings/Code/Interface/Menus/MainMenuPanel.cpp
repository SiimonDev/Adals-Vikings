#include "MainMenuPanel.h"
#include "..\..\Logics\AudioPlayer.h"

MainMenuPanel::MainMenuPanel(MenuPanels &activeMenuPanels) :
mMenuPanels(&activeMenuPanels), mAnimationTime(sf::milliseconds(500)), mTimePassed(sf::Time::Zero)
{
	mCurrentEvent = MenuEvent::NONE;
	mAxeAnimation.restart();
}

void MainMenuPanel::load()
{
	RMI.load(Fonts::MenuButtons, "assets/fonts/font1.ttf");
	RMI.load(Textures::MainMenuPlayButton, "assets/images/interface/MainMenu/button_play.png");
	RMI.load(Textures::MainMenuOptionsButton, "assets/images/interface/MainMenu/button_options_disabled.png");
	RMI.load(Textures::MainMenuQuitButton, "assets/images/interface/MainMenu/button_quit.png");
	RMI.load(Textures::MainMenuBackground, "assets/images/Interface/MainMenu/menu_background.png");
	RMI.load(Textures::AxeAnimation, "assets/images/Interface/MainMenu/flying_axe.png");
	AudioPlayer::playMusic("assets/sounds/music/Theme3.ogg", "mainMenu", true, 20);

	mBackground.setTexture(RMI.getTexture(Textures::MainMenuBackground));

	mAxeAnimation.load(RMI.getTexture(Textures::AxeAnimation), Frames(5, 1), sf::milliseconds(400), sf::seconds(0.1), false);
	mAxeAnimation.getSprite().setOrigin(mAxeAnimation.getSprite().getTextureRect().width, mAxeAnimation.getSprite().getTextureRect().height);
	mAxeAnimation.setProportions(sf::Vector2f(1605, 968));
	mAxeAnimation.setPosition(sf::Vector2f(1920, 1080));
	mAxeAnimation.setIdleFrame(sf::Vector2i(5, 1));
	mAxeAnimation.setIndex(50);
	mAxeAnimation.restart();

	playButton = Button(Textures::MainMenuPlayButton, Fonts::MenuButtons, sf::Vector2f(), "Start a new Game");
	playButton.setPosition(sf::Vector2f(1010, 275));
	playButton.setOrigin(ButtonOrigin::Center);
	playButton.setTextStyle(sf::Text::Bold);
	playButton.setDescriptionStyle(sf::Text::Bold);
	playButton.setDescriptionPosition(sf::Vector2f(200, 0));
	playButton.setIndex(10);

	optionButton = Button(Textures::MainMenuOptionsButton, Fonts::MenuButtons, sf::Vector2f(), "Go to options menu");
	optionButton.setPosition(sf::Vector2f(960, 550));
	optionButton.setOrigin(ButtonOrigin::Center);
	optionButton.setTextStyle(sf::Text::Bold);
	optionButton.setDescriptionStyle(sf::Text::Bold);
	optionButton.setDescriptionPosition(sf::Vector2f(200, 0));
	optionButton.setIndex(10);
	optionButton.setEnabled(false);

	exitButton = Button(Textures::MainMenuQuitButton, Fonts::MenuButtons, sf::Vector2f(), "Exit the game");
	exitButton.setPosition(sf::Vector2f(900, 810));
	exitButton.setOrigin(ButtonOrigin::Center);
	exitButton.setTextStyle(sf::Text::Bold);
	exitButton.setDescriptionStyle(sf::Text::Bold);
	exitButton.setDescriptionPosition(sf::Vector2f(200, 0));
	exitButton.setIndex(10);

	mTimePassed = sf::Time::Zero;
	mAnimateAxe = false;
	mPlay = false;
	mQuit = false;
}

void MainMenuPanel::unload()
{
	RMI.unload(Fonts::MenuButtons);
	RMI.unload(Textures::MainMenuPlayButton);
	RMI.unload(Textures::MainMenuOptionsButton);
	RMI.unload(Textures::MainMenuQuitButton);
	RMI.unload(Textures::MainMenuBackground);
	RMI.unload(Textures::AxeAnimation);
	AudioPlayer::stopMusic("mainMenu");
}

void MainMenuPanel::update(sf::Time frameTime)
{
	mCurrentEvent = MenuEvent::NONE;
	if (!mAnimateAxe)
	{
		playButton.update();
		optionButton.update();
		exitButton.update();
	}

	if (mAnimateAxe)
	{
		mTimePassed += frameTime;

		if (mTimePassed >= mAnimationTime)
		{
			mTimePassed = sf::Time::Zero;
			
			if (mPlay)
				mCurrentEvent = MenuEvent::NewGamePressed;
			else if (mQuit)
				mCurrentEvent = MenuEvent::ExitGamePressed;
		}
	}

	if (mAnimateAxe)
		mAxeAnimation.animate(frameTime);

	if (playButton.isClicked())
	{
		mPlay = true;
		mAnimateAxe = true;
		mAxeAnimation.setPosition(sf::Vector2f(1200, 500));
	}
	else if (exitButton.isClicked())
	{
		mQuit = true;
		mAnimateAxe = true;
		mAxeAnimation.setPosition(sf::Vector2f(1100, 1000));
	}
}

void MainMenuPanel::render(IndexRenderer &iRenderer)
{
	playButton.render(iRenderer);
	optionButton.render(iRenderer);
	exitButton.render(iRenderer);
	iRenderer.addSprite(mBackground, 0);
	if (mAnimateAxe)
		mAxeAnimation.render(iRenderer);
}

MenuEvent MainMenuPanel::getEvent()
{
	return mCurrentEvent;
}