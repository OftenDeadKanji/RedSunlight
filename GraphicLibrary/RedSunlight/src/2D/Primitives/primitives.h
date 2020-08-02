#pragma once
#include "../../Shaders/shader.h"

namespace RedSunlight {

	//base class for primitives
	class RED_API Primitive {
	public:
		Primitive(glm::vec4 color);
		~Primitive();

		virtual void draw() = 0;
	protected:
		GLuint m_VBO, m_VAO;
		Shader* m_shader;
		glm::vec4 m_color;

		glm::mat4 m_proj;
		glm::mat4 m_view;
		glm::mat4 m_model;
	};

	class RED_API Traingle2D
		: public Primitive {
	public:
		Traingle2D(glm::vec2 left, glm::vec2 top, glm::vec2 right, const glm::vec4& color);
		~Traingle2D();

		void draw() override;
	};

	class RED_API Rectangle2D
		: public Primitive {
	public:
		Rectangle2D(glm::vec2 upperLeft, glm::vec2 bottomRight, const glm::vec4& color);
		~Rectangle2D();

		void draw() override;
	};

}