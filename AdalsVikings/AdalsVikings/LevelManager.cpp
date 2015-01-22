#include "LevelManager.h"
#include "Level.h"

LevelManager &LevelManager::getInstance()
{
	static LevelManager instance;
	return instance;
}
LevelManager::LevelManager()
{
}
LevelManager::~LevelManager()
{
}
void LevelManager::load()
{
	mCurrentLevel->load();
}
void LevelManager::unload()
{
	mCurrentLevel->unload();
}
void LevelManager::render(sf::RenderWindow &window)
{
	mCurrentLevel->render(window);
}
void LevelManager::update(sf::Time &frametime)
{
	mCurrentLevel->update(frametime);
}