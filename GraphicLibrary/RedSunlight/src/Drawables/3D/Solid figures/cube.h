#pragma once
#include "../../../Shaders/shader.h"

namespace RedSunlight {

	class RED_API Cube
		: public IDrawable
	{
	public:
		Cube(int centerX, int centerY, int centerZ, int size, int red, int green, int blue, int alpha);
		Cube(const Cube&) = default;
		Cube(Cube&&) = default;
		~Cube() = default;

		Cube& operator=(const Cube&) = default;
		Cube& operator=(Cube&&) = default;

		[[nodiscard]] DrawableType getDrawableType() const override;
		void draw() override;
	private:
		void createShader();
		void setModel(glm::vec3 pos, int size);
		glm::vec3 m_pos;
		int m_size;
		glm::vec4 m_color;

		unsigned int m_VAO, m_VBO, m_EBO;
		Shader* m_shader;

		glm::mat4 m_proj;
		glm::mat4 m_view;
		glm::mat4 m_model;
	};

}