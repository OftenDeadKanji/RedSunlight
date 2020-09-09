#include "pch.h"
#include "cube.h"

namespace RedSunlight {

	Cube::Cube(int centerX, int centerY, int centerZ, int size, int red, int green, int blue, int alpha)
		: m_pos(glm::vec3(centerX, centerY, centerZ)),
		m_size(size),
		m_color(glm::vec4(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f)),
		m_proj(glm::mat4(1.0)), m_view(glm::mat4(1.0)), m_model(glm::mat4(1.0))
	{
		createShader();

		const glm::vec3 upperBackLeft(m_pos.x - 0.5 * size, m_pos.y - 0.5 * size, m_pos.z - 0.5 * size);
		const glm::vec3 lowerFrontRight(m_pos.x + 0.5 * size, m_pos.y + 0.5 * size, m_pos.z + 0.5 * size);

		GLfloat vertices[] = {
			 //X	 //Y	 //Z		//R			//G			//B			//A
			-0.5f,	-0.5f,	-0.5f,		m_color.r,	m_color.g,	m_color.b,	m_color.a,
			-0.5f,	-0.5f,	 0.5f,		m_color.r,	m_color.g,	m_color.b,	m_color.a,
			 0.5f,	-0.5f,	 0.5f,		m_color.r,	m_color.g,	m_color.b,	m_color.a,
			 0.5f,	-0.5f,	-0.5f,		m_color.r,	m_color.g,	m_color.b,	m_color.a,
			-0.5f,	 0.5f,	-0.5f,		m_color.r,	m_color.g,	m_color.b,	m_color.a,
			-0.5f,	 0.5f,	 0.5f,		m_color.r,	m_color.g,	m_color.b,	m_color.a,
			 0.5f,	 0.5f,	 0.5f,		m_color.r,	m_color.g,	m_color.b,	m_color.a,
			 0.5f,	 0.5f,	-0.5f,		m_color.r,	m_color.g,	m_color.b,	m_color.a,

		};

		GLuint indices[] = {
			0, 1, 2,	2, 3, 0,
			1, 5, 6,	6, 2, 5,
			2, 6, 7,	7, 3, 2,
			3, 7, 4,	4, 0, 3,
			0, 4, 5,	5, 1, 0,
			6, 7, 4,	4, 5, 6
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), static_cast<void*>(nullptr));
		glEnableVertexAttribArray(0);

		// color coord attribute
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	DrawableType Cube::getDrawableType() const
	{
		return DrawableType::eElement3D;
	}

	void Cube::draw()
	{
		m_shader->useShader();
		const auto resolution = GlobalInformation::getInstance().getScreenResolution();
		m_proj = glm::perspective(glm::radians(45.0f), static_cast<float>(resolution.first) / static_cast<float>(resolution.second), 0.1f, 100.0f);
		m_shader->setMat4("proj", m_proj);
		m_shader->setMat4("view", m_view);
		m_shader->setMat4("model", m_model);

		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
	}

	void Cube::createShader()
	{
		const char* const vertexShader = R"(
			#version 400 core

			layout (location = 0) in vec3 in_pos;
			layout (location = 1) in vec4 in_color;

			out vec4 fragColor;
			
			uniform mat4 proj;
			uniform mat4 view;
			uniform mat4 model;
			
			void main()
			{
				gl_Position = proj * view * model * vec4(in_pos, 1.0);
				fragColor = in_color;
			}
		)";

		const char* const fragmentShader = R"(
			#version 400 core 

			in vec4 fragColor;

			out vec4 color;
			
			void main()
			{
				color = fragColor;
			}
		)";

		m_shader = new Shader(ShaderCreationMethod::eShaderSourceCode, vertexShader, fragmentShader);

		const auto resolution = GlobalInformation::getInstance().getScreenResolution();

		m_proj = glm::perspective(glm::radians(45.0f), static_cast<float>(resolution.first) / static_cast<float>(resolution.second), 0.1f, 100.0f);
		m_view = translate(m_view, glm::vec3(0.0f, 0.0f, -3.0f));
		//m_model = scale(m_model, glm::vec3(0.5f, 0.5f, 0.5f));
		//m_model = translate(m_model, glm::vec3(-0.5f, -0.5f, 0.0f));

		
		m_shader->useShader();
		m_shader->setMat4("proj", m_proj);
		m_shader->setMat4("view", m_view);
		m_shader->setMat4("model", m_model);
	}

	void Cube::setModel(glm::vec3 pos, int size)
	{
		const auto screenResolution = 1;
	}

}