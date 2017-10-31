#include "stdafx.h"

#include "Graphics\Color.h"

#include <SFML/Graphics.hpp>

namespace crea
{

	Color Color::RED = Color::Color(255, 0, 0, 255);
	Color Color::GREEN = Color::Color(0, 255, 0, 255);
	Color Color::BLUE = Color::Color(0, 0, 255, 255);
	Color Color::BLACK = Color::Color(0, 0, 0, 255);
	Color Color::BLACKGENTIL = Color::Color(0, 0, 0, 64);
	Color Color::WHITE = Color::Color(255, 255, 255, 255);
	Color Color::CYAN = Color::Color(255, 255, 0, 255);
	Color Color::MAGENTA = Color::Color(255, 0, 255, 255);
	Color Color::YELLOW = Color::Color(0, 255, 255, 255);
	Color Color::TRANSPARENT = Color::Color(0, 0, 0, 0);

	Color::Color()
	{
		m_pColor = new sf::Color;
	}

	Color::Color(int r, int g, int b, int a)
	{
		m_pColor = new sf::Color(r, g, b, a);
	}

	Color::~Color()
	{
		delete m_pColor;
	}

	void Color::setValues(int _r, int _g, int _b, int _a)
	{
		m_pColor->r = _r;
		m_pColor->g = _g;
		m_pColor->b = _b;
		m_pColor->a = _a;
	}

} // namespace crea
