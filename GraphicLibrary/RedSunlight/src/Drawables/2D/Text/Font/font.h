#pragma once
#include "../../../shader.h"

namespace RedSunlight {
	class Font {
	public:
		Font(const char* fontFilePath, int size);
		Font(const char* fontFilePath, int size, int color[4]);
		Font(const Font&);
		~Font();

		void renderText(const std::pair<int, int>& pos, const std::string& text);

		void changeColor(int color[4]);
		int* getColor();
		void setTextToRender(const std::string& text, std::pair<int, int> pos);
		void deleteRenderedText();
	private:
		void createShader();
		void setColor();

		struct Character {
			unsigned int textureID; // ID handle of the glyph texture
			glm::ivec2  size;    // Size of glyph
			glm::ivec2  bearing;  // Offset from baseline to left/top of glyph
			unsigned int advance;  // Offset to advance to next glyph
		};
		std::map<char, Character> m_characters;
		void createCharacters(const char* fontFilePath, int size);

		Shader* m_shader;

		GLuint* m_VAOs;
		int m_sizeVAOs;

		GLuint* m_VBOs;
		int m_sizeVBOs;

		glm::mat4 m_proj;
		int m_color[4];
	};

}