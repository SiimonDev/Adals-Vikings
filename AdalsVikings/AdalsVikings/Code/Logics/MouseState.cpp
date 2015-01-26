#include "MouseState.h"
#include <iostream>

static sf::RenderWindow *mWindow;
static double virtualWidth;
static double virtualHeight;

sf::Vector2f scale;

MouseState &MouseState::getInstance(){
	static MouseState instance;
	return instance;
}

MouseState::MouseState(){
}

void MouseState::initialize(sf::RenderWindow &window){
	mWindow = &window;
}

sf::Vector2i MouseState::getMousePosition(){
	sf::Vector2i mousePos = sf::Mouse::getPosition(*mWindow);

	virtualWidth = mWindow->getView().getSize().x;
	virtualHeight = mWindow->getView().getSize().y;

	scale.x = virtualWidth / mWindow->getSize().x;
	scale.y = virtualHeight / mWindow->getSize().y;

	return sf::Vector2i(mousePos.x * scale.x, mousePos.y * scale.y);
}