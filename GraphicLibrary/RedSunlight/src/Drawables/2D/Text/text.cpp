#include "pch.h"
#include "text.h"

#include <ft2build.h>
#include FT_FREETYPE_H 

namespace RedSunlight {

#pragma region Font

	Font::Font(const char* fontFilePath, const int size) 
		: m_color {0, 0, 0, 0}
	{
		createShader();
		
		setColor();

		createCharacters(fontFilePath, size);

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Font::Font(const char* fontFilePath, int size, int color[4])
	{
		createShader();

		for (int i = 0; i < 4; i++)
			m_color[i] = color[i];

		setColor();

		createCharacters(fontFilePath, size);

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Font::Font(const Font& font) 
		: m_characters(font.m_characters)
	{
		createShader();

		setColor();

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Font::~Font()
	{
		glDeleteBuffers(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		delete m_shader;
	}

	void Font::createShader()
	{
		const char* const vertexSource = R"(
            #version 330 core
            layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
            out vec2 TexCoords;
            
            void main()
            {
                gl_Position = vec4(vertex.xy, 1.0, 1.0);
                TexCoords = vertex.zw;
            }
        )";

		const char* const fragmentSource = R"(
            #version 330 core
            in vec2 TexCoords;
            out vec4 color;
            
            uniform sampler2D text;
            uniform vec3 textColor;
            
            void main()
            {    
                vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
                color = vec4(textColor, 1.0) * sampled;
            } 
        )";

		m_shader = new Shader(ShaderCreationMethod::eShaderSourceCode, vertexSource, fragmentSource);
	}
	
	void Font::createCharacters(const char* fontFilePath, int size)
	{
		FT_Library ft;
		// All functions return a value different than 0 whenever an error occurred
		if (FT_Init_FreeType(&ft))
		{
			//TODO RED_TODO komunikat error
			return;
		}

		/*
		// find path to font
		std::string font_name = FileSystem::getPath("resources/fonts/Antonio-Bold.ttf");
		if (font_name.empty())
		{
			//TODO RED_TODO komunikat error
			return;
		}
		*/

		// load font as face
		FT_Face face;
		if (FT_New_Face(ft, fontFilePath, 0, &face)) {
			//TODO RED_TODO komunikat error
			return;
		}
		
		// set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, size);

		// disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// load first 128 characters of ASCII set
		for (unsigned char c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				//TODO RED_TODO komunikat
				continue;
			}
			// generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// now store character for later use
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			m_characters.insert(std::pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		// destroy FreeType once we're finished
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}

	void Font::setColor()
	{
		const glm::vec4 glColor(m_color[0] / 255.f, m_color[1] / 255.f, m_color[2] / 255.f, m_color[3] / 255.f);
		m_shader->useShader();
		m_shader->setVec4f("textColor", glColor);
	}

	void Font::changeColor(int color[4])
	{
		for (int i = 0; i < 4; i++)
			m_color[i] = color[i];
		
		setColor();
	}

	int* Font::getColor()
	{
		return m_color;
	}

	void Font::renderText(const std::pair<int, int>& pos, const std::string& text)
	{
		// activate corresponding render state	
		m_shader->useShader();
		
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(m_VAO);

		float x = pos.first;
		float y = pos.second;

		for (auto c : text)
		{
			const Character ch = m_characters[c];

			const float xpos = x + ch.bearing.x;
			const float ypos = y - ch.bearing.y;

			const std::pair<int, int> scrRes = GlobalInformation::getInstance().getScreenResolution();
			
			const float x1 = xpos / (0.5f * scrRes.first) - 1.0f;
			const float x2 = (xpos + ch.size.x) / (0.5f * scrRes.first) - 1.0f;

			const float y1 = 1.0f - (ypos + ch.size.y) / (0.5f * scrRes.second);
			const float y2 = 1.0f - ypos / (0.5f * scrRes.second);
			
			// update VBO for each character
			float vertices[6][4] = {
				{ x1,	y1,		0.0f, 1.0f },
				{ x1,	y2,		0.0f, 0.0f },
				{ x2,	y2,		1.0f, 0.0f },

				{ x1,	y1,		0.0f, 1.0f },
				{ x2,	y2,		1.0f, 0.0f },
				{ x2,	y1,		1.0f, 1.0f }
			};
			
			// render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.textureID);
			
			// update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			
			// render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.advance >> 6); // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
#pragma endregion

#pragma region Text

	Text::Text(int x, int y, const std::string& text, const Font& font)
		: m_x(x), m_y(y), m_font(font), m_text(text)
	{}

	Text::Text(int x, int y, const std::string& text, const Font& font, int color[4])
		: m_x(x), m_y(y), m_font(font), m_text(text)
	{
		m_font.changeColor(color);
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