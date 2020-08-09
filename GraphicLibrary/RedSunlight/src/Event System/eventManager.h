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
		eNone,
		eMouseButtonPressed,
		eMouseButtonReleased,
		eKeyPressed,
		eKeyReleased,
		eWindowClose
	};

	struct RED_API Event {
		Event();
		explicit Event(EventType type);

		EventType type;
	};

	class RED_API EventManager {
	public:
		EventManager(const EventManager&) = delete;
		EventManager(EventManager&&) = delete;
		
		static EventManager& getInstance();
		void startEventManager(Window* window);
		Mouse* startMouse() const;
		Keyboard* startKeyboard() const;

		bool checkForEvents(Event& event);
	private:
		EventManager();
		
		void processWindowEvents();
		void processKeyboardEvents();
		void processMouseEvents();

		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		std::queue<Event> m_eventQueue;
		Window* m_window;
		Mouse* m_mouse;
		Keyboard* m_keyboard;
	};

#pragma endregion

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

		static std::pair<int, int> getMousePosition();
		bool* getButtonsState();
	private:
		explicit Mouse(Window* window);


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
		eKeyA,
		eKeyB,
		eKeyC,
		eKeyD,
		eKeyE,
		eKeyF,
		eKeyG,
		eKeyH,
		eKeyI,
		eKeyJ,
		eKeyK,
		eKeyL,
		eKeyM,
		eKeyN,
		eKeyO,
		eKeyP,
		eKeyQ,
		eKeyR,
		eKeyS,
		eKeyT,
		eKeyU,
		eKeyV,
		eKeyW,
		eKeyX,
		eKeyY,
		eKeyZ,
		eKeyArrowRight,
		eKeyArrowLeft,
		eKeyArrowDown,
		eKeyArrowUp
	};

	class RED_API Keyboard {
	public:
		bool* getKeysState();
		KeyCode getLastPressedKey() const;
	private:
		explicit Keyboard(Window* window);

		friend void EventManager::startEventManager(Window*);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		Window* m_window;
		KeyCode m_lastPressedKey;
		static const int keysCount = 30;
		bool m_keysState[keysCount];
	};
#pragma endregion
}