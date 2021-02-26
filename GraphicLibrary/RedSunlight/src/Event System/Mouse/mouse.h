#pragma once
#include "mouseButtonsCodes.h"

namespace RedSunlight {
	struct Mouse {
		Mouse();
		~Mouse() = default;
		Mouse(const Mouse&);
		Mouse(Mouse&&) noexcept;

		Mouse& operator=(const Mouse&);
		Mouse& operator=(Mouse&&) noexcept;

		bool buttonStates[getMouseButtonsCount()]{};
		int x = 0, y = 0;
	};
}