#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <string>
#include <vector>

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
	void load(Textures::ID id, const std::string &filename);
	void load(Fonts::ID id, const std::string &filename);
	void unload(Textures::ID id);
	void unload(Fonts::ID id);
	void setIndex(Textures::ID id);

	int& getIndex(Textures::ID id);
	sf::Texture& getTexture(Textures::ID id) const;
	sf::Font& getFont(Fonts::ID id) const;

private:
	ResourceManager();
	ResourceManager(const ResourceManager&);
	void operator=(const ResourceManager&);

	std::map<Textures::ID,
		int> mIndexMap;
	std::map<Textures::ID,
		std::unique_ptr<sf::Texture>> mTextureMap;
	std::map<Fonts::ID,
		std::unique_ptr<sf::Font >> mFontMap;
};

