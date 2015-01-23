#include "TestLevel.h"


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
	mRectangle.setFillColor(sf::Color::Red);
	mRectangle.setSize(sf::Vector2f(100, 100));
	mRectangle.setPosition(sf::Vector2f(400, 300));
}
void TestLevel::unload()
{

}