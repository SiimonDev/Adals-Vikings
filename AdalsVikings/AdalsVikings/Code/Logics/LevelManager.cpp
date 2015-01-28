#include "LevelManager.h"
#include "..\Levels\Level.h"
#include "..\Levels\TestLevel.h"

LevelManager::LevelManager()
{
	mCurrentLevel = new TestLevel();
}
LevelManager::~LevelManager()
{
	delete mCurrentLevel;
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
void LevelManager::changeLevel()
{
	/*mNextLevel = mCurrentLevel->getPortal().getNextLevel();
	mCurrentLevel->unload();
	delete mCurrentLevel;
	mCurrentLevel = mNextLevel;
	mCurrentLevel->load();
	delete mNextLevel;*/

}