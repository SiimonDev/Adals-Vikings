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
	/* =========== Set all the Loads Counts to Zero =========== */
	for (int i = 0; i < Texture::SIZE; i++)
		mTextureCountMap[static_cast<Texture::ID>(i)] = 0;
	for (int i = 0; i < Image::SIZE; i++)
		mImageCountMap[static_cast<Image::ID>(i)] = 0;
	for (int i = 0; i < Font::SIZE; i++)
		mFontCountMap[static_cast<Font::ID>(i)] = 0;
	for (int i = 0; i < Sound::SIZE; i++)
		mSoundCountMap[static_cast<Sound::ID>(i)] = 0;
	for (int i = 0; i < LevelFolder::SIZE; i++)
		mBackgroundsCountMap[static_cast<LevelFolder::ID>(i)] = 0;
	for (int i = 0; i < Footsteps::SIZE; i++)
		mFootstepsCountMap[static_cast<Footsteps::ID>(i)] = 0;
	/* ======================================================== */


	/* ========== Set Texture File paths ========== */
	mTexturePathMap[Texture::UlfrWalk] = "assets/images/ulfr/character_ulfr_walk.png";
	mTexturePathMap[Texture::UlfrWalkUp] = "assets/images/ulfr/character_ulfr_walk_Up.png";
	mTexturePathMap[Texture::UlfrIdle] = "assets/images/ulfr/character_ulfr_idle.png";
	mTexturePathMap[Texture::UlfrStop] = "assets/images/ulfr/character_ulfr_stop.png";
	mTexturePathMap[Texture::UlfrTalkToNpc] = "assets/images/ulfr/character_ulfr_talk.png";
	mTexturePathMap[Texture::UlfrTalkToPlayer] = "assets/images/ulfr/character_ulfr_front.png";
	mTexturePathMap[Texture::UlfrPickup] = "assets/images/ulfr/character_ulfr_pickup.png";

	mTexturePathMap[Texture::Button1] = "assets/images/interface/Buttons/Button1.png";
	mTexturePathMap[Texture::Button1Dissabled] = "assets/images/interface/Buttons/Button1_grey.png";
	mTexturePathMap[Texture::LookButton] = "assets/images/interface/buttons/interface_look.png";
	mTexturePathMap[Texture::TakeButton] = "assets/images/interface/buttons/interface_take.png";
	mTexturePathMap[Texture::TalkButton] = "assets/images/interface/buttons/interface_talk.png";

	mTexturePathMap[Texture::MainMenuPlayButton] = "assets/images/interface/MainMenu/button_play.png";
	mTexturePathMap[Texture::MainMenuOptionsButton] = "assets/images/interface/MainMenu/button_options_disabled.png";
	mTexturePathMap[Texture::MainMenuQuitButton] = "assets/images/interface/MainMenu/button_quit.png";
	mTexturePathMap[Texture::MainMenuBackground] = "assets/images/Interface/MainMenu/menu_background.png";

	mTexturePathMap[Texture::PauseMenuResumeButton] = "assets/images/interface/pauseManu/button_resume.png";
	mTexturePathMap[Texture::PauseMenuSaveButton] = "assets/images/interface/pauseManu/button_save.png";
	mTexturePathMap[Texture::PauseMenuOptionsButton] = "assets/images/interface/pauseManu/button_options.png";
	mTexturePathMap[Texture::PauseMenuMainMenuButton] = "assets/images/interface/pauseManu/button_main_menu.png";
	mTexturePathMap[Texture::PauseMenuExitButton] = "assets/images/interface/pauseManu/button_exit.png";
	mTexturePathMap[Texture::PauseMenuBackground] = "assets/images/interface/pauseManu/InGame_menu.png";
	mTexturePathMap[Texture::IntroScreen] = "assets/images/interface/tutorial2.png";
	mTexturePathMap[Texture::TextBackgroundPaper] = "assets/images/textbackgorund.jpg";

	mTexturePathMap[Texture::WaveAnimation] = "assets/MapFiles/Beach/waves.png";
	mTexturePathMap[Texture::AxeAnimation] = "assets/images/Interface/MainMenu/flying_axe.png";
	mTexturePathMap[Texture::FireForestCampAnimation] = "assets/Mapfiles/Forest_Camp/background_forestcamp_fire.png";
	mTexturePathMap[Texture::DruidsForest1] = "assets/Mapfiles/Forest_Camp/background_forestcamp_druids_1.png";
	mTexturePathMap[Texture::DruidsForest2] = "assets/Mapfiles/Forest_Camp/background_forestcamp_druids_2.png";
	mTexturePathMap[Texture::DruidLeaderIdle] = "assets/Images/Druid/druid_lord_swag.png";
	mTexturePathMap[Texture::DruidLeaderTalk] = "assets/Images/Druid/druid_lord_swag_talk.png";
	mTexturePathMap[Texture::SittingDruidLeader] = "assets/Images/Druid/druid_lord_swag_2.png";

	mTexturePathMap[Texture::InventoryBackground] = "assets/images/Interface/inventory.png";
	mTexturePathMap[Texture::InventoryTile] = "assets/images/InventoryTile.png";

	mTexturePathMap[Texture::BrandrIdle] = "assets/images/Brandr/character_brandr_blink.png";
	mTexturePathMap[Texture::BrandrTalk] = "assets/images/Brandr/character_brandr_talk.png";
	mTexturePathMap[Texture::BrandrAngryTalk] = "assets/images/Brandr/character_brandr_angry_talk.png";
	mTexturePathMap[Texture::ValdisIdle] = "assets/images/Valdis/character_valdis_blink.png";
	mTexturePathMap[Texture::ValdisTalk] = "assets/images/Valdis/character_valdis_talk.png";
	mTexturePathMap[Texture::ValdisSittingIdle] = "assets/images/Valdis/character_valdis_sitting_blink.png";
	mTexturePathMap[Texture::ValdisSittingTalk] = "assets/images/Valdis/character_valdis_sitting_talk.png";
	mTexturePathMap[Texture::LeifrSitIdle] = "assets/images/Leifr/character_leifr_sit_blink.png";
	mTexturePathMap[Texture::LeifrSitTalk] = "assets/images/Leifr/character_leifr_sit_talk.png";
	mTexturePathMap[Texture::LeifrIdle] = "assets/images/Leifr/character_leifr_blink.png";
	mTexturePathMap[Texture::LeifrTalk] = "assets/images/Leifr/character_leifr_talk.png";
	mTexturePathMap[Texture::FinnrIdle] = "assets/images/finnr/character_finnr_blink.png";
	mTexturePathMap[Texture::FinnrTalk] = "assets/images/finnr/character_finnr_talk.png";
	mTexturePathMap[Texture::BrynjaIdle] = "assets/images/Brynja/character_brynja_blink.png";
	mTexturePathMap[Texture::BrynjaTalk] = "assets/images/Brynja/character_brynja_talk.png";
	mTexturePathMap[Texture::BrynjaSleeping] = "assets/images/Brynja/character_brynja_sleeping.png";
	mTexturePathMap[Texture::AlfrIdle] = "assets/images/Alfr/character_alfr.png";
	mTexturePathMap[Texture::AlfrTalk] = "assets/images/Alfr/character_alfr_talk.png";
	mTexturePathMap[Texture::DagnyIdle] = "assets/images/Dagny/character_dagny_blink.png";
	mTexturePathMap[Texture::DagnyTalk] = "assets/images/Dagny/character_dagny_talk.png";
	mTexturePathMap[Texture::YngvarrIdle] = "assets/images/Yngvarr/character_yngvarr_blink.png";
	mTexturePathMap[Texture::YngvarrTalk] = "assets/images/Yngvarr/character_yngvarr_talk.png";
	mTexturePathMap[Texture::YngvarrSadIdle] = "assets/images/Yngvarr/character_yngvarr_uneasy_blink.png";
	mTexturePathMap[Texture::YngvarrSadTalk] = "assets/images/Yngvarr/character_yngvarr_uneasy_talk.png";
	mTexturePathMap[Texture::SeagullIdle] = "assets/images/Seagull/character_fismås_idle.png";
	mTexturePathMap[Texture::SeagullTalk] = "assets/images/Seagull/character_fismås_talk.png";
	mTexturePathMap[Texture::MailmanIdle] = "assets/images/Mailman/character_mailman_leaves_blink.png";
	mTexturePathMap[Texture::MailManTalk] = "assets/images/Mailman/character_mailman_leaves_talk.png";
	mTexturePathMap[Texture::MailManSadIdle] = "assets/images/Mailman/character_sad_mailman_leaves_blink.png";
	mTexturePathMap[Texture::MailManSadTalk] = "assets/images/Mailman/character_sad_mailman_leaves_talk.png";
	mTexturePathMap[Texture::PrincessIdle] = "assets/images/Princess/character_princess_blink.png";
	mTexturePathMap[Texture::PrincessIdle2] = "assets/images/Princess/character_princess_poke.png";
	mTexturePathMap[Texture::PrincessTalk] = "assets/images/Princess/character_princess_talk.png";
	mTexturePathMap[Texture::BeorIdle] = "assets/images/Beor/character_priest_blink.png";
	mTexturePathMap[Texture::BeorTalk] = "assets/images/Beor/character_priest_happy_talk.png";
	/* ============================================ */


	/* =========== Set Image File paths =========== */
	mImagePathMap[Image::Icon] = "assets/images/interface/icon.ico";
	/* =========================================== */

	/* =========== Set Font File paths =========== */
	mFontPathMap[Font::Font1] = "assets/fonts/font1.ttf";
	mFontPathMap[Font::Font2] = "assets/fonts/font2.ttf";
	mFontPathMap[Font::Skranji_regular] = "assets/fonts/skranji_regular.ttf";
	mFontPathMap[Font::Skranji_outline] = "assets/fonts/skranji_outline.ttf";
	/* =========================================== */


	/* =========== Set Sound File paths =========== */
	mSoundPathMap[Sound::InventoryOpen] = "assets/sounds/Inventory (open).ogg";
	mSoundPathMap[Sound::InventoryClose] = "assets/sounds/Inventory (close).ogg";
	mSoundPathMap[Sound::PickUpItem] = "assets/sounds/Pick_up_item.wav";
	/* ============================================ */


	/* =========== Set HDDSound File paths =========== */
	mHDDSoundPathMap[HDDSound::BoatAmbient] = "assets/sounds/boat/Boat.ogg";
	mHDDSoundPathMap[HDDSound::BoatMusic] = "assets/sounds/music/Boat_music.ogg";

	mHDDSoundPathMap[HDDSound::BeachAmbient] = "assets/sounds/beach/Beach.ogg";
	mHDDSoundPathMap[HDDSound::BeachMusic] = "assets/sounds/music/exp theme.ogg";
	mHDDSoundPathMap[HDDSound::BeachWave] = "assets/sounds/beach/wave.ogg";
	/* =============================================== */


	/* =========== Set Background Folder paths =========== */
	mBackgroundsPathMap[LevelFolder::Ship_1] = "assets/MapFiles/Ship1/";
	mBackgroundsPathMap[LevelFolder::Ship_2] = "assets/MapFiles/Ship2/";
	mBackgroundsPathMap[LevelFolder::Beach] = "assets/MapFiles/Beach/";
	mBackgroundsPathMap[LevelFolder::Road] = "assets/MapFiles/Road/";
	mBackgroundsPathMap[LevelFolder::Forest_Road] = "assets/MapFiles/Forest_Road/";
	mBackgroundsPathMap[LevelFolder::Forest_Camp] = "assets/MapFiles/Forest_Camp/";
	mBackgroundsPathMap[LevelFolder::Church_Outside] = "assets/MapFiles/Church_Outside/";
	mBackgroundsPathMap[LevelFolder::Church_Inside] = "assets/MapFiles/Church_Inside/";
	mBackgroundsPathMap[LevelFolder::Tavern_Outside] = "assets/MapFiles/Tavern_Outside/";
	mBackgroundsPathMap[LevelFolder::Tavern_Inside] = "assets/MapFiles/Tavern_Inside/";
	mBackgroundsPathMap[LevelFolder::Camp_Clearing] = "assets/MapFiles/Camp_Clearing/";
	mBackgroundsPathMap[LevelFolder::Camp_Finished] = "assets/MapFiles/Camp_Finished/";
	/* =================================================== */


	/* =========== Set Footstep Folder paths =========== */
	mFootstepsPathMap[Footsteps::Default] = "assets/sounds/footsteps/test/";
	mFootstepsPathMap[Footsteps::Hardwood] = "assets/sounds/footsteps/Hardwood/";
	mFootstepsPathMap[Footsteps::Grass] = "assets/sounds/footsteps/Grass/";
	/* ================================================= */
}


/* ====== Load functions ======== */
void ResourceManager::loadResource(Texture::ID id)
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
void ResourceManager::loadResource(Image::ID id)
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
void ResourceManager::loadResource(Font::ID id)
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
void ResourceManager::loadResource(LevelFolder::ID id)
{
	if (mBackgroundsCountMap[id] == 0)
	{
		BackgroundsPtr mFolderVector;
		std::vector<std::string> filePaths = getAllBackgroundFilesFromFolder(mBackgroundsPathMap[id]);

		for (int i = 0; i < filePaths.size(); i++)
		{
			mFolderVector.push_back(TexturePtr(new sf::Texture()));
			mFolderVector[i]->loadFromFile(filePaths.at(i));
		}
		mBackgroundsMap.insert(std::make_pair(id, std::move(mFolderVector)));

		mFolderVector.clear();
		filePaths.clear();
	}
	mBackgroundsCountMap[id]++;
}
void ResourceManager::loadResource(Footsteps::ID id)
{
	if (mFootstepsCountMap[id] == 0)
	{
		FootstepsPtr mSoundVector;
		std::vector<std::string> filePaths = getAllFootstepsFromFolder(mFootstepsPathMap[id]);

		for (int i = 0; i < filePaths.size(); i++)
		{
			mSoundVector.push_back(SoundPtr(new sf::SoundBuffer()));
			mSoundVector[i]->loadFromFile(filePaths.at(i));
		}
		mFootstepsMap.insert(std::make_pair(id, std::move(mSoundVector)));

		mSoundVector.clear();
		filePaths.clear();
	}
	mFootstepsCountMap[id]++;
}
void ResourceManager::loadTexture(const std::string &filename)
{
	std::cout << "Loading Dynamic Texture: " << filename << std::endl;
	if (mNonIDTextureCount[filename] == 0)
	{
		TexturePtr texture(new sf::Texture());
		texture->loadFromFile(filename);
		texture->setSmooth(true);
		mNonIDTextures.insert(std::make_pair(filename, std::move(texture)));
	}
	mNonIDTextureCount[filename]++;
}
void ResourceManager::loadImage(const std::string &filename)
{
	std::cout << "Loading Dynamic Image: " << filename << std::endl;
	if (mNonIDImagesCount[filename] == 0)
	{
		ImagePtr image(new sf::Image());
		image->loadFromFile(filename);
		mNonIDImages.insert(std::make_pair(filename, std::move(image)));
	}
	mNonIDImagesCount[filename]++;
}


/* ====== Unload functions ======== */
void ResourceManager::unloadResource(Texture::ID id)
{
	if (mTextureCountMap[id] == 1)
		mTextureMap.erase(id);

	if (mTextureCountMap[id] > 0)
		mTextureCountMap[id]--;
}
void ResourceManager::unloadResource(Image::ID id)
{
	if (mImageCountMap[id] == 1)
		mImageMap.erase(id);

	if (mImageCountMap[id] > 0)
		mImageCountMap[id]--;
}
void ResourceManager::unloadResource(Font::ID id)
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
void ResourceManager::unloadResource(LevelFolder::ID id)
{
	if (mBackgroundsCountMap[id] == 1)
	{
		mBackgroundsMap[id].clear();
		mBackgroundsMap.erase(id);
	}

	if (mBackgroundsCountMap[id] > 0)
		mBackgroundsCountMap[id]--;
}
void ResourceManager::unloadResource(Footsteps::ID id)
{
	if (mFootstepsCountMap[id] == 1)
	{
		mFootstepsMap[id].clear();
		mFootstepsMap.erase(id);
	}

	if (mFootstepsCountMap[id] > 0)
		mFootstepsCountMap[id]--;
}
void ResourceManager::unloadTexture(const std::string &filename)
{
	if (mNonIDTextureCount[filename] == 1)
		mNonIDTextures.erase(filename);

	if (mNonIDTextureCount[filename] > 0)
		mNonIDTextureCount[filename]--;
}
void ResourceManager::unloadImage(const std::string &filename)
{
	if (mNonIDImagesCount[filename] == 1)
		mNonIDImages.erase(filename);

	if (mNonIDImagesCount[filename] > 0)
		mNonIDImagesCount[filename]--;
}


/* ====== Truncate functions ======== */
void ResourceManager::truncateTextures()
{
	for (int i = 0; i < Texture::SIZE; i++)
		mTextureCountMap[static_cast<Texture::ID>(i)] = 0;

	mTextureMap.clear();
}
void ResourceManager::truncateImages()
{
	for (int i = 0; i < Image::SIZE; i++)
		mImageCountMap[static_cast<Image::ID>(i)] = 0;

	mImageMap.clear();
}
void ResourceManager::truncateFonts()
{
	for (int i = 0; i < Font::SIZE; i++)
		mFontCountMap[static_cast<Font::ID>(i)] = 0;
	mFontMap.clear();
}
void ResourceManager::truncateSounds()
{
	for (int i = 0; i < Sound::SIZE; i++)
		mSoundCountMap[static_cast<Sound::ID>(i)] = 0;
	mSoundMap.clear();
}
void ResourceManager::truncateBackgrounds()
{
	for (int i = 0; i < LevelFolder::SIZE; i++)
		mBackgroundsCountMap[static_cast<LevelFolder::ID>(i)] = 0;

	for (std::map<LevelFolder::ID, BackgroundsPtr>::iterator it = mBackgroundsMap.begin(); it != mBackgroundsMap.end(); ++it)
		it->second.clear();

	mBackgroundsMap.clear();
}
void ResourceManager::truncateFootsteps()
{
	for (int i = 0; i < Footsteps::SIZE; i++)
		mFootstepsCountMap[static_cast<Footsteps::ID>(i)] = 0;

	for (std::map<Footsteps::ID, FootstepsPtr>::iterator it = mFootstepsMap.begin(); it != mFootstepsMap.end(); ++it)
		it->second.clear();

	mFootstepsMap.clear();
}


/* ====== Get functions ======== */
const BackgroundsPtr &ResourceManager::getResource(LevelFolder::ID id) const
{
	auto found = mBackgroundsMap.find(id);
	return found->second;
}
const FootstepsPtr &ResourceManager::getResource(Footsteps::ID id) const
{
	auto found = mFootstepsMap.find(id);
	return found->second;
}
sf::Image &ResourceManager::getResource(Image::ID id) const
{
	auto found = mImageMap.find(id);
	return *found->second;
}
sf::Texture &ResourceManager::getResource(Texture::ID id) const
{
	auto found = mTextureMap.find(id);
	return *found->second;
}
sf::Font &ResourceManager::getResource(Font::ID id) const
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


/* ====== Get FilePath Functions ======== */
std::string ResourceManager::getFilePath(Texture::ID id)
{
	return mTexturePathMap[id];
}
std::string ResourceManager::getFilePath(Image::ID id)
{
	return mImagePathMap[id];
}
std::string ResourceManager::getFilePath(Font::ID id)
{
	return mFontPathMap[id];
}
std::string ResourceManager::getFilePath(Sound::ID id)
{
	return mSoundPathMap[id];
}
std::string ResourceManager::getFilePath(HDDSound::ID id)
{
	return mHDDSoundPathMap[id];
}
std::string ResourceManager::getFilePath(LevelFolder::ID id)
{
	return mBackgroundsPathMap[id];
}
std::string ResourceManager::getFilePath(Footsteps::ID id)
{
	return mFootstepsPathMap[id];
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
			std::cout << s << std::endl;
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