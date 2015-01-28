#pragma once
#include <SFML\Graphics.hpp>
#include "IndexRenderer.h"

class Level;
class LevelManager
{
public:
	LevelManager();
	LevelManager(const LevelManager&);
	void operator=(const LevelManager&);

	~LevelManager();

	void load();
	void unload();
	void render(IndexRenderer &iRenderer);
	void update(sf::Time &frametime);
	void changeLevel();

private:

	Level *mCurrentLevel, *mNextLevel;
};

