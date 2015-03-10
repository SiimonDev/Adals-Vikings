#include "Inventory.h"
#include "..\Dialog\PlayerMonologue.h"
#include "..\Logics\AudioPlayer.h"
#include "..\Logics\MouseState.h"
#include "..\Logics\BoatEvents.h"
#include "InvTile.h"
#include <iostream>
#include <fstream>


const int invWidth = 8;
const int invHeight = 4;

InvTile invTiles[invWidth][invHeight];

Inventory::Inventory()
{
	mFilePath = "Assets/textfiles/inventory.txt";
	mDisplay = false;
	mPosition = sf::Vector2f(960, 540);
	mScale = sf::Vector2f(0.75, 0.75);
	mHasSnappedObject = false;
}

void Inventory::load()
{
	RMI.loadResource(Sound::PickUpItem);
	RMI.loadResource(Sound::InventoryOpen);
	RMI.loadResource(Sound::InventoryClose);
	RMI.loadResource(Texture::InventoryBackground);
	mSprite.setTexture(RMI.getResource(Texture::InventoryBackground));
	mIndex = 999999;

	// tileShit
	int tileWidth = 140 * mScale.x;
	int tileHeight = 140 * mScale.y;
	float tileStartPosX = mPosition.x - (((1920 / 2) - 310) * mScale.x) + (tileWidth / 2);
	float tileStartPosY = mPosition.y - (((1080 / 2) - 215) * mScale.y) + (tileHeight / 2);

	float tileAreaWidth = ((1920 - 310 - 355) * mScale.x);
	float tileAreaHeight = ((1080 - 215 - 240) * mScale.y) ;
	
	for (int x = 0; x < invWidth; x++){
		for (int y = 0; y < invHeight; y++){
			invTiles[x][y] = InvTile(sf::Vector2f(tileStartPosX + ((tileAreaWidth / invWidth) * x), tileStartPosY + ((tileAreaHeight / invHeight) * y)), tileWidth, tileHeight);
		}
	}

	loadObjects();
}

void Inventory::unload()
{
	RMI.unloadResource(Sound::PickUpItem);
	RMI.unloadResource(Sound::InventoryOpen);
	RMI.unloadResource(Sound::InventoryClose);
	RMI.unloadResource(Texture::InventoryBackground);
	unloadObjects();
}

void Inventory::loadObjects()
{
	loadInventoryFromFile();
	for (int x = 0; x < invWidth; x++){
		for (int y = 0; y < invHeight; y++){
			invTiles[x][y].load();
		}
	}
}

void Inventory::unloadObjects()
{
	for (int x = 0; x < invWidth; x++){
		for (int y = 0; y < invHeight; y++){
			invTiles[x][y].unload();
		}
	}
}

void Inventory::update(sf::Time frameTime)
{
	if (mDisplay)
	{
		for (int x = 0; x < invWidth; x++)
		{
			for (int y = 0; y < invHeight; y++)
			{
				invTiles[x][y].update(frameTime);

				if (invTiles[x][y].isInside(MouseState::getMousePosition()))
				{
					if (MouseState::isPressed(sf::Mouse::Left) && !mHasSnappedObject)
					{
						if (invTiles[x][y].hasObject()){
							mSnappedObject = new Object(invTiles[x][y].getObject());
							invTiles[x][y].removeObject();
							mHasSnappedObject = true;
						}
					}
					else if (!MouseState::isPressed(sf::Mouse::Left) && mHasSnappedObject)
					{
						if (invTiles[x][y].hasObject())
						{
							CombineDialog newObjDialog = mSnappedObject->combineWithObject(invTiles[x][y].getObjectID());

							PlayerMonologueI.displayDialog(newObjDialog);
							if (newObjDialog.mResultID != ""){
								invTiles[x][y].removeObject();
								addItemToInventory(newObjDialog.mResultID);
							}
							else
								addItemToInventory(mSnappedObject->getObjID());
						}
						else
							addItemToInventory(mSnappedObject->getObjID());

						delete mSnappedObject;
						mHasSnappedObject = false;
					}
					else
					{
						if (invTiles[x][y].hasObject())
							invTiles[x][y].getObject().enableDescription(true);
					}
				}
				else
				{
					if (invTiles[x][y].hasObject())
						invTiles[x][y].getObject().enableDescription(false);
				}
			}
		}

		if (!isInside(MouseState::getMousePosition()) && mHasSnappedObject){
			toggleInventory();
		}
	}

	if (mDroppedSnappedObj)
	{
		addItemToInventory(mSnappedObject->getObjID());
		delete mSnappedObject;
		mDroppedSnappedObj = false;
	}

	if (mHasSnappedObject)
	{
		mSnappedObject->enableDescription(false);
		mSnappedObject->setPosition(sf::Vector2f(MouseState::getMousePosition()));
		mSnappedObject->update(frameTime);

		if (!MouseState::isPressed(sf::Mouse::Left))
		{
			mDroppedSnappedObj = true;
			mHasSnappedObject = false;
		}
	}
}

void Inventory::render(IndexRenderer &iRenderer)
{
	if (mDisplay)
	{
		mSprite.setOrigin(mSprite.getTexture()->getSize().x / 2, mSprite.getTexture()->getSize().y / 2);
		mSprite.setScale(mScale);
		mSprite.setPosition(mPosition);
		iRenderer.addSprite(mSprite, mIndex);

		for (int x = 0; x < invWidth; x++){
			for (int y = 0; y < invHeight; y++)
				invTiles[x][y].render(iRenderer);
		}
	}
	if (mHasSnappedObject)
		mSnappedObject->render(iRenderer);
}

bool Inventory::addItemToInventory(std::string objectID)
{
	if (objectID == "bucket")
		BoatEvents::triggerEvent(BoatEvent::PickedUpBucket);

	AudioPlayer::playSound(Sound::PickUpItem, "pickUpItem", false);
	for (int x = 0; x < invWidth; x++)
	{
		for (int y = 0; y < invHeight; y++)
		{
			if (!invTiles[x][y].hasObject())
			{
				Object* obj = new Object(OBHI.getObject(objectID));
				obj->setIndex(9999999);
				invTiles[x][y].setObject(obj);
				invTiles[x][y].load();
				return true;
			}
		}
	}
	return false;
}

bool Inventory::removeItemFromInventory(std::string objectID)
{
	for (int x = 0; x < invWidth; x++)
	{
		for (int y = 0; y < invHeight; y++)
		{
			if (invTiles[x][y].getObjectID() == objectID)
			{
				invTiles[x][y].removeObject();
				return true;
			}
		}
	}
	return false;
}

void Inventory::saveInventoryToFile()
{
	//std::cout << "--- Saving Inventory to: " + mFilePath + " ---" << std::endl;
	std::ofstream file(mFilePath);

	for (int x = 0; x < invWidth; x++)
	{
		for (int y = 0; y < invHeight; y++)
		{
			file << "slot_" << x << "." << y << ": ";
			if (invTiles[x][y].hasObject())
				file << "$" << invTiles[x][y].getObject().getObjID();
			file << std::endl;
		}
	}
	file.close();
}

void Inventory::loadInventoryFromFile()
{
	//std::cout << std::endl << "--- Loading Inventory from " + mFilePath + " ---" << std::endl;
	std::ifstream file("Assets/textfiles/inventory.txt");

	std::string line;
	while (getline(file, line))
	{
		int xI = atoi(&line.c_str()[line.find("_") + 1]);
		int yI = atoi(&line.c_str()[line.find("_") + 3]);

		if (line.find("$") != std::string::npos)
		{
			std::string id = line.substr(line.find("$") + 1, line.size());
			Object* obj = new Object(OBHI.getObject(id));
			obj->setIndex(9999999);
			invTiles[xI][yI].setObject(obj);
		}
	}
}

void Inventory::clearInventory()
{
	//std::cout << "--- Clearing Inventory ---" << std::endl;
	std::ofstream file(mFilePath);
	unloadObjects();
	for (int x = 0; x < invWidth; x++)
	{
		for (int y = 0; y < invHeight; y++)
			file << "slot_" << x << "." << y << ": " << std::endl;
	}
}

void Inventory::toggleInventory()
{
	if (mDisplay)
		AudioPlayer::playSound(Sound::InventoryClose, "closeInv", false);
	else
		AudioPlayer::playSound(Sound::InventoryOpen, "openInv", false);
	
	mDisplay = !mDisplay;
}

bool Inventory::isActive()
{
	return mDisplay;
}

bool Inventory::isInside(sf::Vector2i &pos)
{
	sf::Vector2f size;
	size.x = mSprite.getTextureRect().width;
	size.y = mSprite.getTextureRect().height;
	return
		mPosition.x - ((size.x * mScale.x) / 2) <= pos.x  &&
		pos.x <= mPosition.x + ((size.x * mScale.x) / 2) &&
		mPosition.y - ((size.y * mScale.y) / 2) <= pos.y &&
		pos.y <= mPosition.y + ((size.y * mScale.y) / 2);
}

bool Inventory::hasItemInInventory(std::string objID)
{
	for (int x = 0; x < invWidth; x++)
	{
		for (int y = 0; y < invHeight; y++)
		{
			if (invTiles[x][y].getObjectID() == objID)
				return true;
		}
	}
	return false;
}

std::string Inventory::getSnappedObjectID()
{
	if (mHasSnappedObject)
		return mSnappedObject->getObjID();
	return "";
}

std::string Inventory::getDroppedObjectID()
{
	if (mDroppedSnappedObj)
		return mSnappedObject->getObjID();
	return "";
}