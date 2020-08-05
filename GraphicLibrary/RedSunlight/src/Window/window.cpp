#include "pch.h"
#include "window.h"
#include "../../Drawables/2D/Text/text.h"

namespace RedSunlight {

	Window::Window(int width, int height, const char* title, WindowMode mode)
		: m_window_width(width), m_window_height(height), m_title(title), m_mode(mode), m_window(NULL), m_viewport_x(0), m_viewport_y(0), m_viewport_width(width), m_viewport_height(height)
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

		if (m_window != NULL) {
			glfwMakeContextCurrent(m_window);

			if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				glViewport(m_viewport_x, m_viewport_y, m_viewport_width, m_viewport_height);

				glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

				GlobalInformation::getInstance().setScreenResolution(m_window_width, m_window_height);
			}
			else {
				glfwDestroyWindow(m_window);
				//TODO RED_TODO - wyj¹tek dla z³ego GLAD
			}
		}
		//TODO RED_TODO - wyj¹tek dla m_window == NULL
	}

	Window::Window(Window&& window) noexcept
		: m_window_width(window.m_window_width), m_window_height(window.m_window_height), m_title(window.m_title), m_mode(window.m_mode), m_window(window.m_window), m_viewport_x(window.m_viewport_x), m_viewport_y(window.m_viewport_y), m_viewport_width(window.m_viewport_width), m_viewport_height(window.m_viewport_height)
	{
		window.m_window = NULL;
	}

	Window::~Window()
	{
		if (m_window != NULL)
			glfwDestroyWindow(m_window);
	}

	void Window::setViewport(int newX, int newY, int newWidth, int newHeight)
	{
		m_viewport_x = newX;
		m_viewport_y = newY;
		m_viewport_width = newWidth;
		m_viewport_height = newHeight;

		glViewport(m_viewport_x, m_viewport_y, m_viewport_width, m_viewport_height);
	}

	void Window::displayContent()
	{
		glEnable(GL_DEPTH_TEST);

		while (!m_drawables[DrawableType::ELEMENT_3D].empty()) {
			IDrawable* drawable3D = m_drawables[DrawableType::ELEMENT_3D].front();
			drawable3D->draw();
			m_drawables[DrawableType::ELEMENT_3D].pop();
		}

		glDisable(GL_DEPTH_TEST);

		while (!m_drawables[DrawableType::ELEMENT_2D].empty()) {
			IDrawable* drawable2D = m_drawables[DrawableType::ELEMENT_2D].front();
			drawable2D->draw();
			m_drawables[DrawableType::ELEMENT_2D].pop();
		}

		glfwSwapBuffers(m_window);
	}

	void Window::clearToColor(int r, int g, int b)
	{
		glClearColor(r / 255.f, g / 255.f, b / 255.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::drawElement(IDrawable* drawable)
	{
		m_drawables[drawable->getDrawableType()].push(drawable);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}