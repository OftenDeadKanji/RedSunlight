#pragma once
#include "../Event System/eventManager.h"


namespace RedSunlight {

	class EventManager;

	enum class RED_API WindowMode {
		eWindowed,
		eFullscreen,
		eBorderless
	};

	class RED_API Window
	{
	public:
		Window(int width, int height, const char* title, WindowMode mode);
		Window(Window&) = delete;
		Window(Window&&) noexcept;
		~Window();

		Window& operator=(Window&) = delete;
		Window& operator=(Window&&) noexcept;
		
		void setViewport(int newX, int newY, int newWidth, int newHeight);

		static void clearToColor(int r, int g, int b);
		void drawElement(IDrawable*);
		void displayContent();

	private:
		friend class EventManager;
		friend class Mouse;

		int m_windowWidth, m_windowHeight;
		int m_viewportX, m_viewportY, m_viewportWidth, m_viewportHeight;
		std::string m_title;

		WindowMode m_mode;
		GLFWwindow* m_window;
		std::unordered_map<DrawableType, std::queue<IDrawable*>> m_drawables;
	};
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
