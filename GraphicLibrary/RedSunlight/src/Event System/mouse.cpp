#include "pch.h"
#include "mouse.h"

namespace RedSunlight
{
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Mouse::getInstance().m_position = std::make_pair(xpos, ypos);
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS) {
			Mouse::getInstance().m_mouseEventsQueue.emplace_back(EventType::eMouseButtonPressed);

			if (button == GLFW_MOUSE_BUTTON_LEFT)
				Mouse::getInstance().m_buttons[0] = true;
			else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
				Mouse::getInstance().m_buttons[1] = true;
			else if (button == GLFW_MOUSE_BUTTON_RIGHT)
				Mouse::getInstance().m_buttons[2] = true;
		}
		else if (action == GLFW_RELEASE) {
			Mouse::getInstance().m_mouseEventsQueue.emplace_back(Event(EventType::eMouseButtonReleased));

			if (button == GLFW_MOUSE_BUTTON_LEFT)
				Mouse::getInstance().m_buttons[0] = false;
			else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
				Mouse::getInstance().m_buttons[1] = false;
			else if (button == GLFW_MOUSE_BUTTON_RIGHT)
				Mouse::getInstance().m_buttons[2] = false;
		}
	}

#pragma region Mouse

	Mouse::Mouse() : m_window(nullptr), m_position(std::make_pair(0, 0)), m_buttons{ false, false, false }
	{}

	Mouse& Mouse::getInstance()
	{
		static Mouse mouse;
		return mouse;
	}

	void Mouse::attachWindow(Window* window)
	{
		m_window = window;
		glfwSetCursorPosCallback(m_window->m_window, cursor_position_callback);
		glfwSetMouseButtonCallback(m_window->m_window, mouse_button_callback);
	}

	std::pair<int, int>& Mouse::getMousePosition()
	{
		return m_position;
	}

	bool* Mouse::getButtonsState()
	{
		return m_buttons;
	}

	std::deque<Event>& Mouse::getMouseEventsQueue()
	{
		return m_mouseEventsQueue;
	}

	void Mouse::clearEventsQueue()
	{
		m_mouseEventsQueue.clear();
	}

#pragma endregion
}