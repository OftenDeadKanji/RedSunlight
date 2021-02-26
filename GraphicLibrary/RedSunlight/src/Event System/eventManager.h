#pragma once
#include "Event/event.h"
#include "Keyboard/keyboard.h"
#include "Mouse/mouse.h"

namespace RedSunlight {

	class EventManager {
	public:
		EventManager() = default;
		~EventManager() = default;
		EventManager(const EventManager&);
		EventManager(EventManager&&) noexcept;

		EventManager& operator=(const EventManager&);
		EventManager& operator=(EventManager&&) noexcept;

		static void checkForEvents();
		Event popEvent();
		bool isEventQueueEmpty() const;
		void clearEventQueue();

		void registerKeyboard(Keyboard&);
		void registerMouse(Mouse&);

		void windowCloseCallback(bool shouldCloseWindow);

		void keyCallback(int key, int scancode, int action, int mods);

		void mouseButtonCallback(int button, int action, int mods);
		void cursorPositionCallback(double x, double y);

	private:
		std::list<Event> eventQueue;
		Keyboard* keyboard = nullptr;
		Mouse* mouse = nullptr;
	};




}
