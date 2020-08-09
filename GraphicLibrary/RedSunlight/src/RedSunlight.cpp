#include "pch.h"
#include "RedSunlight.h"

int RED_API RedSunlight::init()
{
	if constexpr (OS == WIN64) {
		if (glfwInit() == GLFW_TRUE)
			return RED_OK;
		return RED_FAIL;
	}
	else
		return RED_FAIL;
}

RED_API void RedSunlight::terminate()
{
	glfwTerminate();
}


