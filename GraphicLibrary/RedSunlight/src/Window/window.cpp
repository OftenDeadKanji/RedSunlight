#include "pch.h"
#include "window.h"

namespace RedSunlight {

	WindowProperties::WindowProperties(const int width, const int height, const char* title, const WindowMode mode)
		: width(width), height(height), title(title), mode(mode)
	{}
	
	Window::Window(const WindowProperties& properties)
		: m_properties(properties), m_window(nullptr)
	{
		//OpenGL settings
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		createWindow();
		
		if (m_window != nullptr) {
			glfwMakeContextCurrent(m_window);

			if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
				glViewport(0, 0, properties.width, properties.height);

				glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

				GlobalInformation::getInstance().setScreenResolution(properties.width, properties.height);
			}
			else {
				glfwDestroyWindow(m_window);
				//TODO RED_TODO - wyj¹tek dla z³ego GLAD
			}
		}
		//TODO RED_TODO - wyj¹tek dla m_window == NULL
	}

	void Window::createWindow()
	{
		if (m_properties.mode == WindowMode::eWindowed) {
			m_window = glfwCreateWindow(m_properties.width, m_properties.height, m_properties.title.c_str(), nullptr, nullptr);
		}
		else {
			auto* const monitor = glfwGetPrimaryMonitor();

			if (m_properties.mode == WindowMode::eFullscreen) {
				m_window = glfwCreateWindow(m_properties.width, m_properties.height, m_properties.title.c_str(), monitor, nullptr);
			}
			else if (m_properties.mode == WindowMode::eBorderless) {
				const auto* videoMode = glfwGetVideoMode(monitor);

				glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
				glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
				glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
				glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);

				m_window = glfwCreateWindow(videoMode->width, videoMode->height, m_properties.title.c_str(), monitor, nullptr);
			}
		}
	}
	
	Window::Window(Window&& window) noexcept
		: m_properties(std::move(window.m_properties)), m_window(window.m_window)
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
		m_properties = std::move(window.m_properties);
		m_window = window.m_window;
		window.m_window = nullptr;

		return *this;
	}

	void Window::resize(const int newWidth, const int newHeight)
	{
		glfwSetWindowSize(m_window, newWidth, newHeight);
		m_properties.width = newWidth;
		m_properties.height = newHeight;
	}

	/*void Window::setViewport(const int newX, const int newY, const int newWidth, const int newHeight)
	{
		m_viewportX = newX;
		m_viewportY = newY;
		m_viewportWidth = newWidth;
		m_viewportHeight = newHeight;

		glViewport(m_viewportX, m_viewportY, m_viewportWidth, m_viewportHeight);
	}*/

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
			auto* drawable2D = m_drawables[DrawableType::eElement2D].front();
			drawable2D->draw();
			m_drawables[DrawableType::eElement2D].pop();
		}

		glfwSwapBuffers(m_window);
	}

	

	void Window::clearToColor(const int red, const int green, const int blue)
	{
		glClearColor(static_cast<float>(red) / 255.f, static_cast<float>(green) / 255.f, static_cast<float>(blue) / 255.f, 1.0f);
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
