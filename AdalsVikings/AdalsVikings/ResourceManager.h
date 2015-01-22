#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <string>

namespace Textures
{
	enum ID
	{
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
	ResourceManager();
	~ResourceManager();

	void Load(Textures::ID id, const std::string &filename);
	void Load(Fonts::ID id, const std::string &filename);
	void Unload(Textures::ID id);
	void Unload(Fonts::ID id);
	sf::Texture& GetTexture(Textures::ID id) const;
	sf::Font& GetFont(Fonts::ID id) const;

private:
	std::map<Textures::ID,
		std::unique_ptr<sf::Texture >> mTextureMap;
	std::map<Fonts::ID,
		std::unique_ptr<sf::Font >> mFontMap;
};

