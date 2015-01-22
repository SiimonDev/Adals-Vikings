#include "ResourceManager.h"


void ResourceManager::Load(Textures::ID _id, const std::string& _filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	texture->loadFromFile(_filename);
	mTextureMap.insert(std::make_pair(_id, std::move(texture)));
}
void ResourceManager::Load(Fonts::ID _id, const std::string& _filename)
{
	std::unique_ptr<sf::Font> font(new sf::Font());
	font->loadFromFile(_filename);
	mFontMap.insert(std::make_pair(_id, std::move(font)));
}
void ResourceManager::Unload(Textures::ID _id)
{
	mTextureMap.erase(_id);
}
void ResourceManager::Unload(Fonts::ID _id)
{
	mFontMap.erase(_id);
}
sf::Texture& ResourceManager::GetTexture(Textures::ID _id) const
{
	auto found = mTextureMap.find(_id);
	return *found->second;
}
sf::Font& ResourceManager::GetFont(Fonts::ID _id) const
{
	auto found = mFontMap.find(_id);
	return *found->second;
}
