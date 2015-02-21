#include "IndexRenderer.h"
#include <iostream>

sf::RenderWindow &IndexRenderer::getRenderWindow(){ return *mWindow; }

bool myCompFunction(IndexObject &a, IndexObject &b)
{ 
	return (a.mIndex < b.mIndex);
}

IndexRenderer::IndexRenderer()
: mAlphaValue(255)
{

}

IndexRenderer::IndexRenderer(sf::RenderWindow &window){
	mWindow = &window;
}

void IndexRenderer::setWindow(sf::RenderWindow &window)
{
	mWindow = &window;
}

void IndexRenderer::addSprite(sf::Sprite &sprite, int index)
{
	mIndexObjects.push_back(IndexObject(sprite, index));
}
void IndexRenderer::addRectangle(sf::RectangleShape &rectangle, int index)
{
	mIndexObjects.push_back(IndexObject(rectangle, index));
}
void IndexRenderer::addText(sf::Text &text, int index)
{
	mIndexObjects.push_back(IndexObject(text, index));
}

void IndexRenderer::clear()
{
	mIndexObjects.clear();
}

void IndexRenderer::display()
{
	mWindow->setView(getLetterboxView(mWindow->getView()));
	std::sort(mIndexObjects.begin(), mIndexObjects.end(), myCompFunction);
	for each (IndexObject iObj in mIndexObjects)
	{
		if (iObj.mObjType == IndObjType::Sprite)
		{
			iObj.mSprite->setColor(sf::Color(255, 255, 255, mAlphaValue));
			mWindow->draw(*iObj.mSprite);
		}
		else if (iObj.mObjType == IndObjType::Rectangle)
			mWindow->draw(*iObj.mRectangle);
		else if (iObj.mObjType == IndObjType::Text)
			mWindow->draw(*iObj.mText);
	}
}

void IndexRenderer::resize(int width, int height)
{

}

void IndexRenderer::setAlpha(int alpha)
{
	mAlphaValue = alpha;
}

sf::View IndexRenderer::getLetterboxView(sf::View view)
{
	float windowRatio = mWindow->getSize().x / (float)mWindow->getSize().y;
	float viewRatio = view.getSize().x / (float)view.getSize().y;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	bool horizontalSpacing = true;
	if (windowRatio < viewRatio)
		horizontalSpacing = false;

	if (horizontalSpacing) {
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.0;
	}

	else {
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.0;
	}

	view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));

	return view;
}