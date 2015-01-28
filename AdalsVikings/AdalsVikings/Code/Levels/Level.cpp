#include "Level.h"
#include <iostream>
#include <vector>
#include <string>

Level::Level()
{
}

Level::~Level()
{
}

void Level::update(sf::Time &frametime)
{
	if (mouseState.isReleased(sf::Mouse::Left, 1))
	{
		Path path = PathFinder::getPath(mPlayer.getPosition(), sf::Vector2f(MouseState::getMousePosition()));
		mPlayer.walkPath(path);
	}
}

std::string getCollisionFileFromFolder(const std::string &directory)
{
	DIR *dir;
	struct dirent *dirnt;
	std::string filePath;

	if ((dir = opendir(directory.c_str())) != NULL)
	{
		while ((dirnt = readdir(dir)) != NULL)
		{
			std::string path = dirnt->d_name;
			if (path.find("rc_") != std::string::npos)
			{
				filePath = directory + dirnt->d_name;
				std::cout << "RCFile: " << filePath << " Loaded" << std::endl;
				return filePath;
			}
		}
		closedir(dir);
	}
	else
	{
		std::cout << "Could not find dir" << std::endl;
	}

	std::cout << "No RC file found" << std::endl;
	return "";
}

void Level::loadAllBackgrounds(std::string filepath)
{
	mRCImage.loadFromFile(getCollisionFileFromFolder(filepath));
	mTileMap.setTiles(sf::Vector2i(15, 15), mRCImage);

	ResourceManager::GetInstance().load(Folder::TestLevel, filepath);
	for (int i = 0; i < ResourceManager::GetInstance().getFolder(Folder::TestLevel).size(); i++)
	{
		mBackgrounds.push_back(mv::ISprite(*ResourceManager::GetInstance().getFolder(Folder::TestLevel).at(i), i * 10));
	}
}