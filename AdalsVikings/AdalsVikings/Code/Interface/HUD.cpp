#include "HUD.h"
#include "..\Logics\WindowState.h"
#include "..\Logics\ResourceManager.h"

HUD::HUD()
{
}

void HUD::load()
{
	RMI.loadResource(Texture::Button1);
	RMI.loadResource(Font::Font1);
	RMI.loadResource(Texture::IntroScreen);

	mHelpPanel.setTexture(RMI.getResource(Texture::IntroScreen));
	mHelpPanel.setScale(2, 2);
	mHelpPanel.setPosition(150, 50);

	mInventoryButton = Button(Texture::Button1, Font::Font1, sf::Vector2f(), " Toggle Inventory");
	mInventoryButton.setPosition(sf::Vector2f(10, 10));
	mInventoryButton.setDescriptionPosition(sf::Vector2f(0, 60));
	mInventoryButton.setScale(sf::Vector2f(1.0f, 1.0f));
	mInventoryButton.setDescriptionStyle(sf::Text::Bold);
	mInventoryButton.setIndex(99999);

	mHelpButton = Button(Texture::Button1, Font::Font1, sf::Vector2f(), " Help");
	mHelpButton.setPosition(sf::Vector2f(100, 10));
	mHelpButton.setDescriptionPosition(sf::Vector2f(0, 60));
	mHelpButton.setScale(sf::Vector2f(1.0f, 1.0f));
	mHelpButton.setDescriptionStyle(sf::Text::Bold);
	mHelpButton.setIndex(99999);

	mOKButton = Button(Texture::Button1, Font::Font1, "OK", sf::Vector2f(), " I Understand");
	mOKButton.setPosition(sf::Vector2f(1700, 900));
	mOKButton.setDescriptionPosition(sf::Vector2f(0, 60));
	mOKButton.setScale(sf::Vector2f(2.0f, 2.0f));
	mOKButton.setOrigin(ButtonOrigin::Center);
	mOKButton.setDescriptionStyle(sf::Text::Bold);
	mOKButton.setIndex(99999);
}
void HUD::unload()
{
	RMI.unloadResource(Texture::Button1);
	RMI.unloadResource(Font::Font1);
}
void HUD::update(sf::Time frameTime)
{
	if (mDisplayHelp)
	{
		mOKButton.update();
		if (mOKButton.isReleased())
			mDisplayHelp = false;
	}
	else
	{
		mInventoryButton.update();
		mHelpButton.update();

		if (isHelpButtonReleased())
			mDisplayHelp = true;
	}
}
void HUD::render(IndexRenderer &iRenderer)
{
	if (mDisplayHelp)
	{
		mOKButton.render(iRenderer);
		iRenderer.addSprite(mHelpPanel, 99998);
	}
	else
	{
		mInventoryButton.render(iRenderer);
		mHelpButton.render(iRenderer);
	}
}

void HUD::displayHelp(bool value)
{
	mDisplayHelp = value;
}

bool HUD::isInventoryButtonReleased()
{
	return mInventoryButton.isReleased();
}

bool HUD::isHelpButtonReleased()
{
	return mHelpButton.isReleased();
}

bool HUD::isButtonClicked()
{
	return mInventoryButton.isClicked() || mHelpButton.isClicked();
}

bool HUD::isButtonPressed()
{
	return mInventoryButton.isPressed() || mHelpButton.isPressed();
}

bool HUD::isButtonReleased()
{
	return mInventoryButton.isReleased() || mHelpButton.isReleased();
}