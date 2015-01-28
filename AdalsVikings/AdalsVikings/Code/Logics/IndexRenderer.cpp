#include "IndexRenderer.h"

sf::RenderWindow &IndexRenderer::getRenderWindow(){ return *mWindow; }

bool myCompFunction(mv::ISprite* a, mv::ISprite* b)
{ 
	return (a->getIndex() < b->getIndex()); 
}

IndexRenderer::IndexRenderer(){

}

IndexRenderer::IndexRenderer(sf::RenderWindow &window){
	mWindow = &window;
}

void IndexRenderer::setWindow(sf::RenderWindow &window)
{
	mWindow = &window;
}

void IndexRenderer::addISprite(mv::ISprite &texture)
{
	mISprites.push_back(&texture);
}

void IndexRenderer::addText(sf::Text &text)
{
	mTexts.push_back(&text);
}

void IndexRenderer::clear()
{
	mISprites.clear();
}

void IndexRenderer::display()
{
	std::sort(mISprites.begin(), mISprites.end(), myCompFunction);
	for each (mv::ISprite* iSprite in mISprites)
	{
		mWindow->draw(iSprite->getSprite());
	}
	for each (sf::Text* text in mTexts)
	{
		mWindow->draw(*text);
	}
}