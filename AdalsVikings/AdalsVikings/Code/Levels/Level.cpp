#include "Level.h"
#include "..\Dialog\DialogHandler.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

Level::Level(Player& player, ActionWheel &ActionWheel)
: mPlayer(player)
, mIsNearbyLevel(false)
, mIsLoaded(false)
, mHasBeenReset(false)
{
	mActionWheel = &ActionWheel;
}

void Level::updateObjects(sf::Time frameTime)
{
	// Object update functions
	for (int i = 0; i < mObjects.size(); i++)
	{
		mObjects[i]->update(frameTime);
		if (mActionWheel->isButtonSelected())
		{
			if (mObjects[i]->isInside(sf::Vector2i(mActionWheel->getPosition())))
			{
				mObjIndex = i;
				mWalkToObject = true;

				if (mActionWheel->isLookSelected())
					mPlayer.setIntention(Intention::Look);
				else if (mActionWheel->isTalkSelected())
					mPlayer.setIntention(Intention::Talk);
				else if (mActionWheel->isPickUpSelected())
					mPlayer.setIntention(Intention::PickUp);

				sf::Vector2f interactPos = mObjects[mObjIndex]->getPosition() + mObjects[mObjIndex]->getInteractionPosition();
				Path path = PathFinder::getPath(mPlayer.getPosition(), interactPos);
				mPlayer.walkPath(path);
			}

		}
		else if (mPlayer.getDroppedObjectID() != "")
		{
			if (mObjects[i]->isInside(MouseState::getMousePosition()))
			{
				mDroppedItemID = mPlayer.getDroppedObjectID();
				mObjIndex = i;
				mWalkToObject = true;

				mPlayer.setIntention(Intention::Interact);

				sf::Vector2f interactPos = mObjects[mObjIndex]->getPosition() + mObjects[mObjIndex]->getInteractionPosition();
				Path path = PathFinder::getPath(mPlayer.getPosition(), interactPos);
				mPlayer.walkPath(path);
			}
		}
		else
		{
			if (mObjects[i]->isInside(MouseState::getMousePosition()))
			{
				mObjects[i]->enableDescription(true);
				if (mPlayer.getSnappedObjectID() != "")
					mObjects[i]->setDescription("Use " + OBHI.getObject(mPlayer.getSnappedObjectID()).getName() + " on " + mObjects[i]->getName());
				else
					mObjects[i]->setDescription(mObjects[i]->getName());
			}
			else
				mObjects[i]->enableDescription(false);
		}
	}

	// Walk to object functions
	if (mWalkToObject && mPlayer.isDestinationReached())
	{
		if (mPlayer.getIntention() == Intention::Look)
		{
			if (mPlayer.getPosition().x < mObjects[mObjIndex]->getPosition().x)
				mPlayer.setFlip(true);
			else
				mPlayer.setFlip(false);
			Dialog dialog = Dialog(mObjects[mObjIndex]->getLookAtDialog());
			DialogWindow::displayDialog(dialog);
			mPlayer.setIntention(Intention::None);
			mWalkToObject = false;

		}
		else if (mPlayer.getIntention() == Intention::Talk)
		{
			if (mPlayer.getPosition().x < mObjects[mObjIndex]->getPosition().x)
				mPlayer.setFlip(true);
			else
				mPlayer.setFlip(false);

			Dialog dialog = (mObjects[mObjIndex]->interactWithObject("player"));
			DialogWindow::displayDialog(dialog);
			mPlayer.setIntention(Intention::None);
			mWalkToObject = false;
		}
		else if (mPlayer.getIntention() == Intention::PickUp)
		{
			if (mPlayer.getPosition().x < mObjects[mObjIndex]->getPosition().x)
				mPlayer.setFlip(true);
			else
				mPlayer.setFlip(false);
			Dialog dialog = Dialog(mObjects[mObjIndex]->getPickupDialog());
			DialogWindow::displayDialog(dialog);
			if (mObjects[mObjIndex]->isPickupable())
			{
				mPlayer.setAnimationStyle(AnimationType::Pickup);
				if (mPlayer.getAnimation().getStopped())
				{
					mPlayer.addItemToInventory(mObjects[mObjIndex]->getObjID());
					PathFinder::getCurrentTileMap().removeCollision(mObjects[mObjIndex]->getCollisionRect());
					delete mObjects[mObjIndex];
					mObjects.erase(mObjects.begin() + mObjIndex);
					mPlayer.setIntention(Intention::None);
					mWalkToObject = false;
				}
			}
		}
		else if (mPlayer.getIntention() == Intention::Interact)
		{
			if (mPlayer.getPosition().x < mObjects[mObjIndex]->getPosition().x)
				mPlayer.setFlip(true);
			else
				mPlayer.setFlip(false);
			Dialog dialog = Dialog(OBHI.getObject(mDroppedItemID).interactWithObject(mObjects[mObjIndex]->getObjID()));
			DialogWindow::displayDialog(dialog);
			mPlayer.setIntention(Intention::None);
			mWalkToObject = false;
		}
	}

	if (MouseState::isPressed(sf::Mouse::Left))
	{
		mPlayer.setIntention(Intention::None);
		mWalkToObject = false;
	}
}
void Level::updateNPCs(sf::Time frameTime)
{
	for (std::map<std::string, NpcPtr>::const_iterator it = mNpcs.begin(); it != mNpcs.end(); it++)
	{
		it->second->update(frameTime);

		if (mActionWheel->isButtonSelected())
		{
			if (it->second->isInside(sf::Vector2i(mActionWheel->getPosition())))
			{
				mCurrentNPCID = it->first;
				mWalkToNPC = true;

				if (mActionWheel->isLookSelected())
					mPlayer.setIntention(Intention::Look);
				else if (mActionWheel->isTalkSelected())
				{
					mPlayer.setIntention(Intention::Talk);
					mActionWheel->setfalse();
				}
				else if (mActionWheel->isPickUpSelected())
					mPlayer.setIntention(Intention::PickUp);

				Path path = PathFinder::getPath(mPlayer.getPosition(), it->second->getInteractionPosition());
				mPlayer.walkPath(path);
			}
		}
		else if (mPlayer.getDroppedObjectID() != "")
		{
			if (it->second->isInside(MouseState::getMousePosition()))
			{
				mDroppedItemID = mPlayer.getDroppedObjectID();
				mCurrentNPCID = it->first;
				mWalkToNPC = true;

				mPlayer.setIntention(Intention::Interact);

				Path path = PathFinder::getPath(mPlayer.getPosition(), it->second->getInteractionPosition());
				mPlayer.walkPath(path);
			}
		}
		else
		{
			if (it->second->isInside(MouseState::getMousePosition()))
			{
				it->second->enableDescription(true);
				if (mPlayer.getSnappedObjectID() != "")
					it->second->setDescription("Give " + OBHI.getObject(mPlayer.getSnappedObjectID()).getName() + " to " + it->second->getName());
				else
					it->second->setDescription(it->second->getName());
			}
			else
				it->second->enableDescription(false);
		}
	}
	
	if (mWalkToNPC && mPlayer.isDestinationReached())
	{
		if (mPlayer.getIntention() == Intention::Look)
		{
			if (mPlayer.getPosition().x < mNpcs[mCurrentNPCID]->getPosition().x)
				mPlayer.setFlip(true);
			else
				mPlayer.setFlip(false);
			mPlayer.UpdateAnimationStyle();
			Dialog dialog = Dialog(mNpcs[mCurrentNPCID]->getLookText(), 2);
			DialogWindow::displayDialog(dialog);
		}
		else if (mPlayer.getIntention() == Intention::Talk)
		{
			if (mPlayer.getPosition().x < mNpcs[mCurrentNPCID]->getPosition().x)
				mPlayer.setFlip(true);
			else
				mPlayer.setFlip(false);
			mPlayer.UpdateAnimationStyle();
			mNpcs[mCurrentNPCID]->startConversation();
			mIsInConversation = true;
			mPlayer.setIntention(Intention::None);
		}
		else if (mPlayer.getIntention() == Intention::PickUp)
		{
			if (mPlayer.getPosition().x < mNpcs[mCurrentNPCID]->getPosition().x)
				mPlayer.setFlip(true);
			else
				mPlayer.setFlip(false);
			mPlayer.UpdateAnimationStyle();
			Dialog dialog = Dialog(mNpcs[mCurrentNPCID]->getUseText(), 2);
			DialogWindow::displayDialog(dialog);
		}
		else if (mPlayer.getIntention() == Intention::Interact)
		{
			if (mPlayer.getPosition().x < mNpcs[mCurrentNPCID]->getPosition().x)
				mPlayer.setFlip(true);
			else
				mPlayer.setFlip(false);
			mPlayer.UpdateAnimationStyle();
			checkInteractEvents();
			Dialog dialog = Dialog(OBHI.getObject(mDroppedItemID).interactWithObject(mCurrentNPCID));
			DialogWindow::displayDialog(dialog);
		}
		mWalkToNPC = false;
	}
	if (MouseState::isPressed(sf::Mouse::Left))
	{
		mPlayer.setIntention(Intention::None);
		mWalkToNPC = false;
	}
}
void Level::updateDialog(sf::Time frameTime)
{
	for (std::map<std::string, DialogueTreePtr>::const_iterator it = DialogHandler::getDialogues().begin(); it != DialogHandler::getDialogues().end(); it++)
	{
		if (it->second->getActiveConversation())
		{
			mIsInConversation = true;
			it->second->update(frameTime);
			for (std::map<std::string, NpcPtr>::const_iterator iz = mNpcs.begin(); iz != mNpcs.end(); iz++)
			{
				if (it->second->getCharacter() == iz->second->getName() && it->second->getPrintText().getString() != "")
				{
					iz->second->setFlip(it->second->getFacing());
					iz->second->setAnimationStyle("Npc");
					mPlayer.setAnimationStyle(AnimationType::Idle);
					if (!iz->second->isInvisible())
					{
						it->second->setTextPosition(sf::Vector2f(iz->second->getAnimation().getSprite().getGlobalBounds().left +
							iz->second->getAnimation().getSprite().getGlobalBounds().width / 2,
							iz->second->getAnimation().getSprite().getGlobalBounds().top - it->second->getPrintText().getGlobalBounds().height / 2));
					}
					else if (iz->second->isInvisible())
					{
						it->second->setTextPosition(sf::Vector2f(iz->second->getInvisRect().getPosition().x +
							iz->second->getInvisRect().getSize().x / 2,
							iz->second->getInvisRect().getPosition().y));
					}
					it->second->setTextColor(iz->second->getColor());
				}
				else if (it->second->getCharacter() == iz->second->getName() && it->second->getPrintText().getString() == "")
				{
					iz->second->setFlip(it->second->getFacing());
					iz->second->setAnimationStyle("Idle");
				}
				else if (it->second->getCharacter() == mPlayer.getName() && it->second->getFacePlayer() && it->second->getPrintText().getString() != "")
				{
					mPlayer.setFlip(it->second->getFacing());
					mPlayer.setAnimationStyle(AnimationType::TalkToPlayer);
					iz->second->setAnimationStyle("Idle");
					it->second->setTextPosition(sf::Vector2f(mPlayer.getSprite().getGlobalBounds().left +
						mPlayer.getSprite().getGlobalBounds().width / 2,
						mPlayer.getSprite().getGlobalBounds().top - it->second->getPrintText().getGlobalBounds().height / 2));
					it->second->setTextColor(sf::Color::White);
				}
				else if (it->second->getCharacter() == mPlayer.getName() && it->second->getFacePlayer() && it->second->getPrintText().getString() == "")
				{
					mPlayer.setFlip(it->second->getFacing());
					mPlayer.setAnimationStyle(AnimationType::Idle);
				}
				else if (it->second->getCharacter() == mPlayer.getName() && !it->second->getFacePlayer() && it->second->getPrintText().getString() != "")
				{
					mPlayer.setAnimationStyle(AnimationType::TalkToNpc);
					iz->second->setAnimationStyle("Idle");
					mPlayer.setFlip(it->second->getFacing());
					it->second->setTextPosition(sf::Vector2f(mPlayer.getSprite().getGlobalBounds().left +
												mPlayer.getSprite().getGlobalBounds().width / 2,
												mPlayer.getSprite().getGlobalBounds().top - it->second->getPrintText().getGlobalBounds().height / 2));
					it->second->setTextColor(sf::Color::White);
				}
				else if (it->second->getCharacter() != iz->second->getName() && it->second->getCharacter() != mPlayer.getName())
				{
					iz->second->setAnimationStyle("Idle");
					mPlayer.setAnimationStyle(AnimationType::Idle);
				}
			}
		}

		if (it->second->getEndConversation() == true)
		{
			DialogHandler::reloadConversations();
			it->second->setEndConversation(false);
			mIsInConversation = false;

			for (std::map<std::string, NpcPtr>::const_iterator iz = mNpcs.begin(); iz != mNpcs.end(); iz++)
				iz->second->setAnimationStyle("Idle");
		}
	}
	setDialogPosition();
}

void Level::update(sf::Time &frameTime)
{
	MouseState::setCursorType(CursorType::Default);
	updateDialog(frameTime);
	updateNPCs(frameTime);
	mPlayer.update(frameTime);
	mPlayer.setFootsteps(mCurrentFootsteps);
	checkEvents();
	setDialogPosition();

	if (KeyboardState::isPressed(sf::Keyboard::F5))
	{
		OBHI.initialize();
		resetLevel();
		refreshLevel();
	}
	
	if (!mIsInConversation && FadeI.getFaded() && !(mPlayer.isInventoryActive() || mPlayer.getSnappedObjectID() != ""))
		mActionWheel->update();
	if (!mIsInConversation && !mOldIsInConversation && FadeI.getFaded())
	{
		mPlayer.move(frameTime);
		updateObjects(frameTime);
	}
	mOldIsInConversation = mIsInConversation;

	// Do the portal thing
	for (std::map<PortalId, Portal*>::const_iterator it = mPortals.begin(); it != mPortals.end(); it++)
	{
		if (!it->second->getWalkAble())
		{
			it->second->update(frameTime, mPlayer);
			it->second->portalTravel(mPlayer);
		}
		else
			it->second->walkPath(mPlayer);
	}
}

void Level::render(IndexRenderer &iRenderer)
{
	mActionWheel->render(iRenderer);
	mPlayer.render(iRenderer);
	FadeI.render(iRenderer);

	// Render all the backgrounds
	for (int i = 0; i < mBackgrounds.size(); i++)
		iRenderer.addSprite(mBackgrounds[i], mBackgroundsIndexes[i]);

	// Render all the portals
	for (std::map<PortalId, Portal*>::const_iterator it = mPortals.begin(); it != mPortals.end(); it++)
		it->second->render(iRenderer);

	// Render all the NPCs
	for (std::map<std::string, NpcPtr>::const_iterator it = mNpcs.begin(); it != mNpcs.end(); it++)
		it->second->render(iRenderer);

	// Render all the dialogues
	for (std::map<std::string, DialogueTreePtr>::const_iterator it = DialogHandler::getDialogues().begin(); it != DialogHandler::getDialogues().end(); it++)
		it->second->render(iRenderer);

	// Render all the objects
	for each (Object* object in mObjects)
		object->render(iRenderer);
}

void Level::loadAllBackgrounds()
{
	// Load TileMap
	mTileMapFilePath = RMI.getRCFileFromFolder(mFolderPath);	 // Find the filepath of the TileMap File
	RMI.loadImage(mTileMapFilePath);							 // Load the TileMap File

	// Load IndexMap
	mIndexMapFilePath = RMI.getIndexFileFromFolder(mFolderPath); // Find the filepath of the indexfile
	RMI.loadImage(mIndexMapFilePath);							 // Load the indexfile

	mTileMap.load(sf::Vector2i(15, 15), RMI.getNonIDImage(mTileMapFilePath), RMI.getNonIDImage(mIndexMapFilePath));
	
	// Load all the backgrounds
	RMI.loadResource(mBackgroundID);

	for (int i = 0; i < RMI.getResource(mBackgroundID).size(); i++)
	{
		mBackgrounds.push_back(sf::Sprite(*RMI.getResource(mBackgroundID).at(i)));
		mBackgroundsIndexes.push_back(i * 10);
	}
}
void Level::loadObjects()
{
	std::ifstream file(mFolderPath + "level_objects.txt");

	std::string line;
	while (getline(file, line))
	{
		if (line.find("#") == std::string::npos)
		{
			//std::cout << std::endl << "-- Loading Object from " << mFolderPath << " ---" << std::endl;
			if (line.find("*id") != std::string::npos)
			{
				std::string id = line.substr(line.find("$") + 1, line.size());

				getline(file, line);
				int xPos = atoi((line.substr(line.find("$X:") + 3, (line.find("$Y:") - 1) - (line.find("$X:") + 3))).c_str());
				int yPos = atoi((line.substr(line.find("$Y:") + 3, line.size())).c_str());

				getline(file, line);
				int intXPos = atoi((line.substr(line.find("$X:") + 3, (line.find("$Y:") - 1) - (line.find("$X:") + 3)).c_str()));
				int intYPos = atoi((line.substr(line.find("$Y:") + 3, line.size()).c_str()));

				getline(file, line);
				int index = atoi((line.substr(line.find("$") + 1, line.size())).c_str());

				getline(file, line);
				float scale = atof((line.substr(line.find("$") + 1, line.size())).c_str());

				getline(file, line);
				std::string collision = line.substr(line.find("$") + 1, line.size());

				bool enableCollision = ("true" == collision);

				Object* obj = new Object(OBHI.getObject(id));
				obj->setPosition(sf::Vector2f(xPos, yPos));
				obj->setInteractionPosition(sf::Vector2f(intXPos, intYPos));
				obj->setIndex(index);
				obj->setScale(sf::Vector2f(scale, scale));
				obj->enableCollision(enableCollision);
				obj->load();
				if (enableCollision)
					mTileMap.addCollision(obj->getCollisionRect());
				mObjects.push_back(obj);

				//std::cout << "ID: " << id << std::endl;
				//std::cout << "XPos: " << xPos << " YPos: " << yPos << std::endl;
				//std::cout << "intXPos: " << intXPos << " intYPos: " << intYPos << std::endl;
				//std::cout << "Index: " << index << std::endl;
				//std::cout << "Scale: " << scale << std::endl;
			}
		}
	}
	file.close();
	//std::cout << std::endl;
}
void Level::saveObjects()
{
	std::ofstream file(mFolderPath + "level_objects.txt");

	//std::cout << "--- Saving Object to " << mFolderPath + "level_objects.txt" << " ---" << std::endl;
	file << "############" << std::endl;
	for each (Object* obj in mObjects)
	{
		file << "*id: $" << obj->getObjID() << std::endl;
		file << "position: $X:" << obj->getPosition().x << " $Y:" << obj->getPosition().y << std::endl;
		file << "interactPosition: $X:" << obj->getInteractionPosition().x << " $Y:" << obj->getInteractionPosition().y << std::endl;
		file << "index: $" << obj->getIndex() << std::endl;
		file << "scale: $" << obj->getScale().x << std::endl;
		file << "hascollision: ";

		if (obj->hasCollision())
			file << "$true";
		else
			file << "$false";
		
		file << std::endl;
		file << "############" << std::endl;
	}
	file.close();
}
void Level::resetLevel()
{
	mInstream.open(mFolderPath + "level_objects_reset.txt");
	mOfstream.open(mFolderPath + "level_objects.txt");
	std::string line;
	while (!mInstream.eof())
	{
		std::getline(mInstream, line);
		mOfstream << line << std::endl;
	}
	mInstream.close();
	mOfstream.close();
}
void Level::refreshLevel()
{
	// Reset Portals
	for (std::map<PortalId, Portal*>::const_iterator it = mPortals.begin(); it != mPortals.end(); it++)
		it->second->setActivate(false);

	// Reset objects
	for each (Object* obj in mObjects){
		mTileMap.removeCollision(obj->getCollisionRect());
		obj->unload();
		delete obj;
	}
	mObjects.clear();

	loadObjects();
}

void Level::load()
{
	// Load All objects
	loadObjects();

	// Load All backgrounds, TileMaps, and index maps
	loadAllBackgrounds();

	// Load NPCs
	for (std::map<std::string, NpcPtr>::const_iterator it = mNpcs.begin(); it != mNpcs.end(); it++)
		it->second->load();

	// Load Default Footsteps
	RMI.loadResource(Footsteps::Default);
	mCurrentFootsteps = Footsteps::Default;
	mPlayer.setFootsteps(Footsteps::Default);
	setLoaded(true);
}
void Level::unload()
{
	RMI.unloadImage(mTileMapFilePath);
	RMI.unloadImage(mIndexMapFilePath);
	mTileMap.unload();
	mBackgrounds.clear();
	RMI.unloadResource(mBackgroundID);

	// Unload NPCs
	for (std::map<std::string, NpcPtr>::const_iterator it = mNpcs.begin(); it != mNpcs.end(); it++)
		it->second->unload();
	mNpcs.clear();
	
	// Unload and delete all the objects
	for each (Object* object in mObjects){
		object->unload();
		delete object;
	}
	mObjects.clear();

	RMI.unloadResource(Footsteps::Default);
}

void Level::checkInteractEvents()
{

}

void Level::checkEvents()
{

}

void Level::setDialogPosition()
{
	DialogWindow::setPosition(sf::Vector2f(mPlayer.getSprite().getGlobalBounds().left +
		mPlayer.getSprite().getGlobalBounds().width / 2,
		mPlayer.getSprite().getGlobalBounds().top));
}

TileMap &Level::getTileMap()
{
	return mTileMap;
}

void Level::setLoaded(bool value)
{
	mIsLoaded = value;
}

void Level::setIsNearbyLevel(bool value)
{
	mIsNearbyLevel = value;
}

bool & Level::getIsNearbyLevel()
{
	return mIsNearbyLevel;
}

bool & Level::getIsLoaded()
{
	return mIsLoaded;
}

void Level::setBackgroundID()
{
	mFolderPath = RMI.getFilePath(mBackgroundID);
}

std::vector<LevelFolder::ID> Level::getConnectedLevels()
{
	for (std::map<PortalId, Portal*>::const_iterator it = mPortals.begin(); it != mPortals.end(); it++)
		MConnectedLevels.push_back(it->second->getConnectedLevel());
	return MConnectedLevels;
}