//
// Created by Kanjiklub on 12 wrz 2020.
//

#ifndef GRAPHICSENGINE_WINDOWPROPERTIES_H
#define GRAPHICSENGINE_WINDOWPROPERTIES_H

#include "windowMode.h"

namespace RedLightBulb {
    struct WindowProperties {
        WindowProperties(int width, int height, WindowMode mode, const std::string& title);
        WindowProperties(const WindowProperties&);
        WindowProperties(WindowProperties&&) noexcept ;

	    WindowProperties& operator=(const WindowProperties&);
	    WindowProperties& operator=(WindowProperties&&) noexcept ;

        int width, height;
        WindowMode mode;
        std::string title;
    };
}
#endif //GRAPHICSENGINE_WINDOWPROPERTIES_H
