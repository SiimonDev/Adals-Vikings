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
typedef std::vector<TexturePtr> TextureFolderPtr;
typedef std::vector<SoundPtr> SoundFolderPtr;

#define RMI ResourceManager::getInstance()

namespace Textures
{
	enum ID
	{ 
		UlfrWalk,
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
		ValdisIdle,
		ValdisTalk,
		LeifrIdle,
		LeifrTalk,
		FinnrIdle,
		FinnrTalk,
		BrynjaIdle,
		BrynjaTalk,
		AlfrIdle,
		AlfrTalk,
		DagnyIdle,
		DagnyTalk,
		YngvarrIdle,
		YngvarrTalk,
		SIZE
	};
}
namespace Images
{
	enum ID
	{
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
		SIZE
	};
}
namespace TextureFolder
{
	enum ID
	{
		ShipLevel1,
		ShipLevel2,
		BeachLevel,
		RoadLevel,
		SIZE
	};
};
namespace SoundFolder
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
	void loadResource(TextureFolder::ID id, const std::string &directory);
	void loadResource(SoundFolder::ID id, const  std::string &directory);
	void loadTexture(const std::string &filename);
	void loadImage(const std::string &filename);

	void unloadResource(Textures::ID id);
	void unloadResource(Images::ID id);
	void unloadResource(Fonts::ID id);
	void unloadResource(Sound::ID id);
	void unloadResource(TextureFolder::ID id);
	void unloadResource(SoundFolder::ID id);
	void unloadTexture(const std::string &filename);
	void unloadImage(const std::string &filename);

	void truncateTextures();
	void truncateImages();
	void truncateSounds();
	void truncateFonts();
	void truncateTextureFolders();
	void truncateSoundFolders();

	sf::Texture &getResource(Textures::ID id) const;
	sf::Image &getResource(Images::ID id) const;
	sf::Font &getResource(Fonts::ID id) const;
	sf::SoundBuffer &getResource(Sound::ID id) const;
	const TextureFolderPtr &getResource(TextureFolder::ID id) const;
	const SoundFolderPtr &getResource(SoundFolder::ID id) const;

	sf::Texture &getNonIDTexture(const std::string &filename) const;
	sf::Image &getNonIDImage(const std::string &filename) const;

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
	std::map<TextureFolder::ID, TextureFolderPtr> mTextureFolderMap;
	std::map<SoundFolder::ID, SoundFolderPtr> mSoundFolderMap;

	// Load Count Maps
	std::map<Textures::ID, int> mTextureCountMap;
	std::map<Images::ID, int> mImageCountMap;
	std::map<Fonts::ID, int> mFontCountMap;
	std::map<Sound::ID, int> mSoundCountMap;
	std::map<TextureFolder::ID, int> mTextureFolderCountMap;
	std::map<SoundFolder::ID, int> mSoundFolderCountMap;

	// FilePath Maps
	std::map<Textures::ID, std::string> mTexturePathMap;
	std::map<Images::ID, std::string> mImagePathMap;
	std::map<Fonts::ID, std::string> mFontPathMap;
	std::map<Sound::ID, std::string> mSoundPathMap;
	std::map<TextureFolder::ID, std::string> mTextureFolderPathMap;
	std::map<SoundFolder::ID, std::string> mSoundFolderPathMap;

	// Dynamic texture loading
	std::map<std::string, TexturePtr> mNonIDTextures;
	std::map<std::string, ImagePtr> mNonIDImages;
};