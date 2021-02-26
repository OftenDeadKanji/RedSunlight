#pragma once
#include "keyCode.h"

namespace RedSunlight {
	struct Keyboard {
		Keyboard();
		~Keyboard() = default;
		Keyboard(const Keyboard&);
		Keyboard(Keyboard&&) noexcept;

		Keyboard& operator=(const Keyboard&);
		Keyboard& operator=(Keyboard&&) noexcept;

		bool keyStates[getKeyboardKeysCount()]{};
	};
}
