#include "ResourceManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <External\dirent.h>

ResourceManager &ResourceManager::getInstance()
{
	static std::unique_ptr<ResourceManager> instance;

	if (instance == NULL)
		instance = std::unique_ptr<ResourceManager>(new ResourceManager());

	return *instance;
}

ResourceManager::ResourceManager()
{

}

bool compareLX(std::string &a, std::string &b)
{
	int aI = atoi(&a.c_str()[a.find("ml_L") + 4]);
	int bI = atoi(&b.c_str()[b.find("ml_L") + 4]);

	return (aI < bI);
}

std::vector<std::string> ResourceManager::getAllBackgroundFilesFromFolder(const std::string &directory)
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

		std::sort(filePaths.begin(), filePaths.end(), compareLX);
		std::cout << std::endl << "--- Loading Map Layers ---" << std::endl;
		for each (std::string s in filePaths)
		{
			std::cout << s << std::endl;
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Could not find dir" << std::endl;
	}
	dir = 0;
	dirnt = 0;
	return filePaths;
}

std::vector<std::string> ResourceManager::getAllFootstepsFromFolder(const std::string &directory)
{
	DIR *dir;
	struct dirent *dirnt;
	std::vector<std::string> filePaths;

	if ((dir = opendir(directory.c_str())) != NULL)
	{
		while ((dirnt = readdir(dir)) != NULL)
		{
			std::string path = dirnt->d_name;
			if (path.find("step") != std::string::npos)
			{
				filePaths.push_back(directory + dirnt->d_name);
			}
		}
		closedir(dir);

		std::sort(filePaths.begin(), filePaths.end(), compareLX);
		std::cout << std::endl << "--- Loading Map Layers ---" << std::endl;
		for each (std::string s in filePaths)
		{
			std::cout << s << std::endl;
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Could not find dir" << std::endl;
	}
	dir = 0;
	dirnt = 0;
	return filePaths;
}
std::string ResourceManager::getRCFileFromFolder(const std::string &directory)
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
				return filePath;
			}
		}
		closedir(dir);
	}
	else
	{
		std::cout << "Could not find RC dir" << std::endl;
	}

	std::cout << "No RC file found" << std::endl;
	return "";
}
std::string ResourceManager::getIndexFileFromFolder(const std::string &directory)
{
	DIR *dir;
	struct dirent *dirnt;
	std::string filePath;

	if ((dir = opendir(directory.c_str())) != NULL)
	{
		while ((dirnt = readdir(dir)) != NULL)
		{
			std::string path = dirnt->d_name;
			if (path.find("im_") != std::string::npos)
			{
				filePath = directory + dirnt->d_name;
				return filePath;
			}
		}
		closedir(dir);
	}
	else
	{
		std::cout << "Could not find Index dir" << std::endl;
	}

	std::cout << "No Index file found" << std::endl;
	return "";
}


/* ====== Load functions ======== */
void ResourceManager::load(Images::ID id, const std::string &directory)
{
	ImagePtr image(new sf::Image());
	image->loadFromFile(directory);
	mImageMap.insert(std::make_pair(id, std::move(image)));
}
void ResourceManager::load(TextureFolder::ID id, const std::string &directory)
{
	std::vector<std::string> filePaths = getAllBackgroundFilesFromFolder(directory);

	for (int i = 0; i < filePaths.size(); i++)
	{
		mFolderVector.push_back(TexturePtr(new sf::Texture()));
		mFolderVector[i]->loadFromFile(filePaths.at(i));
	}
	mTextureFolderMap.insert(std::make_pair(id, std::move(mFolderVector)));

	mFolderVector.clear();
	filePaths.clear();
}
void ResourceManager::load(SoundFolder::ID id, const std::string &directory)
{
	std::vector<std::string> filePaths = getAllFootstepsFromFolder(directory);

	for (int i = 0; i < filePaths.size(); i++)
	{
		mSoundVector.push_back(SoundPtr(new sf::SoundBuffer()));
		mSoundVector[i]->loadFromFile(filePaths.at(i));
	}
	mSoundFolderMap.insert(std::make_pair(id, std::move(mSoundVector)));

	mSoundVector.clear();
	filePaths.clear();
}
void ResourceManager::load(Textures::ID id, const std::string& filename)
{
	std::cout << "Loading Texture: " << filename << std::endl;
	TexturePtr texture(new sf::Texture());
	texture->loadFromFile(filename);
	texture->setSmooth(true);
	mTextureMap.insert(std::make_pair(id, std::move(texture)));
}
void ResourceManager::load(Fonts::ID id, const std::string& filename)
{
	std::cout << "Loading Font: " << filename << std::endl;
	FontPtr font(new sf::Font());
	font->loadFromFile(filename);
	mFontMap.insert(std::make_pair(id, std::move(font)));
}
void ResourceManager::load(Sound::ID id, const std::string& filename)
{
	std::cout << "Loading Sound: " << filename << std::endl;
	SoundPtr sound(new sf::SoundBuffer());
	sound->loadFromFile(filename);
	mSoundMap.insert(std::make_pair(id, std::move(sound)));
}
void ResourceManager::loadTexture(const std::string &filename)
{
	std::cout << "Loading Dynamic Texture: " << filename << std::endl;
	TexturePtr texture(new sf::Texture());
	texture->loadFromFile(filename);
	texture->setSmooth(true);
	mNonIDTextures.insert(std::make_pair(filename, std::move(texture)));
}
void ResourceManager::loadImage(const std::string &filename)
{
	std::cout << "Loading Dynamic Image: " << filename << std::endl;
	ImagePtr image(new sf::Image());
	image->loadFromFile(filename);
	mNonIDImages.insert(std::make_pair(filename, std::move(image)));
}


/* ====== Unload functions ======== */
void ResourceManager::unload(Images::ID id)
{
	mImageMap.erase(id);
}
void ResourceManager::unload(TextureFolder::ID id)
{
	for (int i = 0; i < mTextureFolderMap[id].size(); i++)
		mTextureFolderMap[id].clear();
}
void ResourceManager::unload(SoundFolder::ID id)
{
	for (int i = 0; i < mSoundFolderMap[id].size(); i++)
		mSoundFolderMap[id].clear();
}
void ResourceManager::unload(Textures::ID id)
{
	mTextureMap.erase(id);
}
void ResourceManager::unload(Fonts::ID id)
{
	mFontMap.erase(id);
}
void ResourceManager::unload(Sound::ID id)
{
	mSoundMap.erase(id);
}
void ResourceManager::unloadTexture(const std::string &filename)
{
	mNonIDTextures.erase(filename);
}
void ResourceManager::unloadImage(const std::string &filename)
{
	mNonIDImages.erase(filename);
}


/* ====== Truncate functions ======== */
void ResourceManager::truncateTextures()
{
	mTextureMap.clear();
}
void ResourceManager::truncateImages()
{
	mImageMap.clear();
}
void ResourceManager::truncateTextureFolders()
{
	for (std::map<TextureFolder::ID, TextureFolderPtr>::iterator it = mTextureFolderMap.begin(); it != mTextureFolderMap.end(); ++it)
		it->second.clear();
	mTextureFolderMap.clear();
}
void ResourceManager::truncateSoundFolders()
{
	for (std::map<SoundFolder::ID, SoundFolderPtr>::iterator it = mSoundFolderMap.begin(); it != mSoundFolderMap.end(); ++it)
		it->second.clear();
	mSoundFolderMap.clear();
}
void ResourceManager::truncateSounds()
{
	mSoundMap.clear();
}
void ResourceManager::truncateFonts()
{
	mFontMap.clear();
}


/* ====== Get functions ======== */
sf::Image &ResourceManager::getImage(Images::ID id)
{
	auto found = mImageMap.find(id);
	return *found->second;
}
TextureFolderPtr &ResourceManager::getTextureFolder(TextureFolder::ID id)
{
	auto found = mTextureFolderMap.find(id);
	return found->second;
}
SoundFolderPtr &ResourceManager::getSoundFolder(SoundFolder::ID id)
{
	auto found = mSoundFolderMap.find(id);
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
sf::SoundBuffer &ResourceManager::getSoundBuffer(Sound::ID id) const
{
	auto found = mSoundMap.find(id);
	return *found->second;
}
sf::Texture &ResourceManager::getNonIDTexture(const std::string &filename) const
{
	auto found = mNonIDTextures.find(filename);
	return *found->second;
}
sf::Image &ResourceManager::getNonIDImage(const std::string &filename) const
{
	auto found = mNonIDImages.find(filename);
	return *found->second;
}