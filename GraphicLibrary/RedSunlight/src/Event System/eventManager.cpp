#include "pch.h"
#include "eventManager.h"

namespace RedSunlight {

#pragma region Event things

	EventManager::EventManager() : m_window(nullptr), m_mouse(nullptr), m_keyboard(nullptr)
	{}

	EventManager& EventManager::getInstance()
	{
		static EventManager manager;
		return manager;
	}

	void EventManager::startEventManager(Window* window)
	{
		m_window = window;
		
		m_mouse = &Mouse::getInstance();
		m_mouse->attachWindow(m_window);
		
		m_keyboard = &Keyboard::getInstance();
		m_keyboard->attachWindow(m_window);
	}

	Mouse* EventManager::startMouse() const
	{
		return m_mouse;
	}

	Keyboard* EventManager::startKeyboard() const
	{
		return m_keyboard;
	}

	std::deque<Event>& EventManager::checkForEvents()
	{
		m_eventQueue.clear();
		glfwPollEvents();

		processWindowEvents();
		processKeyboardEvents();
		processMouseEvents();

		return m_eventQueue;
	}

	void EventManager::processWindowEvents()
	{
		if (glfwWindowShouldClose(m_window->m_window))
			m_eventQueue.emplace_back(Event(EventType::eWindowClose));
	}

	void EventManager::processKeyboardEvents()
	{
		auto keyboardEventQueue = m_keyboard->getEventQueue();
		
		while (!keyboardEventQueue.empty()) {
			m_eventQueue.push_back(keyboardEventQueue.front());
			keyboardEventQueue.pop_front();
		}
		
		m_keyboard->clearEventQueue();
	}

	void EventManager::processMouseEvents()
	{
		auto mouseEventQueue = m_mouse->getMouseEventsQueue();
		
		while (!mouseEventQueue.empty()) {
			m_eventQueue.push_back(mouseEventQueue.front());
			mouseEventQueue.pop_front();
		}
		
		m_mouse->clearEventsQueue();
	}

#pragma endregion
}