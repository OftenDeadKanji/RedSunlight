#pragma once
#include "../../../Shaders/shader.h"

namespace RedSunlight {

	//base class for primitives
	class RED_API Primitive
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

	class RED_API Traingle2D
		: public Primitive {
	public:
		Traingle2D(int left[2], int top[2], int right[2], int color[4]);
		~Traingle2D() = default;

	private:
		void draw() override;
	};

	class RED_API Rectangle2D
		: public Primitive {
	public:
		Rectangle2D(int upperLeft[2], int bottomRight[2], int color[4]);
		~Rectangle2D() = default;

	private:
		void draw() override;
	};

}