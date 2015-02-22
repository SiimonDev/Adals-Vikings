#pragma once
#include "..\Dialog\pugixml.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include <map>

using namespace pugi;
typedef std::unique_ptr<sf::Texture> TexturePtr;
typedef std::vector<TexturePtr> FolderPtr;
typedef std::unique_ptr<sf::Font> FontPtr;
typedef std::unique_ptr<sf::Image> ImagePtr;
typedef std::unique_ptr<sf::SoundBuffer> SoundPtr;

#define RMI ResourceManager::getInstance()


namespace Images
{
	enum ID
	{

	};
}
namespace Folder
{
	enum ID
	{
		ShipLevel1,
		ShipLevel2,
		BeachLevel
	};
};
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

		Portal,
		Button1,
		Button1Dissabled,
		LookButton,
		TakeButton,
		TalkButton,

		MainMenuPlayButton,
		MainMenuOptionsButton,
		MainMenuQuitButton,

		PauseMenuResumeButton,
		PauseMenuSaveButton,
		PauseMenuOptionsButton,
		PauseMenuMainMenuButton,
		PauseMenuExitButton,
		PauseMenuBackground,

		Asteroid,
		Axe,
		Stick,

		Wave,
		AxeAnimation,
		MainMenuBackground,

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
	};
}
namespace Fonts
{
	enum ID
	{
		ActionWheelDescription,
		DialogWindow,
		MenuButtons
	};
}
namespace Sound
{
	enum ID
	{
		InventoryOpen,
		InventoryClose,
		PickUpItem,

		BoatAmbient
	};
}
class ResourceManager
{
public:
	//uses Singleton to make the class global.
	static ResourceManager &getInstance();

	void load(Images::ID id, const std::string &directory);
	void load(Folder::ID id, const std::string &directory);
	void load(Textures::ID id, const std::string &filename);
	void load(Fonts::ID id, const std::string &filename);
	void load(Sound::ID id, const std::string &filename);
	void loadTexture(const std::string &filename);
	void loadImage(const std::string &filename);

	void unload(Images::ID id);
	void unload(Folder::ID id);
	void unload(Textures::ID id);
	void unload(Fonts::ID id);
	void unload(Sound::ID id);
	void unloadTexture(const std::string &filename);
	void unloadImage(const std::string &filename);

	void truncateTextures();
	void truncateNonIDTextures();
	void truncateImages();
	void truncateNonIDImages();
	void truncateFolders();
	void truncateSounds();
	void truncateFonts();

	sf::Image &getImage(Images::ID id);
	FolderPtr &getFolder(Folder::ID id);
	sf::Texture &getTexture(Textures::ID id) const;
	sf::Font &getFont(Fonts::ID id) const;
	sf::SoundBuffer &getSoundBuffer(Sound::ID id) const;
	sf::Texture &getNonIDTexture(const std::string &filename) const;
	sf::Image &getNonIDImage(const std::string &filename) const;

	std::vector<std::string> getAllBackgroundFilesFromFolder(const std::string &directory);
	std::string getRCFileFromFolder(const std::string &directory);
	std::string getIndexFileFromFolder(const std::string &directory);

private:
	ResourceManager();
	ResourceManager(const ResourceManager&);
	void operator=(const ResourceManager&);

	FolderPtr mFolderVector;
	std::map<Textures::ID, TexturePtr> mTextureMap;
	std::map<Folder::ID, FolderPtr> mFolderMap;
	std::map<Fonts::ID, FontPtr> mFontMap;
	std::map<Images::ID, ImagePtr> mImageMap;
	std::map<Sound::ID, SoundPtr> mSoundMap;

	// Dynamic texture loading
	std::map<std::string, TexturePtr> mNonIDTextures;
	std::map<std::string, ImagePtr> mNonIDImages;
};

