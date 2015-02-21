#pragma once
#include "..\Objects\ObjectHandler.h"

class Inventory
{
public:
	Inventory();

	void load();
	void unload();
	void loadObjects();
	void unloadObjects();
	void update(sf::Time frameTime);
	void render(IndexRenderer &iRenderer);

	bool addItemToInventory(std::string objectID);
	bool removeItemFromInventory(std::string objectID);
	void saveInventoryToFile();
	void loadInventoryFromFile();
	void clearInventory();
	void toggleInventory();

	bool isActive();
	bool isInside(sf::Vector2i &pos);
	bool hasItemInInventory(std::string objID);

	std::string getDroppedObjectID();

private:
	Object* mSnappedObject;

	int mIndex;

	sf::Sprite mSprite;
	sf::Vector2f mPosition;
	sf::Vector2f mScale;
	std::string mFilePath;

	bool mDisplay;
	bool mHasSnappedObject;
	bool mDroppedSnappedObj;
};