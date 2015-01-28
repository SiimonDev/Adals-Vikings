#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include "..\Logics\ResourceManager.h"
#include "ObjectHandler.h"

class Object
{
public:
	

	Object(std::string objectID, std::string filePath, Textures::ID textureID);
	~Object();

	void render(sf::RenderWindow &window);
	void update(sf::Time &time);

	void load();
	void unload();

	bool interactWithItem(Object *object);
	std::string combineObjects(Object *object);

	std::string getObjID();
	std::string getName();
	std::string getLookAtDialog();
	float getLookAtDialogTimer();
	std::string getUseDialog();
	float getUseDialogTimer();
	std::string getCantUseDialog();
	float getCantUseDialogTimer();
	bool getCanPickUp();
private:
	std::string mObjectID;
	std::string mFileID;
	std::string mFilePath;
	Textures::ID mTextureID;
	std::string mName, mLookAtDialog, mUseDialog, mCantUseDialog;
	float mLookAtDialogTimer, mUseDialogTimer, mCantUseDialogTimer;
	sf::Sprite mSprite;
	bool mCanPickUp;
	std::vector<std::string> mInteractableWith;
	std::map<std::string, std::string> mCreatedObjects; //key: itemID of item combined with; value: itemID of created item
	std::map<std::string, std::string> mSpecificCantUseDialog;
	void readVariables();
};

