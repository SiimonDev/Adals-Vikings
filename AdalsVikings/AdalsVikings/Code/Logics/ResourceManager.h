#pragma once
#include "..\Dialog\pugixml.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include <map>

using namespace pugi;
typedef std::unique_ptr<sf::Texture> TexturePtr;
typedef std::unique_ptr<sf::Font> FontPtr;
typedef std::unique_ptr<sf::Image> ImagePtr;
typedef std::unique_ptr<sf::SoundBuffer> SoundPtr;
typedef std::vector<TexturePtr> BackgroundsPtr;
typedef std::vector<SoundPtr> FootstepsPtr;

#define RMI ResourceManager::getInstance()

namespace Textures
{
	enum ID
	{ 
		UlfrWalk,
		UlfrWalkUp,
		UlfrIdle,
		UlfrFront,
		UlfrBack,
		UlfrStop,
		UlfrTalkToNpc,
		UlfrTalkToPlayer,
		UlfrPickup,

		Button1,
		Button1Dissabled,
		LookButton,
		TakeButton,
		TalkButton,

		MainMenuPlayButton,
		MainMenuOptionsButton,
		MainMenuQuitButton,
		MainMenuBackground,

		PauseMenuResumeButton,
		PauseMenuSaveButton,
		PauseMenuOptionsButton,
		PauseMenuMainMenuButton,
		PauseMenuExitButton,
		PauseMenuBackground,

		WaveAnimation,
		AxeAnimation,

		InventoryBackground,
		InventoryTile,

		BrandrIdle,
		BrandrTalk,
		BrandrAngryTalk,
		ValdisIdle,
		ValdisTalk,
		ValdisSittingIdle,
		ValdisSittingTalk,
		LeifrSitIdle,
		LeifrSitTalk,
		LeifrIdle,
		LeifrTalk,
		FinnrIdle,
		FinnrTalk,
		BrynjaIdle,
		BrynjaTalk,
		BrynjaSleeping,
		AlfrIdle,
		AlfrTalk,
		DagnyIdle,
		DagnyTalk,
		YngvarrIdle,
		YngvarrTalk,
		YngvarrSadIdle,
		YngvarrSadTalk,
		SeagullIdle,
		SeagullTalk,
		SIZE
	};
}
namespace Images
{
	enum ID
	{
		Icon,
		SIZE
	};
}
namespace Fonts
{
	enum ID
	{
		ActionWheelDescription,
		DialogWindow,
		MenuButtons,
		SIZE
	};
}
namespace Sound
{
	enum ID
	{
		InventoryOpen,
		InventoryClose,
		PickUpItem,

		BoatAmbient,
		BeachAmbient,
		SIZE
	};
}
namespace LevelFolder
{
	enum ID
	{
		Ship_1,
		Ship_2,
		Beach,
		Road,
		Forest_Road,
		Forest_Camp,
		Church_Outside,
		Church_Inside,
		Camp,
		SIZE
	};
};
namespace Footsteps
{
	enum ID
	{
		Default,
		Hardwood,
		Grass,
		SIZE
	};
};
class ResourceManager
{
public:
	//uses Singleton to make the class global.
	static ResourceManager &getInstance();

	void loadResource(Textures::ID id);
	void loadResource(Images::ID id);
	void loadResource(Fonts::ID id);
	void loadResource(Sound::ID id);
	void loadResource(LevelFolder::ID id);
	void loadResource(Footsteps::ID id);
	void loadTexture(const std::string &filename);
	void loadImage(const std::string &filename);

	void unloadResource(Textures::ID id);
	void unloadResource(Images::ID id);
	void unloadResource(Fonts::ID id);
	void unloadResource(Sound::ID id);
	void unloadResource(LevelFolder::ID id);
	void unloadResource(Footsteps::ID id);
	void unloadTexture(const std::string &filename);
	void unloadImage(const std::string &filename);

	void truncateTextures();
	void truncateImages();
	void truncateSounds();
	void truncateFonts();
	void truncateBackgrounds();
	void truncateFootsteps();

	sf::Texture &getResource(Textures::ID id) const;
	sf::Image &getResource(Images::ID id) const;
	sf::Font &getResource(Fonts::ID id) const;
	sf::SoundBuffer &getResource(Sound::ID id) const;
	const BackgroundsPtr &getResource(LevelFolder::ID id) const;
	const FootstepsPtr &getResource(Footsteps::ID id) const;

	sf::Texture &getNonIDTexture(const std::string &filename) const;
	sf::Image &getNonIDImage(const std::string &filename) const;

	std::string getFilePath(Textures::ID id);
	std::string getFilePath(Images::ID id);
	std::string getFilePath(Fonts::ID id);
	std::string getFilePath(Sound::ID id);
	std::string getFilePath(LevelFolder::ID id);
	std::string getFilePath(Footsteps::ID id);

	std::vector<std::string> getAllBackgroundFilesFromFolder(const std::string &directory);
	std::vector<std::string> getAllFootstepsFromFolder(const std::string &directory);
	std::string getRCFileFromFolder(const std::string &directory);
	std::string getIndexFileFromFolder(const std::string &directory);

private:
	ResourceManager();
	ResourceManager(const ResourceManager&);
	void operator=(const ResourceManager&);

	// Resource Maps
	std::map<Textures::ID, TexturePtr> mTextureMap;
	std::map<Images::ID, ImagePtr> mImageMap;
	std::map<Fonts::ID, FontPtr> mFontMap;
	std::map<Sound::ID, SoundPtr> mSoundMap;
	std::map<LevelFolder::ID, BackgroundsPtr> mBackgroundsMap;
	std::map<Footsteps::ID, FootstepsPtr> mFootstepsMap;

	// Load Count Maps
	std::map<Textures::ID, int> mTextureCountMap;
	std::map<Images::ID, int> mImageCountMap;
	std::map<Fonts::ID, int> mFontCountMap;
	std::map<Sound::ID, int> mSoundCountMap;
	std::map<LevelFolder::ID, int> mBackgroundsCountMap;
	std::map<Footsteps::ID, int> mFootstepsCountMap;

	std::map<std::string, int> mNonIDTextureCount;
	std::map<std::string, int> mNonIDImagesCount;

	// FilePath Maps
	std::map<Textures::ID, std::string> mTexturePathMap;
	std::map<Images::ID, std::string> mImagePathMap;
	std::map<Fonts::ID, std::string> mFontPathMap;
	std::map<Sound::ID, std::string> mSoundPathMap;
	std::map<LevelFolder::ID, std::string> mBackgroundsPathMap;
	std::map<Footsteps::ID, std::string> mFootstepsPathMap;

	// Dynamic texture loading
	std::map<std::string, TexturePtr> mNonIDTextures;
	std::map<std::string, ImagePtr> mNonIDImages;
};
