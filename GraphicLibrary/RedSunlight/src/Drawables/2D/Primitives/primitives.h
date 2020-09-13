#pragma once
#include "../../shader.h"

namespace RedSunlight {

	//base class for primitives
	class Primitive
		: public IDrawable {
	public:
		explicit Primitive(int color[4]);
		virtual ~Primitive();

		void changeColor(int color[4]);
	private:
		void createShader();

	protected:
		void draw() override = 0;
		[[nodiscard]] DrawableType getDrawableType() const override;

		GLuint m_VBO, m_VAO;
		Shader* m_shader;
		int m_color[4];
	};

	class Triangle2D
		: public Primitive {
	public:
		Triangle2D(int left[2], int top[2], int right[2], int color[4]);
		~Triangle2D() = default;
		void draw() override;
	};

	class Rectangle2D
		: public Primitive {
	public:
		Rectangle2D(int upperLeft[2], int bottomRight[2], int color[4]);
		~Rectangle2D() = default;
		void draw() override;
	};

}