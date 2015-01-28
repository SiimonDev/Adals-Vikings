#pragma once
#include "ISprite.h"

class IndexRenderer
{
public:
	IndexRenderer();
	IndexRenderer(sf::RenderWindow &window);

	sf::RenderWindow &getRenderWindow();

	void setWindow(sf::RenderWindow &window);
	void addISprite(mv::ISprite &iSprite);
	void addText(sf::Text &text);
	void clear();
	void display();

private:
	sf::RenderWindow* mWindow;
	std::vector<mv::ISprite*> mISprites;
	std::vector<sf::Text*> mTexts;
};

