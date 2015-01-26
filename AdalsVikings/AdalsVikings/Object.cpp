#include "Object.h"
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"


Object::Object(ObjID objectID, std::string filePath, Textures::ID textureID) : mObjectID(objectID), mFilePath(filePath), mTextureID(textureID)
{
	
}


Object::~Object()
{
}

void Object::render(sf::RenderWindow &window)
{
	window.draw(mSprite);
}

void Object::update(sf::Time &time)
{
		
}

void Object::load()
{
	ResourceManager::GetInstance().load(mTextureID, mFilePath);
	mSprite.setTexture(ResourceManager::GetInstance().getTexture(mTextureID));
}

void Object::unload(){
	ResourceManager::GetInstance().unload(mTextureID);
}