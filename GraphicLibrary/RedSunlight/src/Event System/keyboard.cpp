#include "pch.h"
#include "keyboard.h"

namespace RedSunlight
{

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS) {
			Keyboard::getInstance().m_eventQueue.emplace_back(EventType::eKeyPressed);
			
			if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z) {
				auto pressedKey = static_cast<KeyCode>(key - GLFW_KEY_A);
				Keyboard::getInstance().m_lastPressedKey = pressedKey;
				Keyboard::getInstance().m_keysState[static_cast<int>(pressedKey)] = true;
			}
			else if (key >= GLFW_KEY_RIGHT && key <= GLFW_KEY_UP) {
				auto pressedKey = static_cast<KeyCode>(key - GLFW_KEY_RIGHT + static_cast<int>(KeyCode::eKeyArrowRight));
				Keyboard::getInstance().m_lastPressedKey = pressedKey;
				Keyboard::getInstance().m_keysState[static_cast<int>(pressedKey)] = true;
			}
		}
		else if (action == GLFW_RELEASE) {
			Keyboard::getInstance().m_eventQueue.emplace_back(Event(EventType::eKeyReleased));
			
			if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
				Keyboard::getInstance().m_keysState[key - GLFW_KEY_A] = false;
			else if (key >= GLFW_KEY_RIGHT && key <= GLFW_KEY_UP)
				Keyboard::getInstance().m_keysState[key - GLFW_KEY_RIGHT + static_cast<int>(KeyCode::eKeyArrowRight)] = false;

		}

	}

	Keyboard& Keyboard::getInstance()
	{
		static Keyboard keyboard;
		return keyboard;
	}

#pragma region Keyboard

	Keyboard::Keyboard() : m_window(nullptr)
	{
		for (auto& i : m_keysState)
			i = false;
	}

	bool* Keyboard::getKeysState()
	{
		return m_keysState;
	}

	KeyCode Keyboard::getLastPressedKey() const
	{
		return m_lastPressedKey;
	}

	std::deque<Event>& Keyboard::getEventQueue()
	{
		return m_eventQueue;
	}

	void Keyboard::clearEventQueue()
	{
		m_eventQueue.clear();
	}

	void Keyboard::attachWindow(Window* window)
	{
		m_window = window;
		glfwSetKeyCallback(m_window->m_window, key_callback);
	}


#pragma endregion
}