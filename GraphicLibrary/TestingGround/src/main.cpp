#include <RedSunlight.h>
#include <iostream>
#include <random>

#define ever (;;) 

int main()
{
	if (RedSunlight::init() == RED_OK) {
		RedSunlight::Window okno(1600, 900, "Testujemy", RedSunlight::WindowMode::WINDOWED);

		for ever{
			okno.clearToColor(rand() % 255, rand() % 255, rand() % 255);



			okno.drawWindowContent();
		}

		RedSunlight::terminate();
		return 0;
	}
	else {
		return -1;
	}
}