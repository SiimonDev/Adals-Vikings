#include "PlayPanel.h"


PlayPanel::PlayPanel()
{
	mCurrentEvent = MenuEvent::NONE;

	mIndex = 100;
}

void PlayPanel::load()
{
	RMI.loadResource(Texture::PlayMenuNewGameButton);
	RMI.loadResource(Texture::PlayMenuLoadGameButton);
	RMI.loadResource(Texture::PlayMenuMenuButton);

	RMI.loadResource(Texture::PlayMenuBackground);
	mBackground.setTexture(RMI.getResource(Texture::PlayMenuBackground));
	mBackground.setPosition(0, 0);

	newGameButton = Button(Texture::PlayMenuNewGameButton, sf::Vector2f());
	newGameButton.setPosition(sf::Vector2f(275, 710));
	newGameButton.setOrigin(ButtonOrigin::Center);
	newGameButton.setIndex(mIndex + 1);

	loadButton = Button(Texture::PlayMenuLoadGameButton, sf::Vector2f());
	loadButton.setPosition(sf::Vector2f(905, 715));
	loadButton.setOrigin(ButtonOrigin::Center);
	loadButton.setIndex(mIndex + 1);

	menuButton = Button(Texture::PlayMenuMenuButton, sf::Vector2f());
	menuButton.setPosition(sf::Vector2f(1540, 720));
	menuButton.setOrigin(ButtonOrigin::Center);
	menuButton.setIndex(mIndex + 1);
}

void PlayPanel::unload()
{
	RMI.unloadResource(Texture::PlayMenuNewGameButton);
	RMI.unloadResource(Texture::PlayMenuLoadGameButton);
	RMI.unloadResource(Texture::PlayMenuMenuButton);

	RMI.unloadResource(Texture::PlayMenuBackground);
}

void PlayPanel::update(sf::Time frameTime)
{
	mCurrentEvent = MenuEvent::NONE;
	newGameButton.update();
	loadButton.update();
	menuButton.update();

	if (newGameButton.isClicked())
	{
		mCurrentEvent = MenuEvent::NewGamePressed;
	}
	else if (loadButton.isClicked())
	{
		mCurrentEvent = MenuEvent::LoadGamePressed;
	}
	else if (menuButton.isClicked())
	{
		mCurrentEvent = MenuEvent::BackToMenuPressed;
	}
}

void PlayPanel::render(IndexRenderer &iRenderer)
{
	newGameButton.render(iRenderer);
	loadButton.render(iRenderer);
	menuButton.render(iRenderer);
	iRenderer.addSprite(mBackground, mIndex);
}

MenuEvent PlayPanel::getEvent()
{
	return mCurrentEvent;
}