#include "Portal.h"
#include "..\Logics\MouseState.h"
#include "..\Logics\LevelManager.h"
#include <iostream>
#include "..\Logics\PathFinder.h"
#include "TileMap.h"

Portal::Portal()
	: mIsActive(false)
	, mSwitchPortal(false)
	, mRightWorld(false)
{
	mArea.setFillColor(sf::Color::Red);
}
Portal::Portal(Portal *portal)
	: mIsActive(false)
	, mSwitchPortal(false)
	, mRightWorld(false)
	, mConnectedPortal(portal)
{
	mArea.setFillColor(sf::Color::Red);
}
Portal::Portal(sf::Vector2f area, sf::Vector2f position, Portal *portal)
	: mIsActive(false)
	, mSwitchPortal(false)
	, mRightWorld(false)
	, mArea(area)
	, mConnectedPortal(portal)
{
	mArea.setPosition(position);
	mArea.setFillColor(sf::Color::Red);
}
Portal::Portal(sf::Vector2f area, sf::Vector2f position)
	: mArea(area)
	, mIsActive(false)
	, mSwitchPortal(false)
	, mRightWorld(false)
{
	mArea.setPosition(position);
	mArea.setFillColor(sf::Color::Red);
}


Portal::~Portal()
{
}

void Portal::render(sf::RenderWindow &window)
{
	window.draw(mArea);
}
void Portal::update(sf::Time &frametime, Player &player)
{
	setActive();
	playerCollision(player);
}
void Portal::setGateway(Portal *portal2)
{
	mConnectedPortal = portal2;
}
void Portal::setArea(sf::Vector2f area)
{
	mArea.setSize(area);
}
void Portal::setPosition(sf::Vector2f position)
{
	mArea.setPosition(position);
}
void Portal::setActive()
{
	if (MouseState::getInstance().getMousePosition().x < mArea.getGlobalBounds().left + mArea.getGlobalBounds().width
		&& MouseState::getInstance().getMousePosition().x > mArea.getGlobalBounds().left
		&& MouseState::getInstance().getMousePosition().y > mArea.getGlobalBounds().top
		&& MouseState::getInstance().getMousePosition().y < mArea.getGlobalBounds().top + mArea.getGlobalBounds().height
		&& sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mIsActive = true;
	}
	else if ((MouseState::getInstance().getMousePosition().x > mArea.getGlobalBounds().left + mArea.getGlobalBounds().width
		|| MouseState::getInstance().getMousePosition().x < mArea.getGlobalBounds().left
		|| MouseState::getInstance().getMousePosition().y > mArea.getGlobalBounds().top
		|| MouseState::getInstance().getMousePosition().y < mArea.getGlobalBounds().top + mArea.getGlobalBounds().height)
		&& sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mIsActive = false;
	}

}
void Portal::playerCollision(Player &player)
{
	if (player.getPosition().x > mArea.getGlobalBounds().left
		&& player.getPosition().x < mArea.getGlobalBounds().left + mArea.getGlobalBounds().width
		&& player.getPosition().y > mArea.getGlobalBounds().top
		&& player.getPosition().y < mArea.getGlobalBounds().top + mArea.getGlobalBounds().height
		&& mIsActive == true)
	{
		mSwitchPortal = true;
		std::cout << "It's Working!" << std::endl;
		player.setPosition(mConnectedPortal->getPosition());
		
		std::cout << player.getPosition().x << " " << player.getPosition().y << std::endl;
	}
}
bool Portal::setRightWorld(bool value)
{
	mRightWorld = value;
	return mRightWorld;
}

sf::Vector2f Portal::getPosition()
{
	return mArea.getPosition();
}
