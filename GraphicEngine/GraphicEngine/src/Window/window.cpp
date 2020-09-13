//
// Created by Kanjiklub on 12 wrz 2020.
//

#include "window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace RedLightBulb {
	void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
		glViewport(0, 0, width, height);
	}

	struct Window::Impl {
		explicit Impl(const RedLightBulb::WindowProperties &properties);

		~Impl();

		static void initOpenGL();

		void createWindow();
		void createWindowedWindow();
		void createFullscreenWindow();
		void createFullscreenWindowedWindow();

		WindowProperties m_properties;
		GLFWwindow *m_window = nullptr;
	};

	Window::Impl::Impl(const WindowProperties &properties)
	: m_properties(properties) {
		initOpenGL();
		createWindow();

		glfwMakeContextCurrent(m_window);

		if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
			glViewport(0, 0, properties.width, properties.height);

			glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
		}
	}

	Window::Impl::~Impl() {
		glfwDestroyWindow(m_window);
	}

	void Window::Impl::initOpenGL() {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	void Window::Impl::createWindow() {
		switch (m_properties.mode) {
			default:
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
	}

	void Window::Impl::createWindowedWindow() {
		m_window = glfwCreateWindow(m_properties.width, m_properties.height, m_properties.title.c_str(), nullptr,nullptr);
	}

	void Window::Impl::createFullscreenWindow() {
		auto *const monitor = glfwGetPrimaryMonitor();
		m_window = glfwCreateWindow(m_properties.width, m_properties.height, m_properties.title.c_str(), monitor,nullptr);
	}

	void Window::Impl::createFullscreenWindowedWindow() {
		auto *const monitor = glfwGetPrimaryMonitor();
		const auto *videoMode = glfwGetVideoMode(monitor);

		glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);

		m_window = glfwCreateWindow(videoMode->width, videoMode->height, m_properties.title.c_str(), monitor, nullptr);
	}

	Window::Window(const RedLightBulb::WindowProperties &properties)
			: pImpl(new Impl(properties)) {}

	void Window::clearToColor(int r, int g, int b) {
		glClearColor(static_cast<float>(r) / 255.f, static_cast<float>(g) / 255.f, static_cast<float>(b) / 255.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::displayContent() {
		glfwSwapBuffers(pImpl->m_window);
	}

}

