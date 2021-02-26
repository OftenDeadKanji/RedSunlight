#pragma once
#include "windowMode.h"

namespace RedSunlight
{
    struct WindowProperties {
        WindowProperties(int width, int height, WindowMode mode, std::string title);
        WindowProperties(const WindowProperties&);
        WindowProperties(WindowProperties&&) noexcept;
        ~WindowProperties() = default;
    	
        WindowProperties& operator=(const WindowProperties&);
        WindowProperties& operator=(WindowProperties&&) noexcept;

        int width, height;
        WindowMode mode;
        std::string title;
    };
}
