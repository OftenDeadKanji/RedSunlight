#include "RedLightBulb.h"
#include "GLFW/glfw3.h"

namespace RedLightBulb {

    int init() {
        return glfwInit();
    }

    void terminate() {
        glfwTerminate();
    }
}