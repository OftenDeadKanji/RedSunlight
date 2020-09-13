//
// Created by Kanjiklub on 12 wrz 2020.
//

#include "windowProperties.h"

namespace RedLightBulb {

	WindowProperties::WindowProperties(int width, int height, WindowMode mode, const std::string &title)
		: width(width), height(height), mode(mode), title(title)
		{}

	WindowProperties::WindowProperties(const WindowProperties & other)
	: width(other.width), height(other.height), mode(other.mode), title(other.title)
	{}

	WindowProperties::WindowProperties(WindowProperties && other) noexcept
	: width(other.width), height(other.height), mode(other.mode), title(std::move(other.title))
	{}

	WindowProperties &WindowProperties::operator=(const WindowProperties & other) {
		width = other.width;
		height = other.height;
		mode = other.mode;
		title = std::string(other.title);

		return *this;
	}

	WindowProperties &WindowProperties::operator=(WindowProperties && other) noexcept {
		width = other.width;
		height = other.height;
		mode = other.mode;
		title = std::move(other.title);

		return *this;
	}
}