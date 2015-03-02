#include "Object.h"
#include "..\Logics\ResourceManager.h"
#include "..\Logics\KeyboardState.h"
#include "..\Logics\MouseState.h"
#include "..\Logics\Debug.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>

Object::Object(Font::ID font, std::string filePath) :
mFilePath(filePath), mCollision(true), mDisplayDescription(false), mScale(1, 1)
{
	int index = mFilePath.find_last_of("/");
	mFolderPath = mFilePath.substr(0, index + 1);

	readVariablesFromFile(); 

	mDescription.setFont(RMI.getResource(font));
	mDescription.setString(mName);
	mTextRect.setFillColor(sf::Color(0, 0, 0, 200));
}

void Object::load()
{
	if (mType == ObjectType::Standard){
		RMI.loadTexture(mImagePath);
		mSprite.setTexture(RMI.getNonIDTexture(mImagePath));
		mSize.x = RMI.getNonIDTexture(mImagePath).getSize().x;
		mSize.y = RMI.getNonIDTexture(mImagePath).getSize().y;
		mSprite.setOrigin(sf::Vector2f(mSize.x / 2, mSize.y / 2));
	}
	else if (mType == ObjectType::Animated){
		RMI.loadTexture(mImagePath);
		mAnimation.setSpriteSize(RMI.getNonIDTexture(mImagePath), mAnimation.getFrames());
		mSize.x = abs(mAnimation.getSprite().getTextureRect().width);
		mSize.y = abs(mAnimation.getSprite().getTextureRect().height);
		mAnimation.getSprite().setOrigin(mSize.x / 2, mSize.y / 2);
	}
	else if (mType == ObjectType::Invisible)
	{
		mRect = sf::RectangleShape(sf::Vector2f(mSize.x, mSize.y));
		mRect.setFillColor(sf::Color(255, 0, 0, 255));
	}

	float objWidth = float(mSize.x * mScale.x);
	float objHeight = float(mSize.y * mScale.y);
	float xPos = mPosition.x - (objWidth / 2);
	float yPos = mPosition.y + ((objHeight / 2) - objHeight * 0.2f);

	if (mCollision)
		mCollisionRect = sf::IntRect(sf::IntRect(xPos, yPos, objWidth, objHeight * 0.2f));
	else
		mCollisionRect = sf::IntRect(sf::IntRect(0, 0, 0, 0));
}

void Object::unload()
{
	RMI.unloadTexture(mImagePath);
}

void Object::update(sf::Time &frameTime)
{
	if (mType == ObjectType::Animated)
		mAnimation.animate(frameTime);

	if (mDisplayDescription)
	{
		mDescription.setPosition(sf::Vector2f(mPosition.x - (mDescription.getGlobalBounds().width / 2), mPosition.y - (mDescription.getGlobalBounds().height) - ((mSize.y * mScale.y) / 2)));

		mTextRect.setSize(sf::Vector2f(mDescription.getGlobalBounds().width + 10, mDescription.getGlobalBounds().height + 10));
		mTextRect.setPosition(sf::Vector2f(mPosition.x - (mTextRect.getGlobalBounds().width / 2), mPosition.y - (mTextRect.getGlobalBounds().height / 2) - ((mSize.y * mScale.y) / 2) + 3));
	}
}

void Object::render(IndexRenderer &iRenderer)
{
	if (mType == ObjectType::Standard){
		mSprite.setScale(mScale);
		mSprite.setPosition(mPosition);
		iRenderer.addSprite(mSprite, mIndex);
	}
	else if (mType == ObjectType::Animated){
		mAnimation.setScaleFromHeight(mScale.x * mSize.x);
		mAnimation.setPosition(mPosition);
		mAnimation.render(iRenderer);
	}
	else if (mType == ObjectType::Invisible){
		if (DebugMode){
			mRect.setPosition(sf::Vector2f(mPosition.x - (mSize.x / 2), mPosition.y - (mSize.y / 2)));
			iRenderer.addRectangle(mRect, mIndex);
		}
	}

	if (mDisplayDescription)
	{
		iRenderer.addRectangle(mTextRect, mIndex + 1);
		iRenderer.addText(mDescription, mIndex + 2);
	}
}

void Object::setInteractionPosition(sf::Vector2f &interPos)
{
	mInteractionPosition = interPos;
}

void Object::setIndex(int index)
{
	mIndex = index;
	mAnimation.setIndex(mIndex);
}

void Object::setPosition(sf::Vector2f &position)
{
	mPosition = position;
}

void Object::setCollisionRect(sf::IntRect &rect)
{
	mCollisionRect = rect;
}

void Object::setScale(sf::Vector2f &scale)
{
	mScale = scale;
}

void Object::setScaleFromWidth(float width)
{
	mScale.x = ((width / abs(mSprite.getTextureRect().width)));
	mScale.y = mScale.x;
}

void Object::setScaleFromHeight(float height)
{
	mScale.y = ((height / abs(mSprite.getTextureRect().height)));
	mScale.x = mScale.y;
}

void Object::setDescription(std::string description)
{
	mDescription.setString(description);
}

void Object::enableCollision(bool active)
{
	mCollision = active;
}

void Object::enableDescription(bool active)
{
	mDisplayDescription = active;
}

std::string Object::getName()
{
	return mName;
}
std::string Object::getObjID()
{
	return mObjectID;
}

Dialog Object::interactWithObject(std::string id)
{
	for (std::map<std::string, Dialog>::iterator it = mInteractDialogs.begin(); it != mInteractDialogs.end(); ++it)
	{
		if (it->first == id){
			return mInteractDialogs[id];
		}
	}

	return getDenyDialog(id);
}
CombineDialog Object::combineWithObject(std::string id)
{
	CombineDialog dialog;
	for (std::map<std::string, CombineDialog>::iterator it = mCombineObjects.begin(); it != mCombineObjects.end(); ++it)
	{
		if (it->first == id){
			return mCombineObjects[id];
		}
	}
	dialog.mDialog = getDenyDialog(id).mDialog;
	dialog.mTimer = getDenyDialog(id).mTimer;
	return dialog;
}
Dialog Object::getPickupDialog()
{
	return mPickupDialog;
}
Dialog Object::getDenyDialog(std::string id)
{
	for (std::map<std::string, Dialog>::iterator it = mDenyDialogs.begin(); it != mDenyDialogs.end(); ++it)
	{
		if (it->first == id){
			return mDenyDialogs[id];
		}
	}

	return mDenyDialog;
}
Dialog Object::getLookAtDialog()
{
	return mLookAtDialog;
}

sf::Vector2f &Object::getPosition()
{
	return mPosition;
}

sf::Vector2f &Object::getInteractionPosition()
{
	return mInteractionPosition;
}

sf::Vector2f Object::getSize()
{
	return sf::Vector2f(mSize.x * mScale.x, mSize.y * mScale.y);
}

sf::Vector2f Object::getScale()
{
	return mScale;
}

sf::IntRect &Object::getCollisionRect()
{
	return mCollisionRect;
}

sf::Sprite &Object::getSprite()
{
	return mSprite;
}

int Object::getIndex()
{
	return mIndex;
}

bool Object::isInside(sf::Vector2i &pos)
{
	return
		mPosition.x - ((mSize.x * mScale.x) / 2) <= pos.x  &&
		pos.x <= mPosition.x + ((mSize.x * mScale.x) / 2) &&
		mPosition.y - ((mSize.y * mScale.y) / 2) <= pos.y &&
		pos.y <= mPosition.y + ((mSize.y * mScale.y) / 2);
}
bool Object::isPickupable()
{
	return mCanPickUp;
}

bool Object::hasCollision()
{
	return mCollision;
}

void Object::readVariablesFromFile()
{
	////std::cout << "--- LOADING ITEM! ---" << std::endl;
	std::ifstream itemFile(mFilePath);
	std::string line;
	while (std::getline(itemFile, line))
	{
		if (line.find("*Type:") != std::string::npos)
		{
			line.erase(0, 7);
			std::string type = line;

			if (type == "standard")
				mType = ObjectType::Standard;
			else if (type == "animated")
				mType = ObjectType::Animated;
			else if (type == "invisible")
				mType = ObjectType::Invisible;

			////std::cout << "Type: " << type << std::endl;
		}
		else if (line.find("*ID:") != std::string::npos)
		{
			int start = line.find("$", 0);
			int end = line.find("$", start + 1);
			std::string subString = line.substr(start + 1, (end - start) - 1);

			mObjectID = subString;
			////std::cout << "ID: " << mObjectID << std::endl;
		}
		else if (line.find("*Name:") != std::string::npos)
		{
			line.erase(0, 7);
			mName = line;
			////std::cout << "Name: " << mName << std::endl;
		}
		else if (line.find("*ispickupable:") != std::string::npos)
		{
			line.erase(0, 15);
			mCanPickUp = (line == "True");
			////std::cout << "isPickupable: " << mCanPickUp << std::endl;
		}
		else if (line.find("*pickup:") != std::string::npos)
		{
			int start = line.find("\"", 0);
			int end = line.find("\"", start + 1);
			std::string dialogText = line.substr(start + 1, (end - start) - 1);

			start = line.find("~", 0);
			std::string dialogTimer = line.substr(start + 1, (line.size() - start) - 1);

			mPickupDialog.mDialog = dialogText;
			mPickupDialog.mTimer = atof(dialogTimer.c_str());

			//std::cout << "pickUpDialog: " << dialogText << "~" << mPickupDialog.mTimer << std::endl;
		}
		else if (line.find("*lookat:") != std::string::npos)
		{
			int start = line.find("\"", 0);
			int end = line.find("\"", start + 1);
			std::string dialogText = line.substr(start + 1, (end - start) - 1);

			start = line.find("~", 0);
			std::string dialogTimer = line.substr(start + 1, (line.size() - start) - 1);

			mLookAtDialog.mDialog = dialogText;
			mLookAtDialog.mTimer = atof(dialogTimer.c_str());

			//std::cout << "lookatDialog: " << dialogText << "~" << mLookAtDialog.mTimer << std::endl;
		}
		else if (line.find("*deny:") != std::string::npos)
		{
			int start = line.find("\"", 0);
			int end = line.find("\"", start + 1);
			std::string dialogText = line.substr(start + 1, (end - start) - 1);

			start = line.find("~", 0);
			std::string dialogTimer = line.substr(start + 1, (line.size() - start) - 1);

			mDenyDialog.mDialog = dialogText;
			mDenyDialog.mTimer = atof(dialogTimer.c_str());

			//std::cout << "denyDialog: " << dialogText << "~" << mDenyDialog.mTimer << std::endl;
		}
		else if (line.find("*denywith:") != std::string::npos)
		{
			std::string segment = "";
			std::stringstream linestream;
			linestream << line;

			while (std::getline(linestream, segment, ';')) //splits the  line at ;
			{
				if (segment.find("$") != std::string::npos)
				{
					// Get the ID
					int start = segment.find("$", 0);
					int end = segment.find("$", start + 1);
					std::string denyID = segment.substr(start + 1, (end - start) - 1);

					// Get the text
					start = segment.find("\"", 0);
					end = segment.find("\"", start + 1);
					std::string dialogText = segment.substr(start + 1, (end - start) - 1);

					start = segment.find("~", 0);
					std::string dialogTimer = segment.substr(start + 1, (segment.size() - start) - 1);

					Dialog dialog;
					dialog.mDialog = dialogText;
					dialog.mTimer = atof(dialogTimer.c_str());

					mDenyDialogs[denyID] = dialog;

					//std::cout << "denyWith: denyID: " << "$" << denyID << "$ " << dialogText << "~" << dialog.mTimer << std::endl;
				}
			}
		}
		else if (line.find("*combine:") != std::string::npos)
		{
			std::string segment = "";
			std::stringstream linestream;
			linestream << line;

			while (std::getline(linestream, segment, ';')) //splits the  line at ;
			{
				if (segment.find("$") != std::string::npos)
				{
					// Get the Object ID
					int start = segment.find("$", 0);
					int end = segment.find("$", start + 1);
					std::string combineID = segment.substr(start + 1, (end - start) - 1);

					// Get the Result ID
					start = segment.find("$", end + 1);
					end = segment.find("$", start + 1);
					std::string resultID = segment.substr(start + 1, (end - start) - 1);

					// Get the text
					start = segment.find("\"", 0);
					end = segment.find("\"", start + 1);
					std::string dialogText = segment.substr(start + 1, (end - start) - 1);

					start = segment.find("~", 0);
					std::string dialogTimer = segment.substr(start + 1, (segment.size() - start) - 1);

					CombineDialog dialog;
					dialog.mResultID = resultID;
					dialog.mDialog = dialogText;
					dialog.mTimer = atof(dialogTimer.c_str());

					mCombineObjects[combineID] = dialog;

					//std::cout << "Combine: combineID: $" << combineID << "$ " << " Resulting ID: $" << dialog.mResultID << "$ " << dialogText << "~" << dialog.mTimer << std::endl;
				}
			}
		}
		else if (line.find("*interact:") != std::string::npos)
		{
			std::string segment = "";
			std::stringstream linestream;
			linestream << line;

			while (std::getline(linestream, segment, ';')) //splits the  line at ;
			{
				if (segment.find("$") != std::string::npos)
				{
					// Get the ID
					int start = segment.find("$", 0);
					int end = segment.find("$", start + 1);
					std::string interactID = segment.substr(start + 1, (end - start) - 1);

					// Get the text
					start = segment.find("\"", 0);
					end = segment.find("\"", start + 1);
					std::string dialogText = segment.substr(start + 1, (end - start) - 1);

					start = segment.find("~", 0);
					std::string dialogTimer = segment.substr(start + 1, (segment.size() - start) - 1);

					Dialog dialog;
					dialog.mDialog = dialogText;
					dialog.mTimer = atof(dialogTimer.c_str());

					mInteractDialogs[interactID] = dialog;

					//std::cout << "Interact: InteractID: $" << interactID << "$ " << dialogText << "~" << dialog.mTimer << std::endl;
				}
			}
		}
		if (mType == ObjectType::Standard || mType == ObjectType::Animated)
		{
			if (line.find("*texture:") != std::string::npos)
			{
				int start = line.find("\"", 0);
				int end = line.find("\"", start + 1);
				std::string subString = line.substr(start + 1, (end - start) - 1);

				mImagePath = mFolderPath + subString;
				//std::cout << "Image: \"" << mImagePath << "\"" << std::endl;
			}
		}
		if (mType == ObjectType::Animated && line.find("*animation:") != std::string::npos)
		{
			int start = line.find("X:", 0);
			int end = line.find(" Y:", start + 1);
			std::string animeX = line.substr(start + 2, (end - start) - 1);

			start = line.find("Y:", 0);
			end = line.find(" ~", start + 1);
			std::string animeY = line.substr(start + 2, (end - start) - 1);

			mAnimation.setFrames(sf::Vector2i(atof(animeX.c_str()), atof(animeY.c_str())));

			start = line.find("~", 0);
			end = line.find(" ~", start + 1);
			double animeTime = atof(line.substr(start + 1, (end - start) - 1).c_str());
			mAnimation.setDuration(sf::seconds(animeTime));

			start = end + 1;
			end = line.size();
			double animeIdle = atof(line.substr(start + 1, (end - start) - 1).c_str());
			mAnimation.setIdleDuration(sf::seconds(animeIdle));
		}
		if (mType == ObjectType::Invisible && line.find("*invisible:") != std::string::npos)
		{
			int start = line.find("X:", 0);
			int end = line.find(" Y:", start + 1);
			std::string invisibleWidth = line.substr(start + 2, (end - start) - 1);
			mSize.x = atof(invisibleWidth.c_str());

			start = line.find("Y:", 0);
			end = line.size() - 1;
			std::string invisibleHeight = line.substr(start + 2, (end - start) - 1);
			mSize.y = atof(invisibleHeight.c_str());
		}
	}
	//std::cout << std::endl;
	itemFile.close();
}