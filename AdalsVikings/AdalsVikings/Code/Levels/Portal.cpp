#include "Portal.h"
#include "..\Logics\MouseState.h"
#include "..\Logics\PathFinder.h"
#include "..\Logics\ResourceManager.h"
#include "..\Logics\KeyboardState.h"
#include <iostream>

Portal::Portal(sf::Vector2f area, sf::Vector2f position, sf::Vector2f portalMovement, sf::Vector2f mPlayerSpawn, Portal *portal)
	: mIsActive(false)
	, mSwitchPortal(false)
	, mRenderPortal(false)
	, mWalkable(false)
	, mArea(area)
	, mConnectedPortal(portal)
	, mPortalMovement(portalMovement)
	, mPlayerSpawn(mPlayerSpawn)
{
	mArea.setPosition(position);
	mArea.setFillColor(sf::Color(255, 0, 0, 50));
}
Portal::Portal(sf::Vector2f area, sf::Vector2f position, sf::Vector2f portalMovement, sf::Vector2f mPlayerSpawn)
	: mArea(area)
	, mIsActive(false)
	, mSwitchPortal(false)
	, mWalkable(false)
	, mPortalMovement(portalMovement)
	, mPlayerSpawn(mPlayerSpawn)
{
	mArea.setPosition(position);
	mArea.setFillColor(sf::Color(255, 0, 0, 50));
}

void Portal::render(IndexRenderer &iRenderer)
{
	if (mRenderPortal)
		iRenderer.addRectangle(mArea, 99999);
}

void Portal::update(sf::Time &frametime, Player &player)
{
	if (KeyboardState::isPressed(sf::Keyboard::F1))
		mRenderPortal = !mRenderPortal;
	setActive();
}

void Portal::load()
{
}

void Portal::unload()
{
	mIsActive = false;
	mSwitchPortal = false;
	mConnectedPortal = 0;
}

void Portal::setGateway(Portal *portal2)
{
	mConnectedPortal = portal2;
}

void Portal::setArea(sf::Vector2f &area)
{
	mArea.setSize(area);
}

void Portal::setPosition(sf::Vector2f &position)
{
	mArea.setPosition(position);
}

void Portal::setActive()
{
	if (MouseState::getMousePosition().x < mArea.getGlobalBounds().left + mArea.getGlobalBounds().width
		&& MouseState::getMousePosition().x > mArea.getGlobalBounds().left
		&& MouseState::getMousePosition().y > mArea.getGlobalBounds().top
		&& MouseState::getMousePosition().y < mArea.getGlobalBounds().top + mArea.getGlobalBounds().height
		&& MouseState::isClicked(sf::Mouse::Left))
	{
		mIsActive = true;
	}
	else if (MouseState::isClicked(sf::Mouse::Left))
	{
		mIsActive = false;
	}
}

void Portal::setActivate(bool value)
{
	mSwitchPortal = value;
	mIsActive = value;
}

void Portal::portalTravel(Player &player)
{
	if (player.getSprite().getPosition().x > mArea.getGlobalBounds().left
		&& player.getSprite().getPosition().x < mArea.getGlobalBounds().left + mArea.getGlobalBounds().width
		&& player.getSprite().getPosition().y > mArea.getGlobalBounds().top
		&& player.getSprite().getPosition().y < mArea.getGlobalBounds().top + mArea.getGlobalBounds().height
		&& mIsActive == true)
	{
		mSwitchPortal = true;
		player.setPosition(mConnectedPortal->getSpawn());
		mConnectedPortal->setWalkable(true);
	}
}

void Portal::walkPath(Player &player)
{
	player.walkPath(PathFinder::getPath(player.getPosition(), mPortalMovement));
	setWalkable(false);
}

void Portal::setWalkable(bool value)
{
	mWalkable = value;
}

bool &Portal::getWalkAble()
{
	return mWalkable;
}

bool &Portal::getActivated()
{
	return mSwitchPortal;
}

sf::Vector2f &Portal::getSpawn()
{
	return mPlayerSpawn;
}