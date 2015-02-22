#include "InvTile.h"
#include "..\Logics\MouseState.h"

InvTile::InvTile()
{
}

InvTile::InvTile(sf::Vector2f position, int width, int height)
{
	mPosition = position;
	mRectangle = sf::RectangleShape(sf::Vector2f(width, height));
	mRectangle.setOrigin(width / 2, height / 2);
	mRectangle.setPosition(mPosition);
	mHasObject = false;
}

void InvTile::setObject(Object* object)
{
	mHasObject = true;
	mObject = object;
}

void InvTile::removeObject()
{
	delete mObject;
	mHasObject = false;
}

void InvTile::setRectangle(sf::RectangleShape &rectShape)
{
	mRectangle = rectShape;
}

bool InvTile::isInside(sf::Vector2i &pos)
{
	return 
		mPosition.x - (mRectangle.getSize().x / 2) <= pos.x  &&
		pos.x <= mPosition.x + (mRectangle.getSize().x) - (mRectangle.getSize().x / 2) &&
		mPosition.y - (mRectangle.getSize().y / 2) <= pos.y &&
		pos.y <= mPosition.y + (mRectangle.getSize().y) - (mRectangle.getSize().y / 2);
}

bool InvTile::hasObject()
{
	return mHasObject;
}

Object &InvTile::getObject()
{
	return *mObject;
}

std::string InvTile::getObjectID()
{
	if (mHasObject)
		return mObject->getObjID();

	return "";
}

sf::RectangleShape &InvTile::getRectangle()
{
	return mRectangle;
}

sf::Vector2f InvTile::getPosition()
{
	return mPosition;
}

void InvTile::load()
{
	if (mHasObject){
		mObject->load();
	}
}

void InvTile::unload()
{
	if (mHasObject){
		mObject->unload();
		delete mObject;
		mHasObject = false;
	}
}

void InvTile::update(sf::Time frameTime)
{
	if (isInside(MouseState::getMousePosition())){
		mScale.x = 1.25f;
		mScale.y = 1.25f;
		mRectangle.setFillColor(sf::Color(255, 0, 0, 255));
	}
	else{
		mScale.x = 1;
		mScale.y = 1;
		mRectangle.setFillColor(sf::Color(255, 255, 255, 255));
	}
}

void InvTile::render(IndexRenderer &iRenderer)
{
	if (mHasObject)
	{
		mObject->setPosition(mPosition);
		mObject->setScale(mScale);
		mObject->render(iRenderer);
	}
	//iRenderer.addRectangle(mRectangle, 99999999);
}