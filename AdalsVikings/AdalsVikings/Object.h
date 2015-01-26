#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>

class Object
{
public:
	Object(std::string objectID, std::string filePath);
	~Object();

	void render(sf::RenderWindow &window);
	void update(sf::Time &time);

private:
	std::string filePath;
	std::string mName, mLookAtDialog, mUsDialog, mCantUseDialog;
	sf::Sprite mSprite;
	bool mCanPickUp;

};

