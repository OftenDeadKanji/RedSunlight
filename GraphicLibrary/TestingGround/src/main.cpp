#include <RedSunlight.h>
#include <iostream>

int main()
{
	if (RedSunlight::init() == RED_OK) {
		RedSunlight::Window okno(1600, 900, "Testujemy", RedSunlight::WindowMode::WINDOWED);

		std::cin.get();
		RedSunlight::terminate();
		return 0;
	}
	else {
		return -1;
	}
}