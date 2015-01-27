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

void IndexRenderer::addTexture(mv::ISprite &texture)
{
	mISprites.push_back(&texture);
}
void IndexRenderer::clearTexture()
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
	mISprites.clear();
}