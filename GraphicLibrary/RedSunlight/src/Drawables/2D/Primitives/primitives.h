#pragma once
#include "../../../Shaders/shader.h"

namespace RedSunlight {

	//base class for primitives
	class RED_API Primitive
		: public IDrawable {
	public:
		explicit Primitive(const glm::vec4& color);
		virtual ~Primitive();

	protected:
		void draw() override = 0;
		[[nodiscard]] DrawableType getDrawableType() const override;

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
		Traingle2D(const glm::vec2& left,const glm::vec2& top, const glm::vec2& right, const glm::vec4& color);
		~Traingle2D() = default;

	private:
		void draw() override;
	};

	class RED_API Rectangle2D
		: public Primitive {
	public:
		Rectangle2D(const glm::vec2& upperLeft,const glm::vec2& bottomRight, const glm::vec4& color);
		~Rectangle2D() = default;

	private:
		void draw() override;
	};

}