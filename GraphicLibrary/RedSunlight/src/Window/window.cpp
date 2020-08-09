#include "pch.h"
#include "window.h"

namespace RedSunlight {

	Window::Window(const int width, const int height, const char* title, const WindowMode mode)
		: m_windowWidth(width), m_windowHeight(height), m_viewportX(0), m_viewportY(0), m_viewportWidth(width),
		  m_viewportHeight(height), m_title(title), m_mode(mode), m_window(nullptr)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		if (mode == WindowMode::eWindowed) {
			m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		}
		else {
			auto* const monitor = glfwGetPrimaryMonitor();

			if (mode == WindowMode::eFullscreen) {
				m_window = glfwCreateWindow(width, height, title, monitor, nullptr);
			}
			else if (mode == WindowMode::eBorderless) {
				const auto* videoMode = glfwGetVideoMode(monitor);

				glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
				glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
				glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
				glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);

				m_window = glfwCreateWindow(videoMode->width, videoMode->height, title, monitor, NULL);
			}
		}

		if (m_window != nullptr) {
			glfwMakeContextCurrent(m_window);

			if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
				glViewport(m_viewportX, m_viewportY, m_viewportWidth, m_viewportHeight);

				glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

				GlobalInformation::getInstance().setScreenResolution(m_windowWidth, m_windowHeight);
			}
			else {
				glfwDestroyWindow(m_window);
				//TODO RED_TODO - wyj¹tek dla z³ego GLAD
			}
		}
		//TODO RED_TODO - wyj¹tek dla m_window == NULL
	}

	Window::Window(Window&& window) noexcept
		: m_windowWidth(window.m_windowWidth), m_windowHeight(window.m_windowHeight), m_viewportX(window.m_viewportX),
		  m_viewportY(window.m_viewportY), m_viewportWidth(window.m_viewportWidth),
		  m_viewportHeight(window.m_viewportHeight), m_title(std::move(window.m_title)), m_mode(window.m_mode),
		  m_window(window.m_window)
	{
		window.m_window = nullptr;
	}

	Window::~Window()
	{
		if (m_window != nullptr)
			glfwDestroyWindow(m_window);
	}

	Window& Window::operator=(Window&& window) noexcept
	{
		m_windowWidth = window.m_windowWidth;
		m_windowHeight = window.m_windowHeight;
		
		m_viewportX = window.m_viewportX;
		m_viewportY = window.m_viewportY;
		m_viewportWidth = window.m_viewportWidth;
		m_viewportHeight = window.m_viewportHeight;
		
		m_title = std::move(window.m_title);
		m_mode = window.m_mode;
		m_window = window.m_window;
		window.m_window = nullptr;

		return *this;
	}

	void Window::setViewport(const int newX, const int newY, const int newWidth, const int newHeight)
	{
		m_viewportX = newX;
		m_viewportY = newY;
		m_viewportWidth = newWidth;
		m_viewportHeight = newHeight;

		glViewport(m_viewportX, m_viewportY, m_viewportWidth, m_viewportHeight);
	}

	void Window::displayContent()
	{
		glEnable(GL_DEPTH_TEST);

		while (!m_drawables[DrawableType::eElement3D].empty()) {
			auto* drawable3D = m_drawables[DrawableType::eElement3D].front();
			drawable3D->draw();
			m_drawables[DrawableType::eElement3D].pop();
		}

		glDisable(GL_DEPTH_TEST);

		while (!m_drawables[DrawableType::eElement2D].empty()) {
			auto drawable2D = m_drawables[DrawableType::eElement2D].front();
			drawable2D->draw();
			m_drawables[DrawableType::eElement2D].pop();
		}

		glfwSwapBuffers(m_window);
	}

	void Window::clearToColor(const int r, const int g, const int b)
	{
		glClearColor(r / 255.f, g / 255.f, b / 255.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::drawElement(IDrawable* drawable)
	{
		m_drawables[drawable->getDrawableType()].push(drawable);
	}
}

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}