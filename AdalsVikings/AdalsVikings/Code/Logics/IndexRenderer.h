#pragma once
#include "ISprite.h"

class IndexRenderer
{
public:
	IndexRenderer();
	IndexRenderer(sf::RenderWindow &window);

	sf::RenderWindow &getRenderWindow();

	void setWindow(sf::RenderWindow &window);
	void addTexture(mv::ISprite &texture);
	void display();

private:
	sf::RenderWindow* mWindow;
	std::vector<mv::ISprite*> mISprites;
};

