#pragma once
#include "../Window/window.h"
#include "event.h"
#include "mouse.h"
#include "keyboard.h"

namespace RedSunlight {

	class Window;
	class Mouse;
	class Keyboard;
	
#pragma region Event things

	class RED_API EventManager {
	public:
		EventManager(const EventManager&) = delete;
		EventManager(EventManager&&) = delete;
		
		static EventManager& getInstance();
		void startEventManager(Window* window);
		[[nodiscard]] Mouse* startMouse() const;
		[[nodiscard]] Keyboard* startKeyboard() const;

		std::deque<Event>& checkForEvents();
	private:
		EventManager();
		
		void processWindowEvents();
		void processKeyboardEvents();
		void processMouseEvents();

		std::deque<Event> m_eventQueue;
		Window* m_window;
		Mouse* m_mouse;
		Keyboard* m_keyboard;
	};

#pragma endregion




}