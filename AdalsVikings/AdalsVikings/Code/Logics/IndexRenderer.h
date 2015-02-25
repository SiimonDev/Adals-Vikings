#pragma once
#include <SFML\Graphics.hpp>

enum IndObjType
{
	Sprite,
	IRectangle,
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
	IndexObject(sf::RectangleShape &iRectangle, int index)
	{
		mObjType = IndObjType::IRectangle;
		mIndex = index;
		mRectangle = &iRectangle;
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
	sf::RectangleShape* mRectangle;
	sf::Text* mText;
};

class IndexRenderer
{
public:
	IndexRenderer();

	void setWindow(sf::RenderWindow &window);
	void addSprite(sf::Sprite &sprite, int index);
	void addRectangle(sf::RectangleShape &rectangle, int index);
	void addText(sf::Text &text, int index);
	void clear();
	void display();
	void resize(int width, int height);

	sf::View getLetterboxView(sf::View view);
private:
	std::vector<IndexObject> mIndexObjects;
};

