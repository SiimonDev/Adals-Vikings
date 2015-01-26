#include "ResourceManager.h"

ResourceManager &ResourceManager::GetInstance()
{
	static ResourceManager instance;
	return instance;
}
ResourceManager::ResourceManager()
{

}
ResourceManager::~ResourceManager()
{

}
void ResourceManager::load(Textures::ID _id, const std::string& _filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	texture->loadFromFile(_filename);
	mTextureMap.insert(std::make_pair(_id, std::move(texture)));

	//mIndexMap.insert(std::make_pair(_id, std::move(_index)));
}
void ResourceManager::load(Fonts::ID _id, const std::string& _filename)
{
	std::unique_ptr<sf::Font> font(new sf::Font());
	font->loadFromFile(_filename);
	mFontMap.insert(std::make_pair(_id, std::move(font)));
}
void ResourceManager::unload(Textures::ID _id)
{
	mTextureMap.erase(_id);
}
void ResourceManager::unload(Fonts::ID _id)
{
	mFontMap.erase(_id);
}
sf::Texture& ResourceManager::getTexture(Textures::ID _id) const
{
	auto found = mTextureMap.find(_id);
	return *found->second;
}
sf::Font& ResourceManager::getFont(Fonts::ID _id) const
{
	auto found = mFontMap.find(_id);
	return *found->second;
}
int& ResourceManager::getIndex(Textures::ID _id)
{
	auto found = mIndexMap.find(_id);
	return found->second;
}