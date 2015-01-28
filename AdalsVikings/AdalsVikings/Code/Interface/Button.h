#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "..\Logics\ISprite.h"
#include "..\Logics\IndexRenderer.h"
#include "..\Logics\ResourceManager.h"
#include "..\Logics\MouseState.h"

class Button
{
public:
	Button();
	Button(Textures::ID id, sf::Vector2f position, std::string description = "");
	Button(Textures::ID id, std::string text, sf::Vector2f position, std::string description = "");

	void setPosition(sf::Vector2f &pos);
	void setScale(sf::Vector2f &scale);
	void update();
	void render(IndexRenderer &iRenderer);

private:
	void setSprites(Textures::ID id);
	bool isInsideButton(sf::Vector2i &pos);

	std::string mText;
	std::string mDescription;
	sf::Vector2f mPosition;
	sf::Vector2f mScale;
	sf::Vector2i mSize;

	mv::ISprite currentSprite;
	mv::ISprite mHoverSprite;
	mv::ISprite mIdleSprite;
	mv::ISprite mClickSprite;

	MouseState mouseState;
};