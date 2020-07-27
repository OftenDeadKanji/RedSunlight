#include "pch.h"
#include "RedSunlight.h"

int RED_API RedSunlight::init()
{
	if (OS == WIN64) {
		if (glfwInit() == GLFW_TRUE)
			return RED_OK;
		else
			return RED_FAIL;
	}
	else
		return RED_FAIL;
}

void RED_API RedSunlight::terminate()
{
	glfwTerminate();
}


