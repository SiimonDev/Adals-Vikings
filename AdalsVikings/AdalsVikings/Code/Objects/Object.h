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
	Object(std::string filePath, std::string folderPath);

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
	void enableCollision(bool active);

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
	std::string mFolderPath;
	std::string mFileID;
	std::string mDocPath;
	std::string mImagePath;

	Dialog mLookAtDialog, mPickupDialog, mDenyDialog;

	ObjectType mType;
	Animation mAnimation;
	Textures::ID mTextureID;
	sf::RectangleShape mRect;
	sf::Vector2f mPosition;
	sf::Vector2f mInteractionPosition;
	sf::Vector2f mScale;
	sf::Vector2i mSize;
	sf::Sprite mSprite;
	sf::IntRect mCollisionRect;

	bool debuggMode;
	bool mCollision;
	bool mCanPickUp;
	int mIndex;

	std::map<std::string, Dialog> mInteractDialogs;
	std::map<std::string, Dialog> mDenyDialogs;
	std::map<std::string, CombineDialog> mCombineObjects;
};

