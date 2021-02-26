#include "pch.h"
#include "primitives.h"

namespace RedSunlight {

	#pragma region Primitive

	Primitive::Primitive(int color[4])
		: m_color{ color[0], color[1], color[2], color[3] }
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		createShader();

		m_shader->useShader();
		const glm::vec4 glColor(m_color[0] / 255.f, m_color[1] / 255.f, m_color[2] / 255.f, m_color[3] / 255.f);
		m_shader->setVec4f("u_color", glColor);
	}

	Primitive::~Primitive()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);

		delete m_shader;
	}

	void Primitive::changeColor(int color[4])
	{
		for (int i = 0; i < 4; i++)
			m_color[i] = color[i];

		const glm::vec4 glColor(m_color[0] / 255.f, m_color[1] / 255.f, m_color[2] / 255.f, m_color[3] / 255.f);
		m_shader->setVec4f("u_color", glColor);
	}

	void Primitive::createShader()
	{
		const char* const vertexShader = R"(
			#version 400 core 
			layout (location = 0) in vec2 position;
			uniform vec4 u_color;

			out vec4 shapeColor;
			
			void main() 
			{ 
				shapeColor = u_color;
			  gl_Position = vec4(position.x, position.y, -1.0, 1.0); 
			}
		)";

		const char* const fragmentShader = R"(
			#version 400 core 

			in vec4 shapeColor;
			out vec4 color;
			
			void main() 
			{ 
			  color = shapeColor; 
			}
		)";

		m_shader = new Shader(ShaderCreationMethod::eShaderSourceCode, vertexShader, fragmentShader);
	}

	DrawableType Primitive::getDrawableType() const
	{
		return DrawableType::eElement2D;
	}

	#pragma endregion

	#pragma region Triangle2D

	Triangle2D::Triangle2D(int left[2], int top[2], int right[2], int color[4])
		: Primitive(color)
	{
		auto scrRes = GlobalInformation::getInstance().getScreenResolution();
		float glLeftX = left[0] / (0.5f * scrRes.first) - 1;
		float glLeftY = 1 - left[1] / (0.5f * scrRes.second);
		
		float glTopX = top[0] / (0.5f * scrRes.first) - 1;
		float glTopY = 1 - top[1] / (0.5f * scrRes.second);

		float glRightX = right[0] / (0.5f * scrRes.first) - 1;
		float glRightY = 1 - right[1] / (0.5f* scrRes.second);

		GLfloat vertices[] = {
			glLeftX,	glLeftY,	// left 
			glTopX,		glTopY,		// right 
			glRightX,	glRightY	// top 
		};

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
	void Triangle2D::draw()
	{
		m_shader->useShader();

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	#pragma endregion

	#pragma region Rectangle2D

	Rectangle2D::Rectangle2D(int upperLeft[2], int lowerRight[2], int color[4])
		: Primitive(color)
	{
		auto scrRes = GlobalInformation::getInstance().getScreenResolution();
		float glUpperLeftX = upperLeft[0] / (0.5f * scrRes.first) - 1;
		float glUpperLeftY = 1 - upperLeft[1] / (0.5f * scrRes.second);
		
		float glLowerRightX = lowerRight[0] / (0.5f * scrRes.first) - 1;
		float glLowerRightY = 1 - lowerRight[1] / (0.5f * scrRes.second);

		float vertices[] = {
			glUpperLeftX,	glUpperLeftY,
			glLowerRightX,	glUpperLeftY,
			glLowerRightX,	glLowerRightY,

			glLowerRightX,	glLowerRightY,
			glUpperLeftX,	glLowerRightY,
			glUpperLeftX,	glUpperLeftY
		};

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Rectangle2D::draw()
	{
		m_shader->useShader();

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	#pragma endregion
}