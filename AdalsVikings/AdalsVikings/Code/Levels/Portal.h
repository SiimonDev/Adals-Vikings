#pragma once
#include "SFML\Graphics.hpp"
#include "..\Objects\Player.h"
#include <map>
#include <memory>

class Portal
{
public:
	Portal();
	Portal(Portal *portal);
	Portal(sf::Vector2f area, sf::Vector2f position);
	Portal(sf::Vector2f area, sf::Vector2f position, Portal *portal);
	~Portal();

	void render(sf::RenderWindow &window);
	void update(sf::Time &frametime, Player &player);
	void setGateway(Portal *portal);
	void setArea(sf::Vector2f area);
	void setPosition(sf::Vector2f position);
	bool setRightWorld(bool value);
	void setActive();
	void playerCollision(Player &player);

	sf::Vector2f getPosition();

private:
	sf::RectangleShape mArea;
	TileMap mTileMap;
	Portal* mConnectedPortal;
	bool mIsActive, mSwitchPortal, mRightWorld;
};

