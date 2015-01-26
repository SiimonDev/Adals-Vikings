#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include "..\Logics\ResourceManager.h"


class Object
{
public:
	enum ObjID{
		Rock
	};

	Object(ObjID objectID, std::string filePath, Textures::ID textureID);
	~Object();

	void render(sf::RenderWindow &window);
	void update(sf::Time &time);

	void load();
	void unload();

private:
	ObjID mObjectID;
	std::string mFilePath;
	Textures::ID mTextureID;
	std::string mName, mLookAtDialog, mUsDialog, mCantUseDialog;
	sf::Sprite mSprite;
	bool mCanPickUp;
};

