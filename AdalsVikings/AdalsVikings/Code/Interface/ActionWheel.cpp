#include "ActionWheel.h"

ActionWheel::ActionWheel()
{
	button1Position = sf::Vector2f(-100, 100);
	button2Position = sf::Vector2f(-100, 0);
	button3Position = sf::Vector2f(-100, -100);
}

ActionWheel::~ActionWheel()
{
}

void ActionWheel::load()
{
	ResourceManager::GetInstance().load(Textures::Button1, "Assets/Images/Buttons/Button1.png");
	button1 = Button(Textures::Button1, sf::Vector2f());
	button2 = Button(Textures::Button1, sf::Vector2f());
	button3 = Button(Textures::Button1, sf::Vector2f());
	button1.setScale(sf::Vector2f(1, 1));
	button2.setScale(sf::Vector2f(1, 1));
	button3.setScale(sf::Vector2f(1, 1));
}

void ActionWheel::unload()
{
	ResourceManager::GetInstance().unload(Textures::Button1);
}

void ActionWheel::update()
{
	if (mouseState.isDown(sf::Mouse::Left, 1))
	{
		mIsActive = true;
	}

	if (mouseState.isReleased(sf::Mouse::Left))
	{
		mIsActive = false;
	}

	if (mIsActive)
	{
		button1.update();
		button2.update();
		button3.update();
	}
	else
	{
		mPosition = sf::Vector2f(MouseState::getMousePosition());
		button1.setPosition(mPosition + button1Position);
		button2.setPosition(mPosition + button2Position);
		button3.setPosition(mPosition + button3Position);
	}
}

void ActionWheel::render(IndexRenderer &iRenderer)
{
	if (mIsActive)
	{
		button1.render(iRenderer);
		button2.render(iRenderer);
		button3.render(iRenderer);
	}
}