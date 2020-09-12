#pragma once
#include "../../shader.h"
#include "Font/font.h"

namespace RedSunlight {

	class Text 
		: public IDrawable {
	public:
		Text(int x, int y, const std::string& text, const Font& font);
		Text(int x, int y, const std::string& text, const Font& font, int color[4]);
		~Text();
		 
		void draw() override;
		[[nodiscard]] DrawableType getDrawableType() const override;

		std::string& getText();
		int* getColor();
	private:
		int m_x, m_y;
		Font m_font;
		std::string m_text;
	};

}