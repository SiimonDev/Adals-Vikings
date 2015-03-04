#include "RoundedRectangleShape.h"
#include <cmath>

namespace sf
{
	RoundedRectangleShape::RoundedRectangleShape(const Vector2f& size, float radius, unsigned int cornerPointCount)
	{
		mSize = size;
		mRadius = radius;
		mCornerPointCount = cornerPointCount;
		update();
	}

	void RoundedRectangleShape::setSize(const Vector2f& size)
	{
		mSize = size;
		update();
	}

	const Vector2f& RoundedRectangleShape::getSize() const
	{
		return mSize;
	}
	void RoundedRectangleShape::setCornersRadius(float radius)
	{
		mRadius = radius;
		update();
	}

	const float RoundedRectangleShape::getCornersRadius() const
	{
		return mRadius;
	}

	void RoundedRectangleShape::setCornerPointCount(unsigned int count)
	{
		mCornerPointCount = count;
		update();
	}

	unsigned int RoundedRectangleShape::getPointCount() const
	{
		return mCornerPointCount * 4;
	}

	sf::Vector2f RoundedRectangleShape::getPoint(unsigned int index) const
	{
		if (index >= mCornerPointCount * 4)
			return sf::Vector2f(0, 0);

		float deltaAngle = 90.0f / (mCornerPointCount - 1);
		sf::Vector2f center;
		unsigned int centerIndex = index / mCornerPointCount;
		unsigned int offset = 0;
		static const float pi = 3.141592654f;

		switch (centerIndex)
		{
		case 0: center.x = mSize.x - mRadius; center.y = mRadius; break;
		case 1: center.x = mRadius; center.y = mRadius; break;
		case 2: center.x = mRadius; center.y = mSize.y - mRadius; break;
		case 3: center.x = mSize.x - mRadius; center.y = mSize.y - mRadius; break;
		}

		return sf::Vector2f(mRadius*cos(deltaAngle*(index - centerIndex)*pi / 180) + center.x,
			mRadius*sin(deltaAngle*(index - centerIndex)*pi / 180) - center.y);
	}
}