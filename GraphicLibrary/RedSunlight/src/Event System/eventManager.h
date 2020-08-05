#pragma once
#include "../Window/window.h"

namespace RedSunlight {

	class Window;
	class Mouse;
	class Keyboard;

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#pragma region Event things

	enum class RED_API EventType {
		NONE,
		MOUSE_BUTTON_PRESSED,
		MOUSE_BUTTON_RELEASED,
		KEY_PRESSED,
		KEY_RELEASED,
		WINDOW_CLOSE
	};

	struct RED_API Event {
		Event();
		Event(EventType type);

		EventType type;
	};

	class RED_API EventManager {
	public:
		static EventManager& getInstance();
		
		void startEventManager(Window* window);
		Mouse* startMouse();
		Keyboard* startKeyboard();

		bool checkForEvents(Event& event);
	private:
		EventManager();
		EventManager(EventManager&) = delete;

		void processWindowEvents();
		void processKeyboardEvents();
		void processMouseEvents();

		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		std::queue<Event> eventQueue;
		Window* m_window;
		Mouse* m_mouse;
		Keyboard* m_keyboard;
	};

#pragma endregion

#pragma region Mouse
	enum class RED_API MOUSE_BUTTONS {
		LEFT,
		MIDDLE,
		RIGHT
	};

	class RED_API Mouse {
	public:
		Mouse(const Mouse&) = delete;

		std::pair<int, int> getMousePosition();
		bool* getButtonsState();
	private:
		Mouse(Window* window);


		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend void EventManager::startEventManager(Window*);
		
		Window* m_window;
		std::pair<int, int> m_position;
		bool m_buttons[3];
	};
#pragma endregion

#pragma region Keyboard

	enum class RED_API KeyCode {
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_ARROW_RIGHT,
		KEY_ARROW_LEFT,
		KEY_ARROW_DOWN,
		KEY_ARROW_UP
	};

	class RED_API Keyboard {
	public:
		bool* getKeysState();
		KeyCode getLastPressedKey();
	private:
		Keyboard(Window* window);

		friend void EventManager::startEventManager(Window*);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		Window* m_window;
		KeyCode m_lastPressedKey;
		static const int keysCount = 30;
		bool m_keysState[keysCount];
	};
#pragma endregion
}