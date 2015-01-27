#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <string>
#include <vector>

typedef std::unique_ptr<sf::Texture> TexturePtr;
typedef std::vector<TexturePtr>* FolderPtr;
typedef std::unique_ptr<sf::Font> FontPtr;

namespace Folder
{
	enum ID
	{
		TestLevel
	};
};
namespace Textures
{
	enum ID
	{ 
		TestBackground,
		TestTileImage,
		Player
	};
}
namespace Fonts
{
	enum ID
	{
	};
}
class ResourceManager
{
public:
	//uses Singleton to make the class global.
	static ResourceManager &GetInstance();

	~ResourceManager();
	void load(Folder::ID id, const std::string &directory);
	void load(Textures::ID id, const std::string &filename);
	void load(Fonts::ID id, const std::string &filename);
	void unload(Folder::ID id);
	void unload(Textures::ID id);
	void unload(Fonts::ID id);
	void setIndex(Textures::ID id);

	int& getIndex(Textures::ID id);
	FolderPtr &getFolder(Folder::ID id);
	sf::Texture& getTexture(Textures::ID id) const;
	sf::Font& getFont(Fonts::ID id) const;

private:
	ResourceManager();
	ResourceManager(const ResourceManager&);
	void operator=(const ResourceManager&);

	std::map<Textures::ID,
		int> mIndexMap;

	std::map<Textures::ID, TexturePtr> mTextureMap;
	std::map<Folder::ID, FolderPtr> mFolderMap;
	std::map<Fonts::ID, FontPtr> mFontMap;
};

