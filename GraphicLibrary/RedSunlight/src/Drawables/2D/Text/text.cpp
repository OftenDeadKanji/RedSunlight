#include "pch.h"
#include "text.h"

#include <ft2build.h>
#include FT_FREETYPE_H 

namespace RedSunlight {

    #pragma region Font

	Font::Font(const char* fontFilePath, int size)
	{
        createShader();
        
        createCharacters(fontFilePath, size);

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
	}

    Font::~Font()
    {
        delete m_shader;
    }

    void Font::renderText(const std::pair<int, int>& pos, const std::string& text, glm::vec3 color, float scale)
    {
        // activate corresponding render state	
        m_shader->useShader();
        m_shader->setVec3f("textColor", color);
        //glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(m_VAO);

        float x = pos.first;
        float y = pos.second;

        // iterate through all characters
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            Character ch = m_characters[*c];

            float xpos = x + ch.bearing.x * scale;
            float ypos = y - (ch.size.y - ch.bearing.y) * scale;

            float w = ch.size.x * scale;
            float h = ch.size.y * scale;
            // update VBO for each character
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
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
            x += (ch.advance >> 6)* scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Font::createShader()
    {
        const char* vertexSource = R"(
            #version 330 core
            layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
            out vec2 TexCoords;
            
            uniform mat4 projection;
            
            void main()
            {
                gl_Position = projection * vec4(vertex.xy, 1.0, 1.0);
                TexCoords = vertex.zw;
            }
        )";

        const char* fragmentSource = R"(
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

        m_shader = new Shader(vertexSource, ShaderCreationMethod::SHADER_SOURCE_CODE, fragmentSource, ShaderCreationMethod::SHADER_SOURCE_CODE);

        auto screenResolution = GlobalInformation::getInstance().getScreenResolution();
        m_proj = glm::ortho(0.0f, static_cast<float>(screenResolution.first), 0.0f, static_cast<float>(screenResolution.second));
        //m_proj = glm::ortho(0.0f, static_cast<float>(screenResolution.first), static_cast<float>(screenResolution.second), 0.0f, 0.1f, 100.0f);

        m_shader->useShader();
        m_shader->setMat4("projection", m_proj);
        //glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

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
        else {
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
                unsigned int texture;
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
        }
        // destroy FreeType once we're finished
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }

    #pragma endregion

    #pragma region Text

    Text::Text(int x, int y, Font* font, const std::string& text, glm::vec3 color) : m_x(x), m_y(y), m_font(font), m_text(text), m_color(glm::vec3(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f))
    {}

    Text::~Text()
    {
        if (m_font != nullptr)
            delete m_font;
    }

    std::string& Text::getText()
    {
        return m_text;
    }

    glm::vec3& Text::getColor()
    {
        return m_color;
    }

    void Text::draw()
    {
        m_font->renderText(std::pair<int, int>(m_x, m_y), m_text, m_color);
    }

    DrawableType Text::getDrawableType() const
    {
        return DrawableType::ELEMENT_2D;
    }

    #pragma endregion
}