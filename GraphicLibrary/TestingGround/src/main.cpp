#include <RedSunlight.h>
#include <iostream>
#include <random>

#define ever (;;) 

int main()
{
	if (RedSunlight::init() == RED_FAIL)
		return -1;

	//utworzenie okna
	RedSunlight::Window okno(1600, 900, "Testujemy", RedSunlight::WindowMode::WINDOWED);

	//testowanie prymitywa - trójk¹t
	RedSunlight::Traingle2D trojkat(glm::vec2(-0.9, 0.3), glm::vec2(-0.8, 0.5), glm::vec2(-0.7, 0.3), glm::vec4(128, 0, 255, 255));
	RedSunlight::Rectangle2D prostokat(glm::vec2(-0.6, 0.5), glm::vec2(-0.3, 0.3), glm::vec4(255, 127, 39, 255));

	for ever
	{
		okno.clearToColor(0, 162, 232);

		trojkat.draw();
		prostokat.draw();

		okno.drawWindowContent();
	}

	//koñczenie
	RedSunlight::terminate();
	return 0;
}