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
		Window(Window&) = default;
		Window(Window&&) = default;
		~Window();

	private:
		int m_width, m_height;
		std::string m_title;
		WindowMode m_mode;
		GLFWwindow* m_window;
	};
}
