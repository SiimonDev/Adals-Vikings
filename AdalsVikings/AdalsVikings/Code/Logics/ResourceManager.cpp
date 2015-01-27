#include "ResourceManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <External\dirent.h>

ResourceManager &ResourceManager::GetInstance()
{
	static ResourceManager instance;
	return instance;
}
ResourceManager::ResourceManager()
{

}
ResourceManager::~ResourceManager()
{

}

std::vector<std::string>getAllBackgroundFilesFromFolder(const std::string &directory)
{
	DIR *dir;
	struct dirent *dirnt;
	std::vector<std::string> filePaths;

	if ((dir = opendir(directory.c_str())) != NULL)
	{
		while ((dirnt = readdir(dir)) != NULL)
		{
			std::string path = dirnt->d_name;
			if (path.find("ml_") != std::string::npos) 
			{
				filePaths.push_back(directory + dirnt->d_name);
			}
		}
		closedir(dir);

		for each (std::string s in filePaths)
			std::cout << s << " Loaded"<< std::endl;
	}
	else 
	{
		std::cout << "Could not find dir" << std::endl;
	}

	return filePaths;
}

void ResourceManager::load(Folder::ID id, const std::string &directory)
{
	std::vector<std::string> filePaths = getAllBackgroundFilesFromFolder(directory);

	for (int i = 0; i < filePaths.size(); i++)
	{
		mFolderVector.push_back(new sf::Texture());
		mFolderVector[i]->loadFromFile(filePaths.at(i));
	}
	mFolderMap.insert(std::make_pair(id, std::move(mFolderVector)));

	for (int i = 0; i < mFolderVector.size(); i++)
	{
		delete mFolderVector[i];
		mFolderVector.erase(mFolderVector.begin() + i);
	}
}
void ResourceManager::load(Textures::ID id, const std::string& filename)
{
	TexturePtr texture(new sf::Texture());
	texture->loadFromFile(filename);
	mTextureMap.insert(std::make_pair(id, std::move(texture)));
}
void ResourceManager::load(Fonts::ID id, const std::string& filename)
{
	FontPtr font(new sf::Font());
	font->loadFromFile(filename);
	mFontMap.insert(std::make_pair(id, std::move(font)));
}

void ResourceManager::unload(Folder::ID id)
{
	mFolderMap.erase(id);
}
void ResourceManager::unload(Textures::ID id)
{
	mTextureMap.erase(id);
}
void ResourceManager::unload(Fonts::ID id)
{
	mFontMap.erase(id);
}

FolderPtr &ResourceManager::getFolder(Folder::ID id)
{
	auto found = mFolderMap.find(id);

	return found->second;
}
sf::Texture &ResourceManager::getTexture(Textures::ID id) const
{
	auto found = mTextureMap.find(id);
	return *found->second;
}
sf::Font &ResourceManager::getFont(Fonts::ID id) const
{
	auto found = mFontMap.find(id);
	return *found->second;
}