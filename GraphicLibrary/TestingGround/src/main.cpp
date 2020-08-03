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
	RedSunlight::Traingle2D trojkat(glm::vec2(0, 0), glm::vec2(200, 400), glm::vec2(300,200), glm::vec4(128, 0, 255, 255));
	RedSunlight::Rectangle2D prostokat(glm::vec2(200, 500), glm::vec2(400, 1000), glm::vec4(255, 127, 39, 255));
	
	RedSunlight::Font czcionka("res/fonts/Segan.ttf", 50);
	RedSunlight::Text tekst(100, 800, &czcionka, "Testowe", glm::vec3(0, 0, 0));

	for ever
	{
		okno.clearToColor(0, 162, 232);

		okno.drawElement(&trojkat);
		okno.drawElement(&prostokat);
		okno.drawElement(&tekst);

		okno.displayContent();
	}

	//koñczenie
	RedSunlight::terminate();
	return 0;
}