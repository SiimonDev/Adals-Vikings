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
	// Set all the loads to zero
	for (int i = 0; i < Textures::SIZE; i++)
		mTextureCountMap[static_cast<Textures::ID>(i)] = 0;

	for (int i = 0; i < Images::SIZE; i++)
		mImageCountMap[static_cast<Images::ID>(i)] = 0;

	for (int i = 0; i < Fonts::SIZE; i++)
		mFontCountMap[static_cast<Fonts::ID>(i)] = 0;

	for (int i = 0; i < Sound::SIZE; i++)
		mSoundCountMap[static_cast<Sound::ID>(i)] = 0;

	for (int i = 0; i < TextureFolder::SIZE; i++)
		mTextureFolderCountMap[static_cast<TextureFolder::ID>(i)] = 0;

	for (int i = 0; i < SoundFolder::SIZE; i++)
		mSoundFolderCountMap[static_cast<SoundFolder::ID>(i)] = 0;
}

/* ====== Load functions ======== */
void ResourceManager::loadResource(Textures::ID id, const std::string& filename)
{
	std::cout << "Loading Texture: " << filename << std::endl;
	if (mTextureCountMap[id] == 0)
	{
		TexturePtr texture(new sf::Texture());
		texture->loadFromFile(filename);
		texture->setSmooth(true);
		mTextureMap.insert(std::make_pair(id, std::move(texture)));
	}
	mTextureCountMap[id]++;
}
void ResourceManager::loadResource(Images::ID id, const std::string &filename)
{
	std::cout << "Loading Image: " << filename << std::endl;
	if (mImageCountMap[id] == 0)
	{
		ImagePtr image(new sf::Image());
		image->loadFromFile(filename);
		mImageMap.insert(std::make_pair(id, std::move(image)));
	}
	mImageCountMap[id]++;
}
void ResourceManager::loadResource(Fonts::ID id, const std::string& filename)
{
	std::cout << "Loading Font: " << filename << std::endl;
	if (mFontCountMap[id] == 0)
	{
		FontPtr font(new sf::Font());
		font->loadFromFile(filename);
		mFontMap.insert(std::make_pair(id, std::move(font)));
	}
	mFontCountMap[id]++;
}
void ResourceManager::loadResource(Sound::ID id, const std::string& filename)
{
	std::cout << "Loading Sound: " << filename << std::endl;
	if (mSoundCountMap[id] == 0)
	{
		SoundPtr sound(new sf::SoundBuffer());
		sound->loadFromFile(filename);
		mSoundMap.insert(std::make_pair(id, std::move(sound)));
	}
	mSoundCountMap[id]++;
}
void ResourceManager::loadResource(TextureFolder::ID id, const std::string &directory)
{
	if (mTextureFolderCountMap[id] == 0)
	{
		TextureFolderPtr mFolderVector;
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
	mTextureFolderCountMap[id]++;
}
void ResourceManager::loadResource(SoundFolder::ID id, const std::string &directory)
{
	if (mSoundFolderCountMap[id] == 0)
	{
		SoundFolderPtr mSoundVector;
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
	mSoundFolderCountMap[id]++;
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
void ResourceManager::unloadResource(Textures::ID id)
{
	if (mTextureCountMap[id] == 1)
		mTextureMap.erase(id);

	if (mTextureCountMap[id] > 0)
		mTextureCountMap[id]--;
}
void ResourceManager::unloadResource(Images::ID id)
{
	if (mImageCountMap[id] == 1)
		mImageMap.erase(id);

	if (mImageCountMap[id] > 0)
		mImageCountMap[id]--;
}
void ResourceManager::unloadResource(Fonts::ID id)
{
	if (mFontCountMap[id] == 1)
		mFontMap.erase(id);

	if (mFontCountMap[id] > 0)
		mFontCountMap[id]--;
}
void ResourceManager::unloadResource(Sound::ID id)
{
	if (mSoundCountMap[id] == 1)
		mSoundMap.erase(id);

	if (mSoundCountMap[id] > 0)
		mSoundCountMap[id]--;
}
void ResourceManager::unloadResource(TextureFolder::ID id)
{
	if (mTextureFolderCountMap[id] == 1)
	{
		mTextureFolderMap[id].clear();
		mTextureFolderMap.erase(id);
	}

	if (mTextureFolderCountMap[id] > 0)
		mTextureFolderCountMap[id]--;
}
void ResourceManager::unloadResource(SoundFolder::ID id)
{
	if (mSoundFolderCountMap[id] == 1)
	{
		mSoundFolderMap[id].clear();
		mSoundFolderMap.erase(id);
	}

	if (mSoundFolderCountMap[id] > 0)
		mSoundFolderCountMap[id]--;
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
	for (int i = 0; i < Textures::SIZE; i++)
		mTextureCountMap[static_cast<Textures::ID>(i)] = 0;

	mTextureMap.clear();
}
void ResourceManager::truncateImages()
{
	for (int i = 0; i < Images::SIZE; i++)
		mImageCountMap[static_cast<Images::ID>(i)] = 0;

	mImageMap.clear();
}
void ResourceManager::truncateFonts()
{
	for (int i = 0; i < Fonts::SIZE; i++)
		mFontCountMap[static_cast<Fonts::ID>(i)] = 0;
	mFontMap.clear();
}
void ResourceManager::truncateSounds()
{
	for (int i = 0; i < Sound::SIZE; i++)
		mSoundCountMap[static_cast<Sound::ID>(i)] = 0;
	mSoundMap.clear();
}
void ResourceManager::truncateTextureFolders()
{
	for (int i = 0; i < TextureFolder::SIZE; i++)
		mTextureFolderCountMap[static_cast<TextureFolder::ID>(i)] = 0;

	for (std::map<TextureFolder::ID, TextureFolderPtr>::iterator it = mTextureFolderMap.begin(); it != mTextureFolderMap.end(); ++it)
		it->second.clear();

	mTextureFolderMap.clear();
}
void ResourceManager::truncateSoundFolders()
{
	for (int i = 0; i < SoundFolder::SIZE; i++)
		mSoundFolderCountMap[static_cast<SoundFolder::ID>(i)] = 0;

	for (std::map<SoundFolder::ID, SoundFolderPtr>::iterator it = mSoundFolderMap.begin(); it != mSoundFolderMap.end(); ++it)
		it->second.clear();

	mSoundFolderMap.clear();
}


/* ====== Get functions ======== */
const TextureFolderPtr &ResourceManager::getResource(TextureFolder::ID id) const
{
	auto found = mTextureFolderMap.find(id);
	return found->second;
}
const SoundFolderPtr &ResourceManager::getResource(SoundFolder::ID id) const
{
	auto found = mSoundFolderMap.find(id);
	return found->second;
}
sf::Image &ResourceManager::getResource(Images::ID id) const
{
	auto found = mImageMap.find(id);
	return *found->second;
}
sf::Texture &ResourceManager::getResource(Textures::ID id) const
{
	auto found = mTextureMap.find(id);
	return *found->second;
}
sf::Font &ResourceManager::getResource(Fonts::ID id) const
{
	auto found = mFontMap.find(id);
	return *found->second;
}
sf::SoundBuffer &ResourceManager::getResource(Sound::ID id) const
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


/* ====== Helper Functions ===== */
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
		std::cout << std::endl << "--- Loading Footsteps ---" << std::endl;
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