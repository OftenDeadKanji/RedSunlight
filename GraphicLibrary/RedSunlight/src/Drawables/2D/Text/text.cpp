#include "pch.h"
#include "text.h"

namespace RedSunlight {

#pragma region Text

	Text::Text(int x, int y, const std::string& text, const Font& font)
		: m_x(x), m_y(y), m_font(font), m_text(text)
	{
		m_font.setTextToRender(m_text, std::make_pair(m_x, m_y));
	}

	Text::Text(int x, int y, const std::string& text, const Font& font, int color[4])
		: m_x(x), m_y(y), m_font(font), m_text(text)
	{
		m_font.changeColor(color);
		m_font.setTextToRender(m_text, std::make_pair(m_x, m_y));
	}

	Text::~Text()
	{
		m_font.deleteRenderedText();
	}

	std::string& Text::getText()
	{
		return m_text;
	}

	int* Text::getColor()
	{
		return m_font.getColor();
	}

	void Text::draw()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_font.renderText(std::make_pair(m_x, m_y), m_text);

		glDisable(GL_BLEND);
	}

	DrawableType Text::getDrawableType() const
	{
		return DrawableType::eElement2D;
	}

#pragma endregion

}