#include "MainMenuPanel.h"
#include "..\..\Logics\AudioPlayer.h"
#include "..\..\Logics\fade.h"

MainMenuPanel::MainMenuPanel() :
 mAnimationTime(sf::milliseconds(750)), mTimePassed(sf::Time::Zero)
{
	mCurrentEvent = MenuEvent::NONE;
}

void MainMenuPanel::load()
{
	RMI.loadResource(Texture::MainMenuPlayButton);
	RMI.loadResource(Texture::MainMenuOptionsButton);
	RMI.loadResource(Texture::MainMenuQuitButton);
	RMI.loadResource(Texture::MainMenuBackground);
	RMI.loadResource(Texture::AxeAnimation);
	RMI.loadResource(Sound::MainMenuAxeSound);

	mRestartSounds = true;

	mBackground.setTexture(RMI.getResource(Texture::MainMenuBackground));

	mAxeAnimation.load(RMI.getResource(Texture::AxeAnimation), Frames(5, 1), sf::milliseconds(588), sf::seconds(0.1), false);
	mAxeAnimation.getSprite().setOrigin(mAxeAnimation.getSprite().getTextureRect().width, mAxeAnimation.getSprite().getTextureRect().height);
	mAxeAnimation.setProportions(sf::Vector2f(1605, 968));
	mAxeAnimation.setPosition(sf::Vector2f(1920, 1080));
	mAxeAnimation.setIdleFrame(sf::Vector2i(5, 1));
	mAxeAnimation.setIndex(50);

	playButton = Button(Texture::MainMenuPlayButton, sf::Vector2f());
	playButton.setPosition(sf::Vector2f(1010, 275));
	playButton.setOrigin(ButtonOrigin::Center);
	playButton.setTextStyle(sf::Text::Bold);
	playButton.setDescriptionStyle(sf::Text::Bold);
	playButton.setDescriptionPosition(sf::Vector2f(200, 0));
	playButton.setIndex(10);

	optionButton = Button(Texture::MainMenuOptionsButton, sf::Vector2f());
	optionButton.setPosition(sf::Vector2f(960, 550));
	optionButton.setOrigin(ButtonOrigin::Center);
	optionButton.setTextStyle(sf::Text::Bold);
	optionButton.setDescriptionStyle(sf::Text::Bold);
	optionButton.setDescriptionPosition(sf::Vector2f(200, 0));
	optionButton.setIndex(10);
	optionButton.setEnabled(false);

	exitButton = Button(Texture::MainMenuQuitButton, sf::Vector2f());
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
	RMI.unloadResource(Texture::MainMenuPlayButton);
	RMI.unloadResource(Texture::MainMenuOptionsButton);
	RMI.unloadResource(Texture::MainMenuQuitButton);
	RMI.unloadResource(Texture::MainMenuBackground);
	RMI.unloadResource(Texture::AxeAnimation);
	RMI.unloadResource(Sound::MainMenuAxeSound);
	AudioPlayer::stopHDDSound(HDDSound::Anlgian_Music);
}

void MainMenuPanel::update(sf::Time frameTime)
{
	if (mRestartSounds)
		AudioPlayer::playHDDSound(HDDSound::Anlgian_Music, true);

	mCurrentEvent = MenuEvent::NONE;
	if (!mAnimateAxe)
	{
		playButton.update();
		optionButton.update();
		exitButton.update();
	}
	else
	{
		if (!mPlaySound)
		{
			AudioPlayer::playSound(Sound::MainMenuAxeSound, "axe", false);
			mPlaySound = true;
		}
		mAxeAnimation.animate(frameTime);
	}

	if (mAnimateAxe)
	{
		mTimePassed += frameTime;

		if (mTimePassed >= mAnimationTime)
		{
			mTimePassed = sf::seconds(0);

			if (mPlay)
			{
				playButton.update();
				mAxeAnimation.restart();
				mCurrentEvent = MenuEvent::PlayPressed;
				mPlay = false;
				mPlaySound = false;
			}
			else if (mQuit)
			{
				mCurrentEvent = MenuEvent::ExitMainMenuPressed;
				mQuit = false;
			}

			mAnimateAxe = false;
		}
	}

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