#pragma once
#include "../Event System/eventManager.h"


namespace RedSunlight {

	class EventManager;

	enum class RED_API WindowMode {
		eWindowed,
		eFullscreen,
		eBorderless
	};

	struct RED_API WindowProperties {
		WindowProperties(int width, int height, const char* title, WindowMode mode);
		WindowProperties(const WindowProperties&) = default;
		WindowProperties(WindowProperties&&) = default;
		~WindowProperties() = default;

		WindowProperties& operator=(const WindowProperties&) = default;
		WindowProperties& operator=(WindowProperties&&) = default;
		
		int width, height;
		std::string title;
		WindowMode mode;
	};
	
	class RED_API Window
	{
	public:
		explicit Window(const WindowProperties& properties);
		Window(Window&) = delete;
		Window(Window&&) noexcept;
		~Window();

		Window& operator=(Window&) = delete;
		Window& operator=(Window&&) noexcept;
		
		//void setViewport(int newX, int newY, int newWidth, int newHeight);
		void resize(int newWidth, int newHeight);

		static void clearToColor(int red, int green, int blue);
		void drawElement(IDrawable*);
		void displayContent();

	private:
		friend class EventManager;
		friend class Mouse;
		friend class Keyboard;

		void createWindow();

		WindowProperties m_properties;
		GLFWwindow* m_window;
		std::unordered_map<DrawableType, std::queue<IDrawable*>> m_drawables;
	};
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
