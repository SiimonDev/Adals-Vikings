#pragma once
#include <SFML\Graphics.hpp>

enum IndObjType
{
	Sprite,
	Shape,
	Text
};

struct IndexObject
{
	IndexObject(sf::Sprite &sprite, int index)
	{
		mObjType = IndObjType::Sprite;
		mSprite = &sprite;
		mIndex = index;
	}
	IndexObject(sf::Shape &iShape, int index)
	{
		mObjType = IndObjType::Shape;
		mIndex = index;
		mShape = &iShape;
	}
	IndexObject(sf::Text &iText, int index)
	{
		mObjType = IndObjType::Text;
		mIndex = index;
		mText = &iText;
	}

	IndObjType mObjType;
	
	int mIndex;
	sf::Sprite* mSprite;
	sf::Shape* mShape;
	sf::Text* mText;
};

class IndexRenderer
{
public:
	IndexRenderer();

	void setWindow(sf::RenderWindow &window);
	void addSprite(sf::Sprite &sprite, int index);
	void addShape(sf::Shape &shape, int index);
	void addText(sf::Text &text, int index);
	void clear();
	void display();

	sf::View getLetterboxView(sf::View view);
private:
	std::vector<IndexObject> mIndexObjects;
};