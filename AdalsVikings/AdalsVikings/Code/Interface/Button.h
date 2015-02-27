#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "..\Logics\IndexRenderer.h"
#include "..\Logics\ResourceManager.h"
#include "..\Logics\MouseState.h"

enum ButtonOrigin{
	Center,
	UpperLeft,
};

class Button
{
public:
	Button();
	Button(Texture::ID texID, sf::Vector2f position);
	Button(Texture::ID texID, Font::ID fontID, sf::Vector2f position, std::string description = "");
	Button(Texture::ID texID, Font::ID fontID, std::string text, sf::Vector2f position, std::string description = "");

	void update();
	void render(IndexRenderer &iRenderer);

	bool isClicked();
	bool isPressed();
	bool isReleased();

	void setPosition(sf::Vector2f &pos);
	void setDescriptionPosition(sf::Vector2f &pos);
	void setScale(sf::Vector2f &scale);
	void setOrigin(ButtonOrigin origin);
	void setEnabled(bool enabled);
	void setIndex(int index);

	void setFont(Font::ID id);

	void setText(std::string text);
	void setDescription(std::string text);

	void setTextSize(int textSize);
	void setDescriptionSize(int dSize);

	void setTextStyle(sf::Text::Style style);
	void setDescriptionStyle(sf::Text::Style style);

	void setTextColor(sf::Color color);
	void setDescriptionColor(sf::Color color);

private:
	void setTextStuff(Font::ID fontID, std::string text, std::string description);
	void setSprites(Texture::ID id);
	bool isInsideButton(sf::Vector2i &pos);

	bool mIsPressed;
	bool mIsReleased;
	bool mIsClicked;
	bool mShowDescription;
	bool mEnabled;

	int mIndex;
	int mTextSize;
	int mDescriptionSize;

	ButtonOrigin mOrigin;

	sf::Text mButtonText;
	sf::Text mDescriptionText;

	std::string mText;
	std::string mDescription;
	sf::Vector2f mPosition;
	sf::Vector2f mDescriptionPosition;
	sf::Vector2f mScale;
	sf::Vector2i mSize;

	sf::Sprite mSprite;
};