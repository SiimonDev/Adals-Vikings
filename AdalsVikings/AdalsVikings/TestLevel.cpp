#include "TestLevel.h"
#include <iostream>

TestLevel::TestLevel()
{
	load();
}


TestLevel::~TestLevel()
{
}

void TestLevel::update(sf::Time &frametime)
{
	mRectangle.move(100 * frametime.asSeconds(), 0);
}
void TestLevel::render(sf::RenderWindow &window)
{
	window.draw(mRectangle);
}
void TestLevel::load()
{
	
}
void TestLevel::unload()
{
	
}