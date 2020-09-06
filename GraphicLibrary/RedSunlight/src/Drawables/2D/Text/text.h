#pragma once
#include "../../../Shaders/shader.h"


namespace RedSunlight {

	class RED_API Font {
	public:
		Font(const char* fontFilePath, int size);
		Font(const char* fontFilePath, int size, int color[4]);
		Font(const Font&);
		~Font();

		void renderText(const std::pair<int, int>& pos, const std::string& text);

		void changeColor(int color[4]);
		int* getColor();
	private:
		Shader* m_shader;
		int m_color[4];
		void createShader();
		void setColor();

		struct Character {
			unsigned int textureID;  // ID handle of the glyph texture
			glm::ivec2   size;       // Size of glyph
			glm::ivec2   bearing;    // Offset from baseline to left/top of glyph
			unsigned int advance;    // Offset to advance to next glyph
		};
		std::map<char, Character> m_characters;
		void createCharacters(const char* fontFilePath, int size);

		unsigned int m_VAO, m_VBO;
		glm::mat4 m_proj;
	};

	class RED_API Text 
		: public IDrawable {
	public:
		Text(int x, int y, const std::string& text, const Font& font);
		Text(int x, int y, const std::string& text, const Font& font, int color[4]);
		~Text() = default;
		 
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