#pragma once
#include "../Primitives/primitives.h"

namespace RedSunlight {
	class RED_API Sprite final
		: public IDrawable
	{
	public:
		Sprite(int posX, int posY, int width, int height, const char* imageFilePath, int imageCoords[4]);
		~Sprite();
	private:
		void createTexture(const char* imageFilePath);
		void createShader();

		[[nodiscard]] DrawableType getDrawableType() const override;
		void draw() override;

		int m_x, m_y;
		int m_width, m_height;
		int m_imageWidth, m_imageHeight;
		unsigned int m_texture;
		Shader* m_shader;
		unsigned int m_VBO, m_VAO, m_EBO;
	};

}