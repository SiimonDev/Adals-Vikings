#pragma once
#include "..\Objects\Object.h"
#include "..\Logics\IndexRenderer.h"
#include <SFML\Graphics.hpp>

class InvTile
{
public:
	InvTile();
	InvTile(sf::Vector2f position, int width, int height);

	void setObject(Object* object);
	void removeObject();
	void setRectangle(sf::RectangleShape &rectShape);

	bool isInside(sf::Vector2i &pos);
	bool hasObject();

	Object &getObject();
	std::string getObjectID();
	sf::RectangleShape &getRectangle();
	sf::Vector2f getPosition();

	void load();
	void unload();
	void update(sf::Time frameTime);
	void render(IndexRenderer &iRenderer);

private:
	bool mHasObject;
	bool mSnapToMouse;

	Object* mObject;
	sf::Vector2f mScale;
	sf::Vector2f mPosition;
	sf::RectangleShape mRectangle;
};
