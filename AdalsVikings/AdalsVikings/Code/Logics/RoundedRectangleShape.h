#ifndef ROUNDEDRECTANGLESHAPE_HPP
#define ROUNDEDRECTANGLESHAPE_HPP

#include <SFML/Graphics.hpp>

namespace sf
{
	class RoundedRectangleShape : public sf::Shape
	{
	public:
		RoundedRectangleShape(const Vector2f& size = Vector2f(0, 0), float radius = 0, unsigned int cornerPointCount = 0);

		void setSize(const Vector2f& size);

		const Vector2f& getSize() const;

		void setCornersRadius(float radius);

		const float getCornersRadius() const;

		void setCornerPointCount(unsigned int count);

		virtual unsigned int getPointCount() const;

		virtual sf::Vector2f getPoint(unsigned int index) const;

	private:
		Vector2f mSize;
		float mRadius;
		unsigned int mCornerPointCount;
	};
}
#endif // ROUNDEDRECTANGLESHAPE_HPP

////////////////////////////////////////////////////////////
/// \class sf::RoundedRectangleShape
/// \ingroup graphics
///
/// This class inherits all the functions of sf::Transformable
/// (position, rotation, scale, bounds, ...) as well as the
/// functions of sf::Shape (outline, color, texture, ...).
///
/// Usage example:
/// \code
/// sf::RoundedRectangleShape roundedRectangle;
/// rectangle.setSize(sf::Vector2f(100, 50));
/// rectangle.setCornersRadius(5);
/// rectangle.setOutlineThickness(5);
/// rectangle.setPosition(10, 20);
/// ...
/// window.draw(rectangle);
/// \endcode
///
/// \see sf::Shape, sf::CircleShape, sf::ConvexShape
///
////////////////////////////////////////////////////////////