#include "pch.h"
#include "sprite.h"

namespace RedSunlight {

	Sprite::Sprite(int posX, int posY, int width, int height, const char* imageFilePath, std::tuple<int, int, int, int> imageCoords) : m_x(posX), m_y(posY), m_proj(glm::mat4(1.0f))
	{
		createTexture(imageFilePath);

		createShader();

		auto textCoords = std::make_tuple(
			(float)std::get<0>(imageCoords) / (float)m_imageWidth,
			(float)(m_imageHeight - std::get<1>(imageCoords)) / (float)m_imageHeight,
			(float)std::get<2>(imageCoords) / (float)m_imageWidth,
			(float)(m_imageHeight - std::get<3>(imageCoords)) / (float)m_imageHeight);

		float vertices[] = {
			//X				Y				Z					//U							V
			posX,			posY,			-0.5f,				std::get<0>(textCoords),	std::get<1>(textCoords),			// top left 
			posX + width,	posY,			-0.5f,				std::get<2>(textCoords),	std::get<1>(textCoords),			// top right
			posX + width,	posY + height,	-0.5f,				std::get<2>(textCoords),	std::get<3>(textCoords),			// bottom right
			posX,			posY + height,	-0.5f,				std::get<0>(textCoords),	std::get<3>(textCoords)			// bottom left
		};
		unsigned int indices[] = {
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	RedSunlight::Sprite::~Sprite()
	{
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
		unsigned char* data = stbi_load(imageFilePath, &width, &height, &nrChannels, 0);
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
	}

	void Sprite::createShader()
	{
		const char* vertexSourceCode = R"(
		#version 400 core
		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec2 aTexCoord;
		
		out vec2 TexCoord;
		
		uniform mat4 proj;

		void main()
		{
		    gl_Position = proj * vec4(aPos, 1.0);
		    TexCoord = aTexCoord;
		}
		)";

		const char* fragmentSourceCode = R"(
		#version 400 core
		out vec4 FragColor;
		
		in vec2 TexCoord;
		
		uniform sampler2D ourTexture;
		
		void main()
		{
		    FragColor = texture(ourTexture, TexCoord);
		}
		)";

		m_shader = new Shader(vertexSourceCode, ShaderCreationMethod::SHADER_SOURCE_CODE, fragmentSourceCode, ShaderCreationMethod::SHADER_SOURCE_CODE);

		auto screenResolution = GlobalInformation::getInstance().getScreenResolution();
		m_proj = glm::ortho(0.0f, static_cast<float>(screenResolution.first), static_cast<float>(screenResolution.second), 0.0f, 0.1f, 100.0f);
	}

	DrawableType Sprite::getDrawableType() const
	{
		return DrawableType::ELEMENT_2D;
	}

	void Sprite::draw()
	{
		m_shader->useShader();
		m_shader->setInt("ourTexture", 0);
		m_shader->setMat4("proj", m_proj);

		glBindTexture(GL_TEXTURE_2D, m_texture);
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

}