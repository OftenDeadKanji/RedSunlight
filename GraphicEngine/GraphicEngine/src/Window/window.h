//
// Created by Kanjiklub on 12 wrz 2020.
//

#ifndef GRAPHICSENGINE_WINDOW_H
#define GRAPHICSENGINE_WINDOW_H
#include "windowProperties.h"

namespace RedLightBulb {

    class Window {
    public:
        explicit Window(const WindowProperties& properties);
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        static void clearToColor(int r, int g, int b);
        void displayContent();

    private:
    	struct Impl;
		std::unique_ptr<Impl> pImpl;
    };

}

#endif //GRAPHICSENGINE_WINDOW_H
