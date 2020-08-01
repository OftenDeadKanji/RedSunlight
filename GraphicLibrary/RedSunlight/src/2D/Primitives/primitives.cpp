#include "pch.h"
#include "primitives.h"

namespace RedSunlight {

	#pragma region Primitive
	Primitive::Primitive(glm::vec4 color)
		: m_color(glm::vec4(color.x / 255.f, color.y / 255.f, color.z / 255.f, color.w / 255.f))
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		const char* vertexShader = R"(
			#version 330 core  
			layout (location = 0) in vec3 position;
			
			void main()  
			{  
			    gl_Position = vec4(position.x, position.y, position.z, 1.0);  
			}
		)";

		const char* fragmentShader = R"(
			#version 330 core 

			uniform vec4 shapeColor;
			out vec4 color;
			
			void main()  
			{  
			    color = shapeColor;  
			}
		)";

		m_shader = new Shader(vertexShader, ShaderCreationMethod::SHADER_SOURCE_CODE, fragmentShader, ShaderCreationMethod::SHADER_SOURCE_CODE);
	}

	Primitive::~Primitive()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);

		delete m_shader;
	}
	#pragma endregion

	#pragma region Triangle2D
	Traingle2D::Traingle2D(glm::vec2 left, glm::vec2 top, glm::vec2 right, const glm::vec4& color) 
		: Primitive(color)
	{
		float vertices[] = {
			left.x,		left.y,		0.0f, // left  
			top.x,		top.y,		0.0f, // right 
			right.x,	right.y,	0.0f  // top  
		};

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	Traingle2D::~Traingle2D()
	{}

	void Traingle2D::draw()
	{
		m_shader->useShader();
		m_shader->setVec4f("shapeColor", m_color);

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	#pragma endregion

	#pragma region Rectangle2D

	Rectangle2D::Rectangle2D(glm::vec2 upperLeft, glm::vec2 bottomRight, const glm::vec4& color)
		: Primitive(color)
	{
		float vertices[] = {
			upperLeft.x,	upperLeft.y,	0.0f,
			bottomRight.x,	upperLeft.y,	0.0f,
			bottomRight.x,	bottomRight.y,	0.0f,

			bottomRight.x,	bottomRight.y,	0.0f,
			upperLeft.x,	bottomRight.y,	0.0f,
			upperLeft.x,	upperLeft.y,	0.0f
		};

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Rectangle2D::~Rectangle2D()
	{
	}

	void Rectangle2D::draw()
	{
		m_shader->useShader();
		m_shader->setVec4f("shapeColor", m_color);

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	#pragma endregion
}