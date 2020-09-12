#pragma once
#include "../Window/window.h"
#include "event.h"

namespace RedSunlight {
	
	class Window;
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#pragma region Keyboard

	enum class KeyCode {
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
		eKeyArrowUp,
		eKeyESC
	};

	class Keyboard {
	public:
		static Keyboard& getInstance();
		
		bool* getKeysState();
		[[nodiscard]] KeyCode getLastPressedKey() const;

		std::deque<Event>& getEventQueue();
		void clearEventQueue();

		void attachWindow(Window* window);
	private:
		explicit Keyboard();

		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		Window* m_window;
		KeyCode m_lastPressedKey;
		static const int keysCount = 31;
		bool m_keysState[keysCount];
		std::deque<Event> m_eventQueue;
	};
#pragma endregion
}