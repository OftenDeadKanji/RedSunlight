#pragma once
#include "../../../Shaders/shader.h"


namespace RedSunlight {

	class RED_API Font {
	public:
		Font(const char* fontFilePath, int size);
		Font(const Font&);
		~Font();

		void renderText(const std::pair<int, int>& pos, const std::string& text, const glm::vec3& color, float scale = 1.0f);
	private:
		Shader* m_shader;
		void createShader();

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
		: public IDrawable{
	public:
		Text(int x, int y, const Font& font, const std::string& text, const glm::vec3& color = glm::vec3(255.0f, 255.0f, 255.0f));
		~Text() = default;

		void draw() override;
		[[nodiscard]] DrawableType getDrawableType() const override;

		std::string& getText();
		glm::vec3& getColor();
	private:
		int m_x, m_y;
		Font m_font;
		std::string m_text;
		glm::vec3 m_color;
	};

}