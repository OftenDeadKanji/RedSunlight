#pragma once

namespace RedSunlight {

	enum class RED_API WindowMode {
		WINDOWED,
		FULLSCREEN,
		BORDERLESS
	};

	class RED_API Window
	{
	public:
		Window(int width, int height, const char* title, WindowMode mode);
		Window(Window&&) noexcept;
		~Window();

		void setViewport(int newX, int newY, int newWidth, int newHeight);
		
		void clearToColor(int r, int g, int b);
		void drawElement(IDrawable*);
		void displayContent();

	private:
		int m_window_width, m_window_height;
		int m_viewport_x, m_viewport_y, m_viewport_width, m_viewport_height;
		std::string m_title;

		WindowMode m_mode;
		GLFWwindow* m_window;

		std::unordered_map<DrawableType, std::queue<IDrawable*>> m_drawables;
	};
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
