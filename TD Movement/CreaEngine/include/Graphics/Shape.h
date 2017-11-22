/***************************************************/
/* Nom:	Shape.h
/* Description: Shape
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _Shape_H
#define _Shape_H

namespace sf
{
	class Shape;
}
namespace crea
{

	class CREAENGINE_API Shape
	{
	public:
		sf::Shape* m_pShape;

		Shape();

		~Shape();

		virtual void draw();

		virtual void setColor(Color* _pColor);

		virtual void setOutlineColor(Color* _pColor);

		virtual void setOutlineThickness(float _fPixels);

		virtual void setPosition(float _x, float _y);
	};

	class CREAENGINE_API RectangleShape : public Shape
	{
	public:

		RectangleShape();

		~RectangleShape();

		virtual void setSize(float _x, float _y);
	};
} // namespace crea

#endif // _Shape_H