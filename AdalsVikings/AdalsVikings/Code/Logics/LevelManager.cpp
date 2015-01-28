#include "LevelManager.h"
#include "..\Levels\Level.h"
#include "..\Levels\TestLevel.h"

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
	delete mCurrentLevel;
}
void LevelManager::initialize()
{
	mCurrentLevel = new TestLevel();
}
void LevelManager::load()
{
	mCurrentLevel->load();
}
void LevelManager::unload()
{
	mCurrentLevel->unload();
}
void LevelManager::render(IndexRenderer &iRenderer)
{
	mCurrentLevel->render(iRenderer);
}
void LevelManager::update(sf::Time &frametime)
{
	mCurrentLevel->update(frametime);
}