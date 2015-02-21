#include "MouseState.h"
#include <iostream>
#include <map>

#define MouseSize int(5)

static sf::RenderWindow *mWindow;
static bool hasFocus;

static std::map<int, bool> buttonStates;
static std::map<int, bool> oldButtonStates;
static std::map<int, double> timeDown;

void MouseState::initialize(sf::RenderWindow &window)
{
	for (size_t i = 0; i <= MouseSize; i++)
	{
		buttonStates.insert(std::make_pair(i, false));
		oldButtonStates.insert(std::make_pair(i, false));
		timeDown.insert(std::make_pair(i, 0));
	}

	mWindow = &window;
	hasFocus = true;
}

void MouseState::update(sf::Time frameTime)
{
	for (size_t i = 0; i <= MouseSize; i++)
	{
		oldButtonStates[i] = buttonStates[i];

		if (oldButtonStates[i])
			timeDown[i] += frameTime.asSeconds();
		else
			timeDown[i] = 0;
	}
	for (int i = 0; i <= MouseSize; i++)
		buttonStates[i] = sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(i));
}

void MouseState::checkEvents(sf::Event::EventType event)
{
	if (event == sf::Event::LostFocus)
		hasFocus = false;
	else if (event == sf::Event::GainedFocus)
		hasFocus = true;
}

sf::Vector2f getLetterboxScale(sf::View view, int windowWidth, int windowHeight)
{
	float windowRatio = windowWidth / (float)windowHeight;
	float viewRatio = view.getSize().x / (float)view.getSize().y;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	bool horizontalSpacing = true;
	if (windowRatio < viewRatio)
		horizontalSpacing = false;

	if (horizontalSpacing) 
	{
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.0;
	}
	else 
	{
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.0;
	}

	return sf::Vector2f(posX, posY);
}

sf::Vector2i MouseState::getMousePosition()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*mWindow);
	sf::Vector2f letterBoxScale = getLetterboxScale(mWindow->getView(), mWindow->getSize().x, mWindow->getSize().y);

	float virtualRenderWidth = mWindow->getView().getSize().x;
	float virtualRenderHeight = mWindow->getView().getSize().y;

	float blackXBarSize = mWindow->getSize().x * letterBoxScale.x;
	float blackYBarSize = mWindow->getSize().y * letterBoxScale.y;

	float physicalRenderWidth = mWindow->getSize().x - (blackXBarSize * 2);
	float physicalRenderHeight = mWindow->getSize().y - (blackYBarSize * 2);

	sf::Vector2f scale;
	scale.x = virtualRenderWidth / physicalRenderWidth;
	scale.y = virtualRenderHeight / physicalRenderHeight;

	//std::cout << "X: " << (mousePos.x - blackXBarSize) * scale2.x << std::endl;
	//std::cout << "Y: " << (mousePos.y - blackYBarSize) * scale2.x << std::endl;
	return sf::Vector2i((mousePos.x - blackXBarSize) * scale.x, (mousePos.y - blackYBarSize) * scale.y);
}

bool MouseState::isClicked(sf::Mouse::Button button)
{
	if (hasFocus)
	{
		if (buttonStates[button] && !oldButtonStates[button])
		{
			std::cout << "MousePosition: X:" << getMousePosition().x << "	Y:" << getMousePosition().y << std::endl;
			return true;
		}
	}
	return false;
}

bool MouseState::isReleased(sf::Mouse::Button button)
{
	if (hasFocus)
		return (!buttonStates[button] && oldButtonStates[button]);

	return false;
}

bool MouseState::isReleased(sf::Mouse::Button button, double seconds)
{
	if (hasFocus)
	{
		if (!buttonStates[button] && oldButtonStates[button])
			return (timeDown.at(button) <= seconds);
	}
	return false;
}

bool MouseState::isPressed(sf::Mouse::Button button, double seconds)
{
	if (hasFocus)
	{
		if (buttonStates[button])
			return (timeDown.at(button) >= seconds);
	}
	return false;
}