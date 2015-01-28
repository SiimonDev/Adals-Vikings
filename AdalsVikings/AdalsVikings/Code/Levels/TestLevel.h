#pragma once
#include "Level.h"

class TestLevel : public Level
{
public:
	TestLevel();
	~TestLevel();

	void update(sf::Time &frametime);
	void render(IndexRenderer &iRenderer);
	void load();
	void unload();
	//Portal& getPortal();

private:
	sf::Sprite mSprite;
};

