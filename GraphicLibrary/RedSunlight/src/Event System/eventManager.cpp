#include "pch.h"
#include "eventManager.h"

namespace RedSunlight {

	KeyCode convertToKeyCode(int glfwKey) {
		switch (glfwKey) {
		default:
			return KeyCode::eKeyNone;
		case GLFW_KEY_A:
			return KeyCode::eKeyA;
		case GLFW_KEY_B:
			return KeyCode::eKeyB;
		case GLFW_KEY_C:
			return KeyCode::eKeyC;
		case GLFW_KEY_D:
			return KeyCode::eKeyD;
		case GLFW_KEY_E:
			return KeyCode::eKeyE;
		case GLFW_KEY_F:
			return KeyCode::eKeyF;
		case GLFW_KEY_G:
			return KeyCode::eKeyG;
		case GLFW_KEY_H:
			return KeyCode::eKeyH;
		case GLFW_KEY_I:
			return KeyCode::eKeyI;
		case GLFW_KEY_J:
			return KeyCode::eKeyJ;
		case GLFW_KEY_K:
			return KeyCode::eKeyK;
		case GLFW_KEY_L:
			return KeyCode::eKeyL;
		case GLFW_KEY_M:
			return KeyCode::eKeyM;
		case GLFW_KEY_N:
			return KeyCode::eKeyN;
		case GLFW_KEY_O:
			return KeyCode::eKeyO;
		case GLFW_KEY_Q:
			return KeyCode::eKeyQ;
		case GLFW_KEY_P:
			return KeyCode::eKeyP;
		case GLFW_KEY_R:
			return KeyCode::eKeyR;
		case GLFW_KEY_S:
			return KeyCode::eKeyS;
		case GLFW_KEY_T:
			return KeyCode::eKeyT;
		case GLFW_KEY_U:
			return KeyCode::eKeyU;
		case GLFW_KEY_W:
			return KeyCode::eKeyW;
		case GLFW_KEY_V:
			return KeyCode::eKeyV;
		case GLFW_KEY_X:
			return KeyCode::eKeyX;
		case GLFW_KEY_Y:
			return KeyCode::eKeyY;
		case GLFW_KEY_Z:
			return KeyCode::eKeyZ;
		case GLFW_KEY_1:
			return KeyCode::eKey1;
		case GLFW_KEY_2:
			return KeyCode::eKey2;
		case GLFW_KEY_3:
			return KeyCode::eKey3;
		case GLFW_KEY_4:
			return KeyCode::eKey4;
		case GLFW_KEY_5:
			return KeyCode::eKey5;
		case GLFW_KEY_6:
			return KeyCode::eKey6;
		case GLFW_KEY_7:
			return KeyCode::eKey7;
		case GLFW_KEY_8:
			return KeyCode::eKey8;
		case GLFW_KEY_9:
			return KeyCode::eKey9;
		case GLFW_KEY_0:
			return KeyCode::eKey0;
		case GLFW_KEY_F1:
			return KeyCode::eKeyF1;
		case GLFW_KEY_F2:
			return KeyCode::eKeyF2;
		case GLFW_KEY_F3:
			return KeyCode::eKeyF3;
		case GLFW_KEY_F4:
			return KeyCode::eKeyF4;
		case GLFW_KEY_F5:
			return KeyCode::eKeyF5;
		case GLFW_KEY_F6:
			return KeyCode::eKeyF6;
		case GLFW_KEY_F7:
			return KeyCode::eKeyF7;
		case GLFW_KEY_F8:
			return KeyCode::eKeyF8;
		case GLFW_KEY_F9:
			return KeyCode::eKeyF9;
		case GLFW_KEY_F10:
			return KeyCode::eKeyF10;
		case GLFW_KEY_F11:
			return KeyCode::eKeyF11;
		case GLFW_KEY_F12:
			return KeyCode::eKeyF12;
		case GLFW_KEY_UP:
			return KeyCode::eKeyArrowUp;
		case GLFW_KEY_LEFT:
			return KeyCode::eKeyArrowLeft;
		case GLFW_KEY_RIGHT:
			return KeyCode::eKeyArrowRight;
		case GLFW_KEY_DOWN:
			return KeyCode::eKeyArrowDown;
		case GLFW_KEY_SPACE:
			return KeyCode::eKeySpace;
		case GLFW_KEY_COMMA:
			return KeyCode::eKeyComma;
		case GLFW_KEY_PERIOD:
			return KeyCode::eKeyDot;
		case GLFW_KEY_SLASH:
			return KeyCode::eKeySlash;
		case GLFW_KEY_SEMICOLON:
			return KeyCode::eKeySemicolon;
		case GLFW_KEY_APOSTROPHE:
			return KeyCode::eKeyApostrophe;
		case GLFW_KEY_BACKSLASH:
			return KeyCode::eKeyBackslash;
		case GLFW_KEY_LEFT_BRACKET:
			return KeyCode::eLeftBracket;
		case GLFW_KEY_RIGHT_BRACKET:
			return KeyCode::eRightBracket;
		case GLFW_KEY_GRAVE_ACCENT:
			return KeyCode::eKeyGraveAccent;
		case GLFW_KEY_MINUS:
			return KeyCode::eKeyMinus;
		case GLFW_KEY_EQUAL:
			return KeyCode::eKeyEqual;
		case GLFW_KEY_BACKSPACE:
			return KeyCode::eKeyBackspace;
		case GLFW_KEY_ESCAPE:
			return KeyCode::eKeyEscape;
		}
	}
	
	EventManager::EventManager(const EventManager& other) {
		keyboard = other.keyboard;
		mouse = other.mouse;
		std::copy(other.eventQueue.begin(), other.eventQueue.end(), eventQueue.begin());
	}

	EventManager::EventManager(EventManager&& other) noexcept {
		keyboard = other.keyboard;
		mouse = other.mouse;
		std::move(other.eventQueue.begin(), other.eventQueue.end(), eventQueue.begin());
	}

	EventManager& EventManager::operator=(const EventManager& other) {
		if (&other == this)
			return *this;

		keyboard = other.keyboard;
		mouse = other.mouse;
		std::copy(other.eventQueue.begin(), other.eventQueue.end(), eventQueue.begin());

		return *this;
	}

	EventManager& EventManager::operator=(EventManager&& other) noexcept {

		keyboard = other.keyboard;
		mouse = other.mouse;
		std::move(other.eventQueue.begin(), other.eventQueue.end(), eventQueue.begin());

		return *this;
	}
	
	void EventManager::registerKeyboard(Keyboard& keyboard) {
		this->keyboard = &keyboard;
	}

	void EventManager::registerMouse(Mouse& mouse) {
		this->mouse = &mouse;
	}

	void EventManager::checkForEvents() {
		glfwPollEvents();
	}

	Event EventManager::popEvent() {
		const Event tmp = eventQueue.front();
		eventQueue.pop_front();
		return tmp;
	}

	bool EventManager::isEventQueueEmpty() const
	{
		return eventQueue.empty();
	}

	void EventManager::clearEventQueue() {
		while (!eventQueue.empty())
			eventQueue.clear();
	}

	void EventManager::keyCallback(int key, int scancode, int action, int mods) {
		if (keyboard) {
			if (action == GLFW_PRESS) {
				eventQueue.emplace_back(EventType::eKeyPressed);

				KeyCode redKey = convertToKeyCode(key);
				keyboard->keyStates[static_cast<int>(redKey)] = true;
			}
			else if (action == GLFW_RELEASE) {
				eventQueue.emplace_back(EventType::eKeyReleased);

				KeyCode redKey = convertToKeyCode(key);
				keyboard->keyStates[static_cast<int>(redKey)] = false;
			}
		}
	}

	void EventManager::windowCloseCallback(bool shouldCloseWindow) {
		if (shouldCloseWindow)
			eventQueue.emplace_back(Event(EventType::eWindowClosed));
	}

	void EventManager::mouseButtonCallback(int button, int action, int mods) {
		if (mouse) {
			if (action == GLFW_PRESS) {
				eventQueue.emplace_back(Event(EventType::eMouseButtonPressed));
				switch (button) {
				default:
					break;
				case GLFW_MOUSE_BUTTON_LEFT:
					mouse->buttonStates[0] = true;
					break;
				case GLFW_MOUSE_BUTTON_MIDDLE:
					mouse->buttonStates[1] = true;
					break;
				case GLFW_MOUSE_BUTTON_RIGHT:
					mouse->buttonStates[2] = true;
					break;
				}
			}
			else if (action == GLFW_RELEASE) {
				eventQueue.emplace_back(Event(EventType::eMouseButtonReleased));
				switch (button) {
				default:
					break;
				case GLFW_MOUSE_BUTTON_LEFT:
					mouse->buttonStates[0] = false;
					break;
				case GLFW_MOUSE_BUTTON_MIDDLE:
					mouse->buttonStates[1] = false;
					break;
				case GLFW_MOUSE_BUTTON_RIGHT:
					mouse->buttonStates[2] = false;
					break;
				}
			}
		}
	}

	void EventManager::cursorPositionCallback(double x, double y) {
		if (mouse) {
			mouse->x = static_cast<int>(x);
			mouse->y = static_cast<int>(y);
		}
	}
}