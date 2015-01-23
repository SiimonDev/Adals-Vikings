#pragma once
#include "Level.h"
class TestLevel : public Level
{
public:
	TestLevel();
	~TestLevel();

	void update(sf::Time &frametime);
	void render(sf::RenderWindow &window);
	void load();
	void unload();

private:
	sf::RectangleShape mRectangle;
};

