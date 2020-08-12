#include "pch.h"
#include "primitives.h"

namespace RedSunlight {

	#pragma region Primitive

	Primitive::Primitive(const glm::vec4& color)
		: m_color(glm::vec4(color.x / 255.f, color.y / 255.f, color.z / 255.f, color.w / 255.f)),
		m_proj(glm::mat4(1.0f)), m_view(glm::mat4(1.0f)), m_model(glm::mat4(1.0f))
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		const auto* const vertexShader = R"(
			#version 400 core  
			layout (location = 0) in vec3 position;
			
			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 projection;

			void main()  
			{  
			    gl_Position = projection * view * model * vec4(position, 1.0);  
			}
		)";

		const auto* const fragmentShader = R"(
			#version 400 core 

			uniform vec4 shapeColor;
			out vec4 color;
			
			void main()  
			{  
			    color = shapeColor;  
			}
		)";

		m_shader = new Shader(ShaderCreationMethod::eShaderSourceCode, vertexShader, fragmentShader);

		const auto screenResolution = GlobalInformation::getInstance().getScreenResolution();

		m_proj = glm::ortho(0.0f, static_cast<float>(screenResolution.first), static_cast<float>(screenResolution.second), 0.0f, 0.1f, 100.0f);
		m_view = glm::translate(m_view, glm::vec3(0.0f, 0.0f, -1.0f));
	}

	Primitive::~Primitive()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);

		delete m_shader;
	}

	DrawableType Primitive::getDrawableType() const
	{
		return DrawableType::eElement2D;
	}

	#pragma endregion

	#pragma region Triangle2D

	Traingle2D::Traingle2D(const glm::vec2& left, const glm::vec2& top, const glm::vec2& right, const glm::vec4& color)
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

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
	void Traingle2D::draw()
	{
		m_shader->useShader();
		m_shader->setVec4f("shapeColor", m_color);
		m_shader->setMat4("model", m_model);
		m_shader->setMat4("view", m_view);
		m_shader->setMat4("projection", m_proj);

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	#pragma endregion

	#pragma region Rectangle2D

	Rectangle2D::Rectangle2D(const glm::vec2& upperLeft, const glm::vec2& bottomRight, const glm::vec4& color)
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

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Rectangle2D::draw()
	{
		m_shader->useShader();
		m_shader->setVec4f("shapeColor", m_color);
		m_shader->setMat4("model", m_model);
		m_shader->setMat4("view", m_view);
		m_shader->setMat4("projection", m_proj);

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	#pragma endregion
}