#pragma once
#include <SFML\Graphics.hpp>
#include "IndexRenderer.h"

class Level;
class LevelManager
{
public:
	//Uses Singleton in order to achieve having only one level active at a time.
	static LevelManager &getInstance();
	~LevelManager();

	void initialize();
	void load();
	void unload();
	void render(IndexRenderer &iRenderer);
	void update(sf::Time &frametime);

private:

	Level *mCurrentLevel;
	LevelManager();
	LevelManager(const LevelManager&);
	void operator=(const LevelManager&);
};

