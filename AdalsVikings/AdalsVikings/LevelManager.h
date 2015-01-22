#pragma once
#include <SFML\Graphics.hpp>
class Level;
class LevelManager
{
public:
	static LevelManager &getInstance();
	~LevelManager();

	void load();
	void unload();
	void render(sf::RenderWindow &window);
	void update(sf::Time &frametime);

private:

	Level *mCurrentLevel;
	LevelManager();
	LevelManager(const LevelManager&);
	void operator=(const LevelManager&);
};

