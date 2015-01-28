#include "Button.h"

Button::Button() 
{
}

Button::Button(Textures::ID id, sf::Vector2f position, std::string description) :
mText(""), mPosition(position), mDescription(description)
{
	setSprites(id);
}

Button::Button(Textures::ID id, std::string text, sf::Vector2f position, std::string description) :
mText(text), mPosition(position), mDescription(description)
{
	setSprites(id);
}

void Button::setSprites(Textures::ID id)
{
	sf::Texture* texture = &ResourceManager::GetInstance().getTexture(id);
	int texWidth = texture->getSize().x;
	int texHeight = texture->getSize().y;

	mSize.x = texWidth;
	mSize.y = texHeight / 3;

	mIdleSprite = mv::ISprite(*texture, 1000);
	mIdleSprite.getSprite().setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(mSize.x, mSize.y)));

	mHoverSprite = mv::ISprite(*texture, 1000);
	mHoverSprite.getSprite().setTextureRect(sf::IntRect(sf::Vector2i(0, mSize.y), sf::Vector2i(mSize.x, mSize.y)));

	mClickSprite = mv::ISprite(*texture, 1000);
	mClickSprite.getSprite().setTextureRect(sf::IntRect(sf::Vector2i(0, mSize.y * 2), sf::Vector2i(mSize.x, mSize.y)));

	currentSprite = mIdleSprite;
	setScale(sf::Vector2f(2, 2));
}

void Button::setPosition(sf::Vector2f &pos)
{
	mPosition = pos;
}

void Button::setScale(sf::Vector2f &scale)
{
	mScale = scale;
}

bool Button::isInsideButton(sf::Vector2i &pos)
{
	return (mPosition.x <= pos.x && pos.x <= mPosition.x + (mSize.x * mScale.x) &&  mPosition.y <= pos.y && pos.y <= mPosition.y + (mSize.y * mScale.y));
}

void Button::update()
{
	sf::Vector2i mousePos = MouseState::getMousePosition();

	if (isInsideButton(mousePos))
	{
		if (mouseState.isDown(sf::Mouse::Left))
		{
			currentSprite = mClickSprite;
		}
		else
		{
			currentSprite = mHoverSprite;
		}
	}
	else
	{
		currentSprite = mIdleSprite;
	}
}

void Button::render(IndexRenderer &iRenderer)
{
	currentSprite.getSprite().setPosition(mPosition);
	currentSprite.getSprite().setScale(mScale);
	iRenderer.addISprite(currentSprite);
}