#include "pch.h"
#include "sprite.h"

namespace RedSunlight {

	Sprite::Sprite(const int posX, const int posY, const int width, const int height, const char* imageFilePath, int imageCoords[4])
	: m_x(posX), m_y(posY)
	{
		createShader();

		createTexture(imageFilePath);

		const auto scrRes = GlobalInformation::getInstance().getScreenResolution();

		GLfloat spriteCoords[4] = {
			posX / (0.5f * scrRes.first) - 1.0f, 
			1.0f - posY / (0.5f * scrRes.second),
			(posX + width) / (0.5f * scrRes.first) - 1.0f, 
			1.0f - (posY + height) / (0.5f * scrRes.second)
		};

		GLfloat textCoords[4] = {
			static_cast<float>(imageCoords[0]) / m_imageWidth,
			static_cast<float>(m_imageHeight - imageCoords[1]) / m_imageHeight,
			static_cast<float>(imageCoords[2]) / m_imageWidth,
			static_cast<float>(m_imageHeight - imageCoords[3]) / m_imageHeight
		};

		GLfloat vertices[] = {
			//X					//Y					//U				//V
			spriteCoords[0],	spriteCoords[1],	textCoords[0],	textCoords[1],	// top left 
			spriteCoords[2],	spriteCoords[1],	textCoords[2],	textCoords[1],	// top right
			spriteCoords[2],	spriteCoords[3],	textCoords[2],	textCoords[3],	// bottom right
			spriteCoords[0],	spriteCoords[3],	textCoords[0],	textCoords[3]	// bottom left
		};

		GLuint indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
		};

		
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), static_cast<void*>(nullptr));
		glEnableVertexAttribArray(0);

		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	Sprite::~Sprite()
	{
		delete m_shader;
		glDeleteTextures(1, &m_texture);
	}

	void Sprite::createTexture(const char* imageFilePath)
	{
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// load and generate the texture
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		auto* data = stbi_load(imageFilePath, &width, &height, &nrChannels, 0);
		m_imageWidth = width;
		m_imageHeight = height;
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			//TODO RED_TODO komunikat o load image bad
		}
		stbi_image_free(data);
		
		m_shader->useShader();
		m_shader->setInt("ourTexture", 0);
	}

	void Sprite::createShader()
	{
		const auto* const vertexSourceCode = R"(
		#version 400 core
		layout (location = 0) in vec2 aPos;
		layout (location = 1) in vec2 aTexCoord;
		
		out vec2 TexCoord;
		
		void main()
		{
		    gl_Position = vec4(aPos.x, aPos.y, 1.0, 1.0);
		    TexCoord = aTexCoord;
		}
		)";

		const auto* const fragmentSourceCode = R"(
		#version 400 core
		out vec4 FragColor;
		
		in vec2 TexCoord;
		
		uniform sampler2D ourTexture;
		
		void main()
		{
		    FragColor = texture(ourTexture, TexCoord);
		}
		)";

		m_shader = new Shader(ShaderCreationMethod::eShaderSourceCode, vertexSourceCode, fragmentSourceCode);
	}

	DrawableType Sprite::getDrawableType() const
	{
		return DrawableType::eElement2D;
	}

	void Sprite::draw()
	{

		glBindTexture(GL_TEXTURE_2D, m_texture);
		m_shader->useShader();
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

}