#include "HUD.h"
#include "..\Logics\WindowState.h"
#include "..\Logics\ResourceManager.h"

HUD::HUD()
{
}

void HUD::load()
{
	RMI.loadResource(Texture::OKButton);
	RMI.loadResource(Texture::HelpButton);
	RMI.loadResource(Texture::InventoryButton);
	RMI.loadResource(Font::Font1);
	RMI.loadResource(Texture::IntroScreen);

	mHelpPanel.setTexture(RMI.getResource(Texture::IntroScreen));
	mHelpPanel.setScale(1, 1);
	mHelpPanel.setPosition(0, 0);

	mInventoryButton = Button(Texture::InventoryButton, Font::Font1, sf::Vector2f(), " Toggle Inventory");
	mInventoryButton.setPosition(sf::Vector2f(30, 10));
	mInventoryButton.setDescriptionPosition(sf::Vector2f(-35, 90));
	mInventoryButton.setScale(sf::Vector2f(0.5f, 0.5f));
	mInventoryButton.setDescriptionStyle(sf::Text::Bold);
	mInventoryButton.setIndex(99999);

	mHelpButton = Button(Texture::HelpButton, Font::Font1, sf::Vector2f(), "Help");
	mHelpButton.setPosition(sf::Vector2f(150, 10));
	mHelpButton.setDescriptionPosition(sf::Vector2f(0, 90));
	mHelpButton.setScale(sf::Vector2f(0.3f, 0.3f));
	mHelpButton.setDescriptionStyle(sf::Text::Bold);
	mHelpButton.setIndex(99999);

	mOKButton = Button(Texture::OKButton, Font::Font1, sf::Vector2f()/*, "I Understand"*/);
	mOKButton.setPosition(sf::Vector2f(1650, 920));
	mOKButton.setDescriptionPosition(sf::Vector2f(0, 60));
	mOKButton.setScale(sf::Vector2f(1.6f, 1.6f));
	mOKButton.setOrigin(ButtonOrigin::Center);
	mOKButton.setDescriptionStyle(sf::Text::Bold);
	mOKButton.setIndex(99999);
}
void HUD::unload()
{
	RMI.unloadResource(Texture::OKButton);
	RMI.unloadResource(Texture::HelpButton);
	RMI.unloadResource(Texture::Button1);
	RMI.unloadResource(Font::Font1);
}
void HUD::update(sf::Time frameTime)
{
	if (mDisplayHelp)
	{
		if (mOKButton.isReleased() || mHelpButton.isReleased())
			mDisplayHelp = false;

		mOKButton.update();
		mHelpButton.update();
	}
	else
	{
		if (isHelpButtonReleased())
			mDisplayHelp = true;

		mInventoryButton.update();
		mHelpButton.update();
	}
}
void HUD::render(IndexRenderer &iRenderer)
{
	if (mDisplayHelp)
	{
		mOKButton.render(iRenderer);
		iRenderer.addSprite(mHelpPanel, 99998);
	}
	mInventoryButton.render(iRenderer);
	mHelpButton.render(iRenderer);
}

void HUD::displayHelp(bool value)
{
	mDisplayHelp = value;
}

bool HUD::isHelpActive()
{
	return mDisplayHelp;
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
	return mInventoryButton.isClicked() || mHelpButton.isClicked() || mOKButton.isClicked();
}

bool HUD::isButtonPressed()
{
	return mInventoryButton.isPressed() || mHelpButton.isPressed() || mOKButton.isPressed();
}

bool HUD::isButtonReleased()
{
	return mInventoryButton.isReleased() || mHelpButton.isReleased() || mOKButton.isReleased();
}