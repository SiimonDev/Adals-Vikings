#pragma once
#include "..\Objects\Player.h"
#include "..\Logics\PathFinder.h"
#include "..\Logics\IndexRenderer.h"
#include <SFML\Graphics.hpp>

class Portal
{
public:
	Portal(sf::Vector2f area, sf::Vector2f position, sf::Vector2f portalMovement, sf::Vector2f mPlayerSpawn);
	Portal(sf::Vector2f area, sf::Vector2f position, sf::Vector2f portalMovement, sf::Vector2f mPlayerSpawn, Portal *portal);

	void render(IndexRenderer &iRenderer);
	void update(sf::Time &frametime, Player &player);
	void unload();
	void setGateway(Portal *portal);
	void setArea(sf::Vector2f &area);
	void setPosition(sf::Vector2f &position);
	void setWalkable(bool value);
	void setActivate(bool value);
	void setActive();
	void portalTravel(Player &player);
	void walkPath(Player &player);

	bool &getActivated();
	bool &getWalkAble();
	sf::Vector2f &getSpawn();

private:
	sf::RectangleShape mArea;
	Portal* mConnectedPortal;

	bool mIsActive, mSwitchPortal, mWalkable;
	sf::Vector2f mPortalMovement, mPlayerSpawn;
};

