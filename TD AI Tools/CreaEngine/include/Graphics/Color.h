/***************************************************/
/* Nom:	Color.h
/* Description: Color
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _Color_H
#define _Color_H

namespace sf
{
	class Color;
}
namespace crea
{

	class CREAENGINE_API Color
	{
	public:
		sf::Color* m_pColor;

		Color();
		Color(int r, int g, int b, int a);

		virtual ~Color();

		void setValues(int _r, int _g, int _b, int _a);

		static Color RED;
		static Color GREEN;
		static Color BLUE;
		static Color BLACK;
		static Color BLACKGENTIL;
		static Color WHITE;
		static Color YELLOW;
		static Color CYAN;
		static Color MAGENTA;
		static Color TRANSPARENT;
	};
} // namespace crea

#endif // _Color_H