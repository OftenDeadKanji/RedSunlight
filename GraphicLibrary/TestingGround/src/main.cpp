﻿#include <iostream>
#include <RedSunlight.h>

int main()
{
	if (RedSunlight::init() == RED_FAIL)
		return -1;

	//utworzenie okna
	RedSunlight::Window okno(RedSunlight::WindowProperties(1600, 900, "Testujemy", RedSunlight::WindowMode::eWindowed));

	//testowanie prymitywa - tr�jk�t
	int trLewy[2] = { 0,0 };
	int trGorny[2] = { 200,400 };
	int trPrawy[2] = { 300,200 };
	int trKolor[4] = { 128, 0, 255, 255 };
	RedSunlight::Triangle2D trojkat(trLewy, trGorny, trPrawy, trKolor);

	int prLewy[2] = { 200, 500 };
	int prPrawy[2] = { 400, 1000 };
	int prKolor[4] = { 255, 127, 39, 255 };
	RedSunlight::Rectangle2D prostokat(prLewy, prPrawy, prKolor);

	RedSunlight::Cube kostka(200, 200, 0, 200, 0, 255, 140, 255);

	RedSunlight::Font czcionka("res/fonts/Segan.ttf", 50);
	RedSunlight::Text tekst(100, 800, "Testowe", czcionka);

	int wspTekstury[4] = { 0, 0, 251, 232 };
	RedSunlight::Sprite myLover(500, 600, 125, 116, "res/images/kenobi.png", wspTekstury);

	RedSunlight::EventManager::getInstance().startEventManager(&okno);
	auto* mysz = RedSunlight::EventManager::getInstance().startMouse();
	auto* klawiatura = RedSunlight::EventManager::getInstance().startKeyboard();

	auto warunek = true;
	while (warunek)
	{
		auto queue = RedSunlight::EventManager::getInstance().checkForEvents();

		while (!queue.empty()) {
			auto event = queue.front();
			queue.pop_front();
			if (event.type == RedSunlight::EventType::eWindowClose) {
				warunek = false;
			}
			else if (event.type == RedSunlight::EventType::eKeyPressed) {

			}
			else if (event.type == RedSunlight::EventType::eMouseButtonPressed) {
				auto* mouseButtonsState = mysz->getButtonsState();
			}

		}

		okno.clearToColor(157, 217, 234);

		okno.drawElement(&trojkat);
		okno.drawElement(&tekst);
		okno.drawElement(&myLover);
		okno.drawElement(&kostka);

		okno.displayContent();
	}

	//kończenie
	RedSunlight::terminate();
	return 0;
}