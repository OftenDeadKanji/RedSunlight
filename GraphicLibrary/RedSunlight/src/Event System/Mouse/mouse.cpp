#include "pch.h"
#include "mouse.h"

namespace RedSunlight
{
	Mouse::Mouse()
	{
		for (bool& state : buttonStates)
			state = false;
	}

	Mouse::Mouse(const Mouse& other)
		: x(other.x), y(other.y)
	{
		std::copy(std::begin(other.buttonStates), std::end(other.buttonStates), std::begin(buttonStates));
	}

	Mouse::Mouse(Mouse&& other) noexcept
		: x(other.x), y(other.y)
	{
		std::move(std::begin(other.buttonStates), std::end(other.buttonStates), std::begin(buttonStates));
	}

	Mouse& Mouse::operator=(const Mouse& other)
	{
		if (&other == this)
			return *this;

		x = other.x;
		y = other.y;
		std::copy(std::begin(other.buttonStates), std::end(other.buttonStates), std::begin(buttonStates));

		return *this;
	}

	Mouse& Mouse::operator=(Mouse&& other) noexcept
	{
		x = other.x;
		y = other.y;
		std::move(std::begin(other.buttonStates), std::end(other.buttonStates), std::begin(buttonStates));

		return *this;
	}
}
