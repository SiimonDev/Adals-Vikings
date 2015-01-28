#include "Object.h"
#include <SFML/Graphics.hpp>
#include "..\Logics\LevelManager.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>

static std::string itemFilePath = "Assets\\Textfiles\\Items.txt";

Object::Object(std::string objectID, std::string filePath, Textures::ID textureID) : mObjectID(objectID), mFilePath(filePath), mTextureID(textureID)
{
	readVariables();
}


Object::~Object()
{
}

void Object::render(sf::RenderWindow &window)
{
	window.draw(mSprite);
}

void Object::update(sf::Time &time)
{
	
}

void Object::load()
{
	ResourceManager::GetInstance().load(mTextureID, mFilePath);
	mSprite.setTexture(ResourceManager::GetInstance().getTexture(mTextureID));
}

void Object::unload()
{
	ResourceManager::GetInstance().unload(mTextureID);
}

bool Object::interactWithItem(Object *object)
{
	if (std::find(mInteractableWith.begin(), mInteractableWith.end(), object->getObjID()) != mInteractableWith.end()){
		return true;
	}
	return false;

}

std::string Object::combineObjects(Object *object){
	
	std::map<std::string, std::string>::iterator search = mCreatedObjects.find(object->getObjID());
	if (search != mCreatedObjects.end()){
		return search->second;
	}
	return "";
}

std::string Object::getName()
{
	return mName;
}

std::string Object::getObjID()
{
	return mObjectID;
}

std::string Object::getLookAtDialog()
{
	return mLookAtDialog;
}

float Object::getLookAtDialogTimer()
{
	return mLookAtDialogTimer;
}

std::string Object::getUseDialog()
{
	return mUseDialog;
}

float Object::getUseDialogTimer()
{
	return mUseDialogTimer;
}

std::string Object::getCantUseDialog()
{
	return mCantUseDialog;
}

float Object::getCantUseDialogTimer()
{
	return mCantUseDialogTimer;
}

bool Object::getCanPickUp()
{
	return mCanPickUp;
}

void Object::readVariables()
{
	std::ifstream itemFile(itemFilePath);
	std::string line = "";
	std::string word = "";
	std::stringstream ss;
	
	std::string  itemID = "$" + mObjectID + "$";
	while (itemFile.good())
	{
		std::getline(itemFile, line);
		if (line == itemID)
		{

			/*********************************************************/
			/*					mName							 	 */
			/*********************************************************/
			std::getline(itemFile, line); //set the variable mName
			line.erase(0, 5);
			mName = line;

			/*********************************************************/
			/*					mUseDialog						 	 */
			/*********************************************************/
			std::getline(itemFile, line);
			line.erase(0, 5);
			line.erase(std::remove(line.begin(), line.end(), '"'), line.end());
			if (line != "")
			{
				std::string segment = "";
				std::vector<std::string> segvector;
				std::stringstream linestream;
				linestream << line;

				while (std::getline(linestream, segment, '~')) //splits the  line at ~
				{
					segvector.push_back(segment);
				}

				mUseDialog = segvector[0];
				mUseDialogTimer = std::stof(segvector[1]);
			}
			else
			{
				mUseDialog = "Default use dialog";
				mUseDialogTimer = 0.7;
			}

			/*********************************************************/
			/*					mLookAtDialog					 	 */
			/*********************************************************/
			std::getline(itemFile, line); //set the lookatdialog
			line.erase(0, 7);
			line.erase(std::remove(line.begin(), line.end(), '"'), line.end());
			if (line != "")
			{
				std::string segment = "";
				std::vector<std::string> segvector;
				std::stringstream linestream;
				linestream << line;

				while (std::getline(linestream, segment, '~')) //splits the  line at ~
				{
					segvector.push_back(segment);
				}

				mLookAtDialog = segvector[0];
				mLookAtDialogTimer = std::stof(segvector[1]);
			}
			else
			{
				mLookAtDialog = "Default look at dialog";
				mLookAtDialogTimer = 0.7;
			}

			/*********************************************************/
			/*					mCombineItems					 	 */
			/*********************************************************/
			std::string combinedWithItem;
			std::string createdItem;
			std::getline(itemFile, line);
			line.erase(0, 9);
			ss << line;
			std::cout << "mCombineWith: " << line << std::endl;
			if (line != "")
			{
				for (int i = 1; ss >> combinedWithItem; i += 2)
				{
					combinedWithItem.erase(std::remove(combinedWithItem.begin(), combinedWithItem.end(), '$'), combinedWithItem.end());
					std::cout << "combineItems: " << combinedWithItem << std::endl;
					ss >> createdItem;
					createdItem.erase(std::remove(createdItem.begin(), createdItem.end(), '$'), createdItem.end());
					std::cout << "combineItems: " << createdItem << std::endl;
					mCreatedObjects[combinedWithItem] = createdItem;
				}
			}


			/*********************************************************/
			/*					mInteractableWIth				 	 */
			/*********************************************************/
			std::getline(itemFile, line);//set variables mInteractableWith
			line.erase(0, 10);
			ss << line;
			
			if (line != "")
			{
				for (int i = 1; ss >> word; i++)
				{
					word.erase(std::remove(word.begin(), word.end(), '$'), word.end());
					mInteractableWith.push_back(word);
					std::cout << "interactable: " << word << std::endl;
				}
			}

			/*********************************************************/
			/*					mCanPickUp						 	 */
			/*********************************************************/
			std::getline(itemFile, line); //set variable mCanPickUp
			line.erase(0, 8);
			if (line == "true")
			{
				mCanPickUp = true;
				std::cout << "This item can be picked up" << std::endl;
			} 
			else
			{
				mCanPickUp = false;
				std::cout << "This item can not be picked up" << std::endl;
			}

			/*********************************************************/
			/*					mCantUseDialog					 	 */
			/*********************************************************/
			std::getline(itemFile, line); //set variable mCantUseDialog
			line.erase(0, 4);
			//removes the " from the line
			line.erase(std::remove(line.begin(), line.end(), '"'), line.end());
			if (line != "")
			{
				std::string segment = "";
				std::vector<std::string> segvector;
				std::stringstream linestream;
				linestream << line;

				while (std::getline(linestream, segment, '~')) //splits the  line at ~
				{
					segvector.push_back(segment);
				}

				mCantUseDialog = segvector[0];
				mCantUseDialogTimer = std::stof(segvector[1]);
			}
			else
			{
				mCantUseDialog = "Default cant use dialog";
				mCantUseDialogTimer = 0.7;
			}

			/*********************************************************/
			/*					mDenyWith						 	 */
			/*********************************************************/
			std::getline(itemFile, line);
			//implement the code for getting the denywith map
			line.erase(0, 10);
			std::cout << "mDenyWith: " << line << std::endl;
			if (line != "")
			{	
				if (line.find('|') != std::string::npos)
				{
					std::cout << "Found a |" << std::endl;

						
				}
				else
				{
					std::cout << "did not find a | " << std::endl;
					std::string segment = "";
					std::vector<std::string> segvector;
					std::stringstream linestream;
					linestream << line;

					while (std::getline(linestream, segment, '~')) //splits the  line at ~
					{
						segvector.push_back(segment);
					}
					mSpecificCantUseDialog[segvector[0]] = segvector[1];
				}
			}
		}
	}
	
}