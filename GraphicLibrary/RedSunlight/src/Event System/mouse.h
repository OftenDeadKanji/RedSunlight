#pragma once
#include "../Window/window.h"
#include "event.h"

namespace RedSunlight {

	class Window;
	
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	
#pragma region Mouse
	enum class RED_API MouseButtons {
		eLeft,
		eMiddle,
		eRight
	};
	
	class RED_API Mouse {
	public:
		Mouse(const Mouse&) = delete;
		Mouse(Mouse&&) = delete;

		static Mouse& getInstance();
		void attachWindow(Window* window);
		
		std::pair<int, int>& getMousePosition();
		bool* getButtonsState();
		
		std::deque<Event>& getMouseEventsQueue();
		void clearEventsQueue();
	private:
		Mouse();
		
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

		Window* m_window;
		std::pair<int, int> m_position;
		bool m_buttons[3];
		std::deque<Event> m_mouseEventsQueue;
	};
#pragma endregion

}