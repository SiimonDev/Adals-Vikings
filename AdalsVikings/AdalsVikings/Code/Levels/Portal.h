#pragma once
#include "..\Objects\Player.h"
#include "..\Logics\PathFinder.h"
#include "..\Logics\IndexRenderer.h"
#include "..\Logics\ResourceManager.h"
#include <SFML\Graphics.hpp>

class Portal
{
public:
	Portal(LevelFolder::ID levelID, sf::Vector2f area, sf::Vector2f position, sf::Vector2f portalMovement, sf::Vector2f mPlayerSpawn);

	void render(IndexRenderer &iRenderer);
	void update(sf::Time &frametime, Player &player);
	void load();
	void unload();
	void setGateway(Portal *portal);
	void setArea(sf::Vector2f &area);
	void setPosition(sf::Vector2f &position);
	void setWalkable(bool value);
	void setActivate(bool value);
	void setActive();
	void portalTravel(Player &player);
	void walkPath(Player &player);
	void setCannotDialogue(std::string string);
	void setWorking(bool value);

	bool getActivated();
	bool getWorking();
	bool getWalkAble();
	bool isInside();
	sf::Vector2f &getSpawn();

	LevelFolder::ID getCurrentLevel();
	LevelFolder::ID getConnectedLevel();

private:
	Portal* mConnectedPortal;
	std::string mCannotDialogue;
	sf::RectangleShape mArea;
	sf::Vector2f mPortalMovement, mPlayerSpawn;

	LevelFolder::ID mCurrentLevel;

	bool mIsActive, mSwitchPortal, mWalkable, mWorking;
};