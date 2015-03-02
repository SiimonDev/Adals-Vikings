#pragma once
#include "..\Logics\ResourceManager.h"
#include "..\Logics\IndexRenderer.h"
#include "..\Dialog\Dialog.h"
#include "..\Logics\Animation.h"
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>

enum ObjectType
{
	Standard,
	Animated,
	Invisible
};

class Object
{
public:
	Object(Font::ID font, std::string filePath);

	void load();
	void unload();

	void update(sf::Time &frameTime);
	void render(IndexRenderer &IRenderer);

	void setInteractionPosition(sf::Vector2f &interPos);
	void setIndex(int index);
	void setPosition(sf::Vector2f &position);
	void setCollisionRect(sf::IntRect &rect);
	void setScale(sf::Vector2f &scale);
	void setScaleFromWidth(float width);
	void setScaleFromHeight(float height);
	void setDescription(std::string description);
	void enableCollision(bool active);
	void enableDescription(bool active);

	std::string getObjID();
	std::string getName();

	CombineDialog combineWithObject(std::string id);
	Dialog interactWithObject(std::string id);
	Dialog getDenyDialog(std::string id);
	Dialog getPickupDialog();
	Dialog getLookAtDialog();

	sf::Vector2f &getPosition();
	sf::Vector2f &getInteractionPosition();
	sf::Vector2f getSize();
	sf::Vector2f getScale();
	sf::IntRect &getCollisionRect();
	sf::Sprite &getSprite();

	int getIndex();
	bool isInside(sf::Vector2i &pos);
	bool isPickupable();
	bool hasCollision();

private:
	void readVariablesFromFile();

	std::string mName;
	std::string mObjectID;
	std::string mFileID;
	std::string mFolderPath;
	std::string mFilePath;
	std::string mImagePath;

	Dialog mLookAtDialog, mPickupDialog, mDenyDialog;

	ObjectType mType;
	Animation mAnimation;
	sf::RectangleShape mTextRect;
	sf::RectangleShape mRect;
	sf::Vector2f mPosition;
	sf::Vector2f mInteractionPosition;
	sf::Vector2f mScale;
	sf::Vector2i mSize;
	sf::Sprite mSprite;
	sf::IntRect mCollisionRect;
	sf::Text mDescription;

	bool mCollision;
	bool mCanPickUp;
	bool mDisplayDescription;
	int mIndex;

	std::map<std::string, Dialog> mInteractDialogs;
	std::map<std::string, Dialog> mDenyDialogs;
	std::map<std::string, CombineDialog> mCombineObjects;
};

