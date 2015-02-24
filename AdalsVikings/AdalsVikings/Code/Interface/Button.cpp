#include "Button.h"
#include <iostream>

Button::Button():
mText(""), mPosition(0, 0), mDescription(""), mOrigin(ButtonOrigin::UpperLeft), mScale(1, 1), mEnabled(true)
{
}

void Button::setTextStuff(Fonts::ID fontID, std::string text, std::string description)
{
	setFont(fontID);
	setText(text);
	setDescription(description);
	setTextSize(24);
	setDescriptionSize(24);
}

Button::Button(Textures::ID texID, sf::Vector2f position) :
mText(""), mPosition(position), mDescription(""), mOrigin(ButtonOrigin::UpperLeft), mScale(1, 1), mEnabled(true)
{
	setSprites(texID);
}

Button::Button(Textures::ID texID, Fonts::ID fontID, sf::Vector2f position, std::string description) :
mText(""), mPosition(position), mDescription(description), mOrigin(ButtonOrigin::UpperLeft), mScale(1, 1), mEnabled(true)
{
	setSprites(texID);
	setTextStuff(fontID, "", mDescription);
}

Button::Button(Textures::ID texID, Fonts::ID fontID, std::string text, sf::Vector2f position, std::string description) :
mText(text), mPosition(position), mDescription(description), mOrigin(ButtonOrigin::UpperLeft), mScale(1, 1), mEnabled(true)
{
	setSprites(texID);
	setTextStuff(fontID, text, mDescription);
}

void Button::setSprites(Textures::ID id)
{
	sf::Texture* texture = &RMI.getResource(id);
	int texWidth = texture->getSize().x;
	int texHeight = texture->getSize().y;
	mSize.x = RMI.getResource(id).getSize().x;
	mSize.y = RMI.getResource(id).getSize().y;

	mSize.x = texWidth;
	mSize.y = texHeight / 3;

	mIndex = 1000;
	mSprite.setTexture(*texture);
	mSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(mSize.x, mSize.y)));
}


void Button::update()
{
	mIsClicked = false;
	mIsPressed = false;
	mIsReleased = false;
	mShowDescription = false;

	if (mEnabled)
	{
		if (isInsideButton(MouseState::getMousePosition()))
		{
			if (MouseState::isClicked(sf::Mouse::Left))
				mIsClicked = true;
			if (MouseState::isReleased(sf::Mouse::Left))
				mIsReleased = true;
			if (MouseState::isPressed(sf::Mouse::Left))
			{
				mIsPressed = true;
				mSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, mSize.y * 2), sf::Vector2i(mSize.x, mSize.y)));
			}
			else
				mSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, mSize.y), sf::Vector2i(mSize.x, mSize.y)));
			mShowDescription = true;
		}
		else
			mSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(mSize.x, mSize.y)));
	}
}

void Button::render(IndexRenderer &iRenderer)
{
	mSprite.setPosition(mPosition);
	mSprite.setScale(mScale);
	iRenderer.addSprite(mSprite, mIndex);

	mButtonText.setPosition(sf::Vector2f(mPosition.x - (mButtonText.getGlobalBounds().width / 2), mPosition.y - (mButtonText.getGlobalBounds().height / 2)));
	iRenderer.addText(mButtonText, mIndex + 2);
	
	if (mShowDescription)
	{
		mDescriptionText.setPosition(mPosition + mDescriptionPosition);
		iRenderer.addText(mDescriptionText, mIndex + 1);
	}
}

bool Button::isClicked()  { return mIsClicked; }
bool Button::isPressed()  { return mIsPressed; }
bool Button::isReleased() { return mIsReleased; }

bool Button::isInsideButton(sf::Vector2i &pos) 
{ 
	if (mOrigin == ButtonOrigin::Center)
	{
		return 
			mPosition.x - ((mSize.x * mScale.x) / 2) <= pos.x  &&
			pos.x <= mPosition.x + ((mSize.x * mScale.x) / 2) &&
			mPosition.y - ((mSize.y * mScale.y) / 2) <= pos.y &&
			pos.y <= mPosition.y + ((mSize.y * mScale.y) / 2);
	}
	else if (mOrigin == ButtonOrigin::UpperLeft)
	{
		return 
			mPosition.x <= pos.x && 
			pos.x <= mPosition.x + (mSize.x * mScale.x) && 
			mPosition.y <= pos.y && 
			pos.y <= mPosition.y + (mSize.y * mScale.y);
	}

	return false;
}

void Button::setPosition(sf::Vector2f &pos)
{
	mPosition = pos;
	setDescriptionPosition(mDescriptionPosition);
}

void Button::setDescriptionPosition(sf::Vector2f &pos)
{
	mDescriptionPosition = pos;
}

void Button::setScale(sf::Vector2f &scale)
{
	mScale = scale;
	setPosition(mPosition);
}

void Button::setOrigin(ButtonOrigin origin)
{
	mOrigin = origin;
	if (mOrigin == ButtonOrigin::Center)
		mSprite.setOrigin(sf::Vector2f(mSize.x / 2, mSize.y / 2));
	else if (mOrigin == ButtonOrigin::UpperLeft)
		mSprite.setOrigin(sf::Vector2f(0, 0));
	setPosition(mPosition);
}

void Button::setEnabled(bool enabled)
{
	mEnabled = enabled;
}

void Button::setIndex(int index)
{
	mIndex = index;
}

void Button::setFont(Fonts::ID id)
{
	mButtonText.setFont(RMI.getResource(id));
	mDescriptionText.setFont(RMI.getResource(id));
}
void Button::setText(std::string text)
{
	mButtonText.setString(text);
}
void Button::setDescription(std::string text)
{
	mDescriptionText.setString(text);
}
void Button::setTextSize(int textSize)
{
	mButtonText.setCharacterSize(textSize);
}
void Button::setDescriptionSize(int dSize)
{
	mDescriptionText.setCharacterSize(dSize);
}
void Button::setTextStyle(sf::Text::Style style)
{
	mButtonText.setStyle(style);
}
void Button::setDescriptionStyle(sf::Text::Style style)
{
	mDescriptionText.setStyle(style);
}
void Button::setTextColor(sf::Color color)
{
	mButtonText.setColor(color);
}
void Button::setDescriptionColor(sf::Color color)
{
	mDescriptionText.setColor(sf::Color::White);
}