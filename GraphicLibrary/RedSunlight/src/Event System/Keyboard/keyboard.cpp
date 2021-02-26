#include "pch.h"
#include "keyboard.h"

namespace RedSunlight
{
	Keyboard::Keyboard()
	{
		for (bool& keyState : keyStates)
			keyState = false;
	}

	Keyboard::Keyboard(const Keyboard& other)
	{
		std::copy(std::begin(other.keyStates), std::end(other.keyStates), std::begin(keyStates));
	}

	Keyboard::Keyboard(Keyboard&& other) noexcept
	{
		std::move(std::begin(other.keyStates), std::end(other.keyStates), std::begin(keyStates));
	}

	Keyboard& Keyboard::operator=(const Keyboard& other)
	{
		if (&other == this)
			return *this;

		std::copy(std::begin(other.keyStates), std::end(other.keyStates), std::begin(keyStates));
		return *this;
	}

	Keyboard& Keyboard::operator=(Keyboard&& other) noexcept
	{
		if (&other == this)
			return *this;

		std::move(std::begin(other.keyStates), std::end(other.keyStates), std::begin(keyStates));
		return *this;
	}
#pragma endregion
}
