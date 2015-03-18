#include "MouseState.h"
#include "WindowState.h"
#include "ResourceManager.h"
#include <iostream>
#include <map>

#define MouseSize int(5)

static bool hasFocus;

static std::map<int, bool> buttonStates;
static std::map<int, bool> oldButtonStates;
static std::map<int, double> timeDown;

static sf::Sprite* mSprite;

void MouseState::initialize()
{
	CurrentWindow.pushGLStates();
	RMI.loadResource(Texture::CursorDefault);
	RMI.loadResource(Texture::CursorArrow);
	mSprite = new sf::Sprite();
	mSprite->setTexture(RMI.getResource(Texture::CursorDefault));

	for (size_t i = 0; i <= MouseSize; i++)
	{
		buttonStates.insert(std::make_pair(i, false));
		oldButtonStates.insert(std::make_pair(i, false));
		timeDown.insert(std::make_pair(i, 0));
	}
	hasFocus = true;
	CurrentWindow.popGLStates();
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

	if (isClicked(sf::Mouse::Left))
		std::cout << "MousePosition: X:" << getMousePosition().x << "	Y:" << getMousePosition().y << std::endl;

	mSprite->setPosition(sf::Vector2f(getMousePosition()));
}

void MouseState::render()
{
	CurrentWindow.draw(*mSprite);
}

void MouseState::setCursorType(CursorType::ID id, float rotation)
{
	delete mSprite;
	mSprite = new sf::Sprite;
	if (id == CursorType::Default)
	{
		mSprite->setTexture(RMI.getResource(Texture::CursorDefault));
	}
	else if (id == CursorType::Arrow)
	{
		mSprite->setTexture(RMI.getResource(Texture::CursorArrow));
		mSprite->setOrigin(mSprite->getTextureRect().width / 2, mSprite->getTextureRect().height / 2);
		mSprite->setRotation(rotation);
	}
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
	sf::Vector2i mousePos = sf::Mouse::getPosition(CurrentWindow);
	sf::Vector2f letterBoxScale = getLetterboxScale(CurrentWindow.getView(), CurrentWindow.getSize().x, CurrentWindow.getSize().y);

	float virtualRenderWidth = 1920; //mWindow->getView().getSize().x;
	float virtualRenderHeight = 1080; //mWindow->getView().getSize().y;

	float blackXBarSize = CurrentWindow.getSize().x * letterBoxScale.x;
	float blackYBarSize = CurrentWindow.getSize().y * letterBoxScale.y;

	float physicalRenderWidth = CurrentWindow.getSize().x - (blackXBarSize * 2);
	float physicalRenderHeight = CurrentWindow.getSize().y - (blackYBarSize * 2);

	sf::Vector2f scale;
	scale.x = virtualRenderWidth / physicalRenderWidth;
	scale.y = virtualRenderHeight / physicalRenderHeight;

	/*std::cout << "X: " << (mousePos.x - blackXBarSize) * scale2.x << std::endl;
	std::cout << "Y: " << (mousePos.y - blackYBarSize) * scale2.x << std::endl;*/
	return sf::Vector2i((mousePos.x - blackXBarSize) * scale.x, (mousePos.y - blackYBarSize) * scale.y);
}

bool MouseState::isClicked(sf::Mouse::Button button)
{
	if (hasFocus)
		return (buttonStates[button] && !oldButtonStates[button]);
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