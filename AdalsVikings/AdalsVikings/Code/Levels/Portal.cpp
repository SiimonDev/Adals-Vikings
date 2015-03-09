#include "Portal.h"
#include "..\Logics\MouseState.h"
#include "..\Logics\PathFinder.h"
#include "..\Logics\ResourceManager.h"
#include "..\Logics\Debug.h"
#include "..\Logics\KeyboardState.h"
#include "..\Dialog\PlayerMonologue.h"
#include <iostream>

Portal::Portal(LevelFolder::ID levelID, sf::Vector2f area, sf::Vector2f position, sf::Vector2f portalMovement, sf::Vector2f mPlayerSpawn)
	: mArea(area)
	, mIsActive(false)
	, mSwitchPortal(false)
	, mWalkable(false)
	, mWorking(false)
	, mPortalMovement(portalMovement)
	, mPlayerSpawn(mPlayerSpawn)
	, mCurrentLevel(levelID)
{
	mArea.setPosition(position);
	mArea.setFillColor(sf::Color(255, 0, 0, 50));
}

void Portal::render(IndexRenderer &iRenderer)
{
	if (DebugMode)
		iRenderer.addShape(mArea, 99999);
}

void Portal::update(sf::Time &frametime, Player &player)
{
	setActive();
}

void Portal::load()
{
}

void Portal::unload()
{
	mIsActive = false;
	mSwitchPortal = false;
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
	if (isInside())
		MouseState::setCursorType(CursorType::Arrow);
	if (isInside() && MouseState::isClicked(sf::Mouse::Left))
		mIsActive = true;
	else if (MouseState::isClicked(sf::Mouse::Left))
		mIsActive = false;
}

void Portal::setActivate(bool value)
{
	mSwitchPortal = value;
	mIsActive = value;
}
void Portal::setWorking(bool value)
{
	mWorking = value;
}
void Portal::portalTravel(Player &player)
{
	if (player.getSprite().getPosition().x > mArea.getGlobalBounds().left
		&& player.getSprite().getPosition().x < mArea.getGlobalBounds().left + mArea.getGlobalBounds().width
		&& player.getSprite().getPosition().y > mArea.getGlobalBounds().top
		&& player.getSprite().getPosition().y < mArea.getGlobalBounds().top + mArea.getGlobalBounds().height
		&& mIsActive == true)
	{
		if (mWorking)
		{
			mSwitchPortal = true;
			player.setPosition(mConnectedPortal->getSpawn());
			mConnectedPortal->setWalkable(true);
		}
		else
		{
			Dialog dialog = Dialog(mCannotDialogue, 2);
			PlayerMonologueI.displayDialog(dialog);
		}
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
void Portal::setCannotDialogue(std::string string)
{
	mCannotDialogue = string;
}

bool Portal::getWalkAble()
{
	return mWalkable;
}

bool Portal::isInside()
{
	return
		(MouseState::getMousePosition().x < mArea.getGlobalBounds().left + mArea.getGlobalBounds().width
		&& MouseState::getMousePosition().x > mArea.getGlobalBounds().left
		&& MouseState::getMousePosition().y > mArea.getGlobalBounds().top
		&& MouseState::getMousePosition().y < mArea.getGlobalBounds().top + mArea.getGlobalBounds().height);
}

bool Portal::getWorking()
{
	return mWorking;
}

bool Portal::getActivated()
{
	return mSwitchPortal;
}

sf::Vector2f &Portal::getSpawn()
{
	return mPlayerSpawn;
}

LevelFolder::ID Portal::getCurrentLevel()
{
	return mCurrentLevel;
}

LevelFolder::ID Portal::getConnectedLevel()
{
	return mConnectedPortal->getCurrentLevel();
}