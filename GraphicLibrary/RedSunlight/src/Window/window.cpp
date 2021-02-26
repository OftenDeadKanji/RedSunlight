#include "pch.h"
#include "window.h"

namespace RedSunlight
{
#pragma region GLFW Callbacks
	void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
	{
		glViewport(0, 0, width, height);
	}

	void window_close_callback(GLFWwindow* window)
	{
		auto* userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		if (userWindow)
		{
			userWindow->windowCloseCallback(glfwWindowShouldClose(window));
		}
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		auto* userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		if (userWindow)
		{
			userWindow->keyCallback(key, scancode, action, mods);
		}
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		auto* userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		if (userWindow)
		{
			userWindow->mouseButtonCallback(button, action, mods);
		}
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		auto* userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		if (userWindow)
		{
			userWindow->cursorPositionCallback(xpos, ypos);
		}
	}
#pragma endregion

	Window::Window(WindowProperties properties)
		: properties(std::move(properties))
	{
		initOpenGL();
		createGLFWWindow();

		if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			glViewport(0, 0, properties.width, properties.height);

			glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

			GlobalInformation::getInstance().setScreenResolution(properties.width, properties.height);
		}
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
	}

	void Window::centerWindow()
	{
		const auto monitor = glfwGetPrimaryMonitor();
		if (!monitor)
			return;

		const auto mode = glfwGetVideoMode(monitor);
		if (!mode)
			return;

		int monitorX, monitorY;
		glfwGetMonitorPos(monitor, &monitorX, &monitorY);

		int windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		glfwSetWindowPos(window, monitorX + (mode->width - windowWidth) / 2, monitorY + (mode->height - windowHeight) / 2);
	}

	void Window::clearToColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		glClearColor(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::clearToColorf(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::displayContent() const
	{
		glfwSwapBuffers(window);
	}

	GLFWwindow* Window::getInnerWindow()
	{
		return window;
	}

	bool Window::isResizable() const
	{
		return resizable;
	}

	void Window::setResizable(bool value)
	{
		resizable = value;
		glfwSetWindowAttrib(window, GLFW_RESIZABLE, value);
	}

	void Window::attachEventManager(EventManager& manager)
	{
		eventManager = &manager;

		glfwSetWindowCloseCallback(window, window_close_callback);
		glfwSetKeyCallback(window, key_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);

		glfwSetWindowUserPointer(window, reinterpret_cast<void*>(this));
	}
	
	void Window::initOpenGL()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	void Window::createGLFWWindow()
	{
		switch (properties.mode)
		{
		case WindowMode::eWindowed:
			createWindowedWindow();
			break;
		case WindowMode::eFullscreen:
			createFullscreenWindow();
			break;
		case WindowMode::eWindowedFullscreen:
			createFullscreenWindowedWindow();
			break;
		}
		glfwSetWindowAttrib(window, GLFW_RESIZABLE, resizable);
		glfwMakeContextCurrent(window);
	}

	void Window::createWindowedWindow()
	{
		window = glfwCreateWindow(properties.width, properties.height, properties.title.c_str(), nullptr, nullptr);
		centerWindow();
	}

	void Window::createFullscreenWindow()
	{
		auto* const monitor = glfwGetPrimaryMonitor();
		window = glfwCreateWindow(properties.width, properties.height, properties.title.c_str(), monitor, nullptr);
	}

	void Window::createFullscreenWindowedWindow()
	{
		auto* const monitor = glfwGetPrimaryMonitor();
		const auto* videoMode = glfwGetVideoMode(monitor);

		glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);

		window = glfwCreateWindow(videoMode->width, videoMode->height, properties.title.c_str(), monitor, nullptr);
	}
	
	void Window::windowCloseCallback(bool shouldCloseWindow)
	{
		eventManager->windowCloseCallback(shouldCloseWindow);
	}

	void Window::keyCallback(int key, int scancode, int action, int mods)
	{
		eventManager->keyCallback(key, scancode, action, mods);
	}

	void Window::mouseButtonCallback(int button, int action, int mods)
	{
		eventManager->mouseButtonCallback(button, action, mods);
	}

	void Window::cursorPositionCallback(double x, double y)
	{
		eventManager->cursorPositionCallback(x, y);
	}
}
