#include "Level_Cliffs_Down.h"
#include <iostream>

Level_Cliffs_Down::Level_Cliffs_Down(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Cliffs_Down;
}

void Level_Cliffs_Down::restartSounds()
{

}

void Level_Cliffs_Down::update(sf::Time &frametime)
{
	mWaveAnimation.animate(frametime);
	mWaveAnimationIdle.animate(frametime);
	Level::update(frametime);
	changeLevel();
}

void Level_Cliffs_Down::render(IndexRenderer &iRenderer)
{
	if (mWaveAnimation.getCurrentFrame() == 0)
		mWaveAnimationIdle.render(iRenderer);
	else
		mWaveAnimation.render(iRenderer);
	Level::render(iRenderer);
}

void Level_Cliffs_Down::load()
{
	Level::load();

	RMI.loadResource(Texture::WaveAnimationCliffs);
	mWaveAnimation.load(RMI.getResource(Texture::WaveAnimationCliffs), sf::Vector2i(5, 10), sf::seconds(8), sf::seconds(7), true);
	mWaveAnimation.setIndex(4);
	mWaveAnimation.setProportions(sf::Vector2f(1940, 1120));
	mWaveAnimation.getSprite().setOrigin(mWaveAnimation.getSprite().getTextureRect().width, mWaveAnimation.getSprite().getTextureRect().height);
	mWaveAnimation.setPadding(2);
	mWaveAnimation.setPosition(sf::Vector2f(1920 + 20, 1080 + 20));

	RMI.loadResource(Texture::WaveAnimationCliffsIdle);
	mWaveAnimationIdle.load(RMI.getResource(Texture::WaveAnimationCliffsIdle), sf::Vector2i(5, 1), sf::seconds(1), sf::seconds(0), true);
	mWaveAnimationIdle.setIndex(4);
	mWaveAnimationIdle.setProportions(sf::Vector2f(1940, 1120));
	mWaveAnimationIdle.getSprite().setOrigin(mWaveAnimation.getSprite().getTextureRect().width, mWaveAnimation.getSprite().getTextureRect().height);
	mWaveAnimationIdle.setPadding(2);
	mWaveAnimationIdle.setPosition(sf::Vector2f(1920 + 20, 1080 + 20));
}

void Level_Cliffs_Down::unload()
{
	Level::unload();
	RMI.unloadResource(Texture::WaveAnimationCliffs);
	RMI.unloadResource(Texture::WaveAnimationCliffsIdle);
}

void Level_Cliffs_Down::changeLevel()
{
}

void Level_Cliffs_Down::checkInteractEvents()
{

}
void Level_Cliffs_Down::checkEvents()
{

}
