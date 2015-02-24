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

	/* ========== Set Texture File paths ========== */
	mTexturePathMap[Textures::UlfrWalk] = "assets/images/ulfr/character_ulfr_walk.png";
	mTexturePathMap[Textures::UlfrIdle] = "assets/images/ulfr/character_ulfr_idle.png";
	mTexturePathMap[Textures::UlfrFront] = "assets/images/ulfr/character_ulfr_front.png";
	mTexturePathMap[Textures::UlfrBack] = "assets/images/ulfr/character_ulfr_back.png";
	mTexturePathMap[Textures::UlfrStop] = "assets/images/ulfr/character_ulfr_stop.png";
	mTexturePathMap[Textures::UlfrTalkToNpc] = "assets/images/ulfr/character_ulfr_talk.png";
	mTexturePathMap[Textures::UlfrTalkToPlayer] = "assets/images/ulfr/character_ulfr_front.png";
	mTexturePathMap[Textures::UlfrPickup] = "assets/images/ulfr/character_ulfr_pickup.png";

	mTexturePathMap[Textures::Button1] = "assets/images/interface/Buttons/Button1.png";
	mTexturePathMap[Textures::Button1Dissabled] = "assets/images/interface/Buttons/Button1_grey.png";
	mTexturePathMap[Textures::LookButton] = "assets/images/interface/buttons/interface_look.png";
	mTexturePathMap[Textures::TakeButton] = "assets/images/interface/buttons/interface_take.png";
	mTexturePathMap[Textures::TalkButton] = "assets/images/interface/buttons/interface_talk.png";

	mTexturePathMap[Textures::MainMenuPlayButton] = "assets/images/interface/MainMenu/button_play.png";
	mTexturePathMap[Textures::MainMenuOptionsButton] = "assets/images/interface/MainMenu/button_options_disabled.png";
	mTexturePathMap[Textures::MainMenuQuitButton] = "assets/images/interface/MainMenu/button_quit.png";
	mTexturePathMap[Textures::MainMenuBackground] = "assets/images/Interface/MainMenu/menu_background.png";

	mTexturePathMap[Textures::PauseMenuResumeButton] = "assets/images/interface/pauseManu/button_resume.png";
	mTexturePathMap[Textures::PauseMenuSaveButton] = "assets/images/interface/pauseManu/button_save.png";
	mTexturePathMap[Textures::PauseMenuOptionsButton] = "assets/images/interface/pauseManu/button_options.png";
	mTexturePathMap[Textures::PauseMenuMainMenuButton] = "assets/images/interface/pauseManu/button_main_menu.png";
	mTexturePathMap[Textures::PauseMenuExitButton] = "assets/images/interface/pauseManu/button_exit.png";
	mTexturePathMap[Textures::PauseMenuBackground] = "assets/images/interface/pauseManu/InGame_menu.png";

	mTexturePathMap[Textures::WaveAnimation] = "assets/MapFiles/Beach/waves.png";
	mTexturePathMap[Textures::AxeAnimation] = "assets/images/Interface/MainMenu/flying_axe.png";

	mTexturePathMap[Textures::InventoryBackground] = "assets/images/Interface/inventory.png";
	mTexturePathMap[Textures::InventoryTile] = "assets/images/InventoryTile.png";

	mTexturePathMap[Textures::BrandrIdle] = "assets/images/Brandr/character_brandr_blink.png";
	mTexturePathMap[Textures::BrandrTalk] = "assets/images/Brandr/character_brandr_talk.png";
	mTexturePathMap[Textures::ValdisIdle] = "assets/images/Valdis/character_valdis_blink.png";
	mTexturePathMap[Textures::ValdisTalk] = "assets/images/Valdis/character_valdis_talk.png";
	mTexturePathMap[Textures::LeifrIdle] = "assets/images/Leifr/character_leifr_blink.png";
	mTexturePathMap[Textures::LeifrTalk] = "assets/images/Leifr/character_leifr_talk.png";
	mTexturePathMap[Textures::FinnrIdle] = "assets/images/finnr/character_finnr_blink.png";
	mTexturePathMap[Textures::FinnrTalk] = "assets/images/finnr/character_finnr_talk.png";
	mTexturePathMap[Textures::BrynjaIdle] = "assets/images/Brynja/character_brynja_blink.png";
	mTexturePathMap[Textures::BrynjaTalk] = "assets/images/Brynja/character_brynja_talk.png";
	mTexturePathMap[Textures::BrynjaSleeping] = "assets/images/Brynja/character_brynja_sleeping.png";
	mTexturePathMap[Textures::AlfrIdle] = "assets/images/Alfr/character_alfr.png";
	mTexturePathMap[Textures::AlfrTalk] = "assets/images/Alfr/character_alfr_talk.png";
	mTexturePathMap[Textures::DagnyIdle] = "assets/images/Dagny/character_dagny_blink.png";
	mTexturePathMap[Textures::DagnyTalk] = "assets/images/Dagny/character_dagny_talk.png";
	mTexturePathMap[Textures::YngvarrIdle] = "assets/images/Yngvarr/character_yngvarr_blink.png";
	mTexturePathMap[Textures::YngvarrTalk] = "assets/images/Yngvarr/character_yngvarr_talk.png";
	/* ============================================ */


	/* =========== Set Font File paths =========== */
	mFontPathMap[Fonts::ActionWheelDescription] = "assets/fonts/font1.ttf";
	mFontPathMap[Fonts::DialogWindow] = "Assets/fonts/font2.ttf";
	mFontPathMap[Fonts::MenuButtons] = "assets/fonts/font1.ttf";
	/* =========================================== */


	/* =========== Set Sound File paths =========== */
	mSoundPathMap[Sound::InventoryOpen] = "assets/sounds/Inventory(open).wav";
	mSoundPathMap[Sound::InventoryClose] = "assets/sounds/Inventory(close).wav";
	mSoundPathMap[Sound::PickUpItem] = "assets/sounds/Pick_up_item.wav";

	mSoundPathMap[Sound::BoatAmbient] = "assets/sounds/Boat.wav";
	/* ============================================ */


	/* =========== Set Texture Folder File paths =========== */
	mTextureFolderPathMap[TextureFolder::ShipLevel1];
	mTextureFolderPathMap[TextureFolder::ShipLevel2];
	mTextureFolderPathMap[TextureFolder::BeachLevel];
	mTextureFolderPathMap[TextureFolder::RoadLevel];
	/* ===================================================== */


	/* =========== Set Sound Folder File paths =========== */
	mSoundFolderPathMap[SoundFolder::Default];
	mSoundFolderPathMap[SoundFolder::Hardwood];
	mSoundFolderPathMap[SoundFolder::Grass];
	/* =================================================== */
}

/* ====== Load functions ======== */
void ResourceManager::loadResource(Textures::ID id)
{
	std::cout << "Loading Texture: " << mTexturePathMap[id] << std::endl;
	if (mTextureCountMap[id] == 0)
	{
		TexturePtr texture(new sf::Texture());
		texture->loadFromFile(mTexturePathMap[id]);
		texture->setSmooth(true);
		mTextureMap.insert(std::make_pair(id, std::move(texture)));
	}
	mTextureCountMap[id]++;
}
void ResourceManager::loadResource(Images::ID id)
{
	std::cout << "Loading Image: " << mImagePathMap[id] << std::endl;
	if (mImageCountMap[id] == 0)
	{
		ImagePtr image(new sf::Image());
		image->loadFromFile(mImagePathMap[id]);
		mImageMap.insert(std::make_pair(id, std::move(image)));
	}
	mImageCountMap[id]++;
}
void ResourceManager::loadResource(Fonts::ID id)
{
	std::cout << "Loading Font: " << mFontPathMap[id] << std::endl;
	if (mFontCountMap[id] == 0)
	{
		FontPtr font(new sf::Font());
		font->loadFromFile(mFontPathMap[id]);
		mFontMap.insert(std::make_pair(id, std::move(font)));
	}
	mFontCountMap[id]++;
}
void ResourceManager::loadResource(Sound::ID id)
{
	std::cout << "Loading Sound: " << mSoundPathMap[id] << std::endl;
	if (mSoundCountMap[id] == 0)
	{
		SoundPtr sound(new sf::SoundBuffer());
		sound->loadFromFile(mSoundPathMap[id]);
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