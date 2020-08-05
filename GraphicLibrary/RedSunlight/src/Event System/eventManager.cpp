#include "pch.h"
#include "eventManager.h"



namespace RedSunlight {
	Event::Event() : type(EventType::NONE)
	{}
	Event::Event(EventType type) : type(type)
	{}

	EventManager::EventManager() : m_window(nullptr), m_mouse(nullptr)
	{}

	EventManager& EventManager::getInstance()
	{
		static EventManager manager;
		return manager;
	}

	void EventManager::startEventManager(Window* window)
	{
		m_window = window;
		m_mouse = new Mouse(window);
		m_keyboard = new Keyboard(window);
	}

	Mouse* EventManager::startMouse()
	{
		glfwSetMouseButtonCallback(m_window->m_window, mouse_button_callback);

		return m_mouse;
	}

	Keyboard* EventManager::startKeyboard()
	{
		glfwSetKeyCallback(m_window->m_window, key_callback);


		return m_keyboard;
	}

	bool EventManager::checkForEvents(Event& event)
	{
		glfwPollEvents();

		processWindowEvents();
		processKeyboardEvents();
		processMouseEvents();

		if (eventQueue.empty())
			return false;

		event = eventQueue.front();
		eventQueue.pop();

		return true;
	}

	void EventManager::processWindowEvents()
	{
		if (glfwWindowShouldClose(m_window->m_window))
			eventQueue.push(Event(EventType::WINDOW_CLOSE));
	}

	void EventManager::processKeyboardEvents()
	{}

	void EventManager::processMouseEvents()
	{}


	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Mouse* mouse = EventManager::getInstance().startMouse();

		if (action == GLFW_PRESS) {
			EventManager::getInstance().eventQueue.push(Event(EventType::MOUSE_BUTTON_PRESSED));

			if (button == GLFW_MOUSE_BUTTON_LEFT)
				mouse->m_buttons[0] = true;
			else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
				mouse->m_buttons[1] = true;
			else if (button == GLFW_MOUSE_BUTTON_RIGHT)
				mouse->m_buttons[2] = true;
		}
		else if (action == GLFW_RELEASE) {
			EventManager::getInstance().eventQueue.push(Event(EventType::MOUSE_BUTTON_RELEASED));

			if (button == GLFW_MOUSE_BUTTON_LEFT)
				mouse->m_buttons[0] = false;
			else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
				mouse->m_buttons[1] = false;
			else if (button == GLFW_MOUSE_BUTTON_RIGHT)
				mouse->m_buttons[2] = false;
		}
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Keyboard* keyboard = EventManager::getInstance().startKeyboard();

		if (action == GLFW_PRESS) {
			EventManager::getInstance().eventQueue.push(Event(EventType::KEY_PRESSED));
			if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z) {
				KeyCode pressedKey = (KeyCode)(key - GLFW_KEY_A);
				keyboard->m_lastPressedKey = pressedKey;
				keyboard->m_keysState[(int)pressedKey] = true;
			}
			else if (key >= GLFW_KEY_RIGHT && key <= GLFW_KEY_UP) {
				KeyCode pressedKey = (KeyCode)(key - GLFW_KEY_RIGHT + (int)KeyCode::KEY_ARROW_RIGHT);
				keyboard->m_lastPressedKey = pressedKey;
				keyboard->m_keysState[(int)pressedKey] = true;
			}
		}
		else if (action == GLFW_RELEASE) {
			EventManager::getInstance().eventQueue.push(Event(EventType::KEY_RELEASED));
			if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
				keyboard->m_keysState[key - GLFW_KEY_A] = false;
			else if (key >= GLFW_KEY_RIGHT && key <= GLFW_KEY_UP)
				keyboard->m_keysState[key - GLFW_KEY_RIGHT + (int)KeyCode::KEY_ARROW_RIGHT] = false;

		}

	}

#pragma region Mouse

	Mouse::Mouse(Window* window) : m_window(window), m_position(std::make_pair(0, 0)), m_buttons{ false, false, false }
	{
		glfwSetCursorPosCallback(m_window->m_window, cursor_position_callback);
	}

	/*Mouse::Mouse(const Mouse& mouse) : m_window(mouse.m_window), m_buttons{ mouse.m_buttons }, m_position(mouse.m_position)
	{}*/

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		EventManager::getInstance().startMouse()->m_position = std::make_pair(xpos, ypos);
	}

	std::pair<int, int> Mouse::getMousePosition()
	{
		return std::pair<int, int>();
	}

	bool* Mouse::getButtonsState()
	{
		return m_buttons;
	}

#pragma endregion

#pragma region Keyboard

	bool* Keyboard::getKeysState()
	{
		return m_keysState;
	}

	KeyCode Keyboard::getLastPressedKey()
	{
		return m_lastPressedKey;
	}

	Keyboard::Keyboard(Window* window) : m_window(window)
	{
		for (int i = 0; i < keysCount; i++)
			m_keysState[i] = false;
	}

#pragma endregion
}