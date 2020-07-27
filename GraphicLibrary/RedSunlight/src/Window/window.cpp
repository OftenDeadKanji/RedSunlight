#include "pch.h"
#include "window.h"

namespace RedSunlight {

	Window::Window(int width, int height, const char* title, WindowMode mode) : m_width(width), m_height(height), m_title(title), m_mode(mode), m_window(NULL)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		if (mode == WindowMode::WINDOWED) {
			m_window = glfwCreateWindow(width, height, title, NULL, NULL);
		}
		else {
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();

			if (mode == WindowMode::FULLSCREEN) {
				m_window = glfwCreateWindow(width, height, title, monitor, NULL);
			}
			else if (mode == WindowMode::BORDERLESS) {
				const GLFWvidmode* mode = glfwGetVideoMode(monitor);

				glfwWindowHint(GLFW_RED_BITS, mode->redBits);
				glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
				glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
				glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

				m_window = glfwCreateWindow(mode->width, mode->height, title, monitor, NULL);
			}
		}
		//TODO REDTODO - wyj¹tek dla m_window == NULL
	}

	Window::~Window()
	{
		if (m_window != NULL)
			glfwDestroyWindow(m_window);
	}

}