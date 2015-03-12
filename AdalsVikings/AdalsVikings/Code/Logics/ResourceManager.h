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

namespace Texture
{
	enum ID
	{ 
		UlfrWalk,
		UlfrWalkUp,
		UlfrIdle,
		UlfrStop,
		UlfrTalkToNpc,
		UlfrTalkToPlayer,
		UlfrPickup,

		Button1,
		Button1Dissabled,
		LookButton,
		TakeButton,
		TalkButton,
		HelpButton,
		OKButton,
		InventoryButton,
		IntroScreen,

		LoadingScreenBackground,
		LoadingScreenBackgroundX,
		LoadingThingyAnimation,

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

		FrontBoatWaveAnimation,
		BackBoatRopeAnimation,
		BackBoatWaveAnimation,
		WaveAnimationBoat,
		WaveAnimation,
		AxeAnimation,
		FireForestCampAnimation,
		DruidsForest1,
		DruidsForest2,
		DruidLeaderIdle,
		DruidLeaderTalk,
		SittingDruidLeader,

		InventoryBackground,
		InventoryTile,

		CursorDefault,
		CursorArrow,

		BrandrIdle,
		BrandrTalk,
		BrandrAngryTalk,
		BrandrAngryIdle,
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
		MailmanIdle,
		MailManTalk,
		MailManSadIdle,
		MailManSadTalk,
		PrincessIdle,
		PrincessIdle2,
		PrincessTalk,
		BeorIdle,
		BeorTalk,
		BearWalk,
		BearIdle,
		SIZE
	};
}
namespace Image
{
	enum ID
	{
		Icon,
		SIZE
	};
}
namespace Font
{
	enum ID
	{
		Font1,
		Font2,
		Skranji_regular,
		Skranji_outline,
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
		SIZE
	};
}
namespace HDDSound
{
	enum ID
	{
		Boat_Music,
		Beach_Road_Tavern_Outside_Music,
		Camp_Finished_Music,
		Church_Music,
		Forest_Music,
		Hils_Gate_Music,
		Tavern_Inside_Music,

		Boat_Ambient,
		Beach_Ambient,
		Road_Ambient,
		Tavern_Outside_Ambient,
		Church_Inside_Ambient,
		Church_Outside_Ambient,
		Forest_Road_Ambient,
		Forest_Camp_Ambient,

		Beach_Wave,
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
		Beach_Hills,
		Road,
		Farm_1,
		Farm_2,
		City_Gates,
		Forest_Road,
		Forest_Camp,
		Church_Outside,
		Church_Inside,
		Tavern_Outside,
		Tavern_Inside,
		Camp_Clearing,
		Camp_Finished,

		Cavern_Left,
		Cavern_Right,
		Cliffs_Down,
		Cliffs_Up,
		Hills,
		Ruins,
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
		Church,
		Concrete,
		Dirt,
		SIZE
	};
};
class ResourceManager
{
public:
	// Uses Singleton to make the class global.
	static ResourceManager &getInstance();

	void loadResource(Texture::ID id);
	void loadResource(Image::ID id);
	void loadResource(Font::ID id);
	void loadResource(Sound::ID id);
	void loadResource(LevelFolder::ID id);
	void loadResource(Footsteps::ID id);
	void loadTexture(const std::string &filename);
	void loadImage(const std::string &filename);

	void unloadResource(Texture::ID id);
	void unloadResource(Image::ID id);
	void unloadResource(Font::ID id);
	void unloadResource(Sound::ID id);
	void unloadResource(LevelFolder::ID id);
	void unloadResource(Footsteps::ID id);
	void unloadTexture(const std::string &filename);
	void unloadImage(const std::string &filename);

	void reloadResource(Texture::ID id);
	void reloadResource(Image::ID id);
	void reloadResource(Font::ID id);
	void reloadResource(Sound::ID id);
	void reloadResource(LevelFolder::ID id);
	void reloadResource(Footsteps::ID id);

	sf::Texture &getResource(Texture::ID id) const;
	sf::Image &getResource(Image::ID id) const;
	sf::Font &getResource(Font::ID id) const;
	sf::SoundBuffer &getResource(Sound::ID id) const;
	const BackgroundsPtr &getResource(LevelFolder::ID id) const;
	const FootstepsPtr &getResource(Footsteps::ID id) const;

	sf::Texture &getNonIDTexture(const std::string &filename) const;
	sf::Image &getNonIDImage(const std::string &filename) const;

	std::string getFilePath(Texture::ID id);
	std::string getFilePath(Image::ID id);
	std::string getFilePath(Font::ID id);
	std::string getFilePath(Sound::ID id);
	std::string getFilePath(HDDSound::ID id);
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
	std::map<Texture::ID, TexturePtr> mTextureMap;
	std::map<Image::ID, ImagePtr> mImageMap;
	std::map<Font::ID, FontPtr> mFontMap;
	std::map<Sound::ID, SoundPtr> mSoundMap;
	std::map<LevelFolder::ID, BackgroundsPtr> mBackgroundsMap;
	std::map<Footsteps::ID, FootstepsPtr> mFootstepsMap;

	// Load Count Maps
	std::map<Texture::ID, int> mTextureCountMap;
	std::map<Image::ID, int> mImageCountMap;
	std::map<Font::ID, int> mFontCountMap;
	std::map<Sound::ID, int> mSoundCountMap;
	std::map<LevelFolder::ID, int> mBackgroundsCountMap;
	std::map<Footsteps::ID, int> mFootstepsCountMap;

	std::map<std::string, int> mNonIDTextureCount;
	std::map<std::string, int> mNonIDImagesCount;

	// FilePath Maps
	std::map<Texture::ID, std::string> mTexturePathMap;
	std::map<Image::ID, std::string> mImagePathMap;
	std::map<Font::ID, std::string> mFontPathMap;
	std::map<Sound::ID, std::string> mSoundPathMap;
	std::map<HDDSound::ID, std::string> mHDDSoundPathMap;
	std::map<LevelFolder::ID, std::string> mBackgroundsPathMap;
	std::map<Footsteps::ID, std::string> mFootstepsPathMap;

	// Dynamic texture loading
	std::map<std::string, TexturePtr> mNonIDTextures;
	std::map<std::string, ImagePtr> mNonIDImages;
};
