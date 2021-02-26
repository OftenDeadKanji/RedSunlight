#pragma once
#include "windowProperties.h"
#include "../Event System/eventManager.h"

namespace RedSunlight {
	class Window {
	public:
		explicit Window(WindowProperties properties);
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		~Window();

		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

		static void clearToColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
		static void clearToColorf(float r, float g, float b, float a = 1.0f);
		void displayContent() const;

		GLFWwindow* getInnerWindow();
		[[nodiscard]] bool isResizable() const;
		
		void setResizable(bool);

		void attachEventManager(EventManager& manager);

		void windowCloseCallback(bool shouldCloseWindow);
		void keyCallback(int key, int scancode, int action, int mods);
		void mouseButtonCallback(int button, int action, int mods);
		void cursorPositionCallback(double x, double y);
		
	private:
		void initOpenGL();

		void createGLFWWindow();
		void createWindowedWindow();
		void createFullscreenWindow();
		void createFullscreenWindowedWindow();
		
		void centerWindow();

		WindowProperties properties;
		GLFWwindow* window = nullptr;
		EventManager* eventManager = nullptr;

		bool resizable = false;
	};
}