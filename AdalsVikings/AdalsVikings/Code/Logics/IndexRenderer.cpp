#include "IndexRenderer.h"
#include "WindowState.h"
#include <iostream>

bool myCompFunction(IndexObject &a, IndexObject &b)
{ 
	return (a.mIndex < b.mIndex);
}

IndexRenderer::IndexRenderer()
{

}
void IndexRenderer::addSprite(sf::Sprite &sprite, int index)
{
	mIndexObjects.push_back(IndexObject(sprite, index));
}
void IndexRenderer::addShape(sf::Shape &shape, int index)
{
	mIndexObjects.push_back(IndexObject(shape, index));
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
	CurrentWindow.setView(getLetterboxView(CurrentWindow.getView()));
	std::sort(mIndexObjects.begin(), mIndexObjects.end(), myCompFunction);
	for each (IndexObject iObj in mIndexObjects)
	{
		if (iObj.mObjType == IndObjType::Sprite)
			CurrentWindow.draw(*iObj.mSprite);
		else if (iObj.mObjType == IndObjType::Shape)
			CurrentWindow.draw(*iObj.mShape);
		else if (iObj.mObjType == IndObjType::Text)
			CurrentWindow.draw(*iObj.mText);
	}
}

sf::View IndexRenderer::getLetterboxView(sf::View view)
{
	float windowRatio = CurrentWindow.getSize().x / (float)CurrentWindow.getSize().y;
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