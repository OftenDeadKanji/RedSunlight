#include <iostream>
#include <RedSunlight.h>

int main()
{
	if (RedSunlight::init() == RED_FAIL)
		return -1;

	//utworzenie okna
	RedSunlight::Window okno(RedSunlight::WindowProperties(1600, 900, "Testujemy", RedSunlight::WindowMode::eWindowed));

	//testowanie prymitywa - trójk¹t
	int trLewy[2] = { 0,0 };
	int trGorny[2] = { 200,400 };
	int trPrawy[2] = { 300,200 };
	int trKolor[4] = { 128, 0, 255, 255 };
	RedSunlight::Traingle2D trojkat(trLewy, trGorny, trPrawy, trKolor);

	int prLewy[2] = { 200, 500 };
	int prPrawy[2] = { 400, 1000 };
	int prKolor[4] = { 255, 127, 39, 255 };
	RedSunlight::Rectangle2D prostokat(prLewy, prPrawy, prKolor);
	
	RedSunlight::Triangle2D trojkat(wierzcholki, glm::vec4(128, 0, 255, 255));
	RedSunlight::Rectangle2D prostokat1(glm::vec2(500, 350), glm::vec2(700, 550), glm::vec4(255, 127, 39, 255));
	RedSunlight::Rectangle2D prostokat2(glm::vec2(700, 550), glm::vec2(900, 750), glm::vec4(255, 127, 39, 255));
	RedSunlight::Cube kostka(200, 200, 0, 200, 0, 255, 140, 255);

	RedSunlight::Font czcionka("res/fonts/Segan.ttf", 50);
	RedSunlight::Text tekst(100, 800, "Testowe", czcionka);

	int wspTekstury[4] = { 0, 0, 251, 232 };
	RedSunlight::Sprite myLover(500, 600, 125, 116, "res/images/kenobi.png", wspTekstury);

	RedSunlight::EventManager::getInstance().startEventManager(&okno);
	auto* mysz = RedSunlight::EventManager::getInstance().startMouse();
	auto* klawiatura = RedSunlight::EventManager::getInstance().startKeyboard();

	auto r = 0, g = 162, b = 232;
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
				if (klawiatura->getLastPressedKey() == RedSunlight::KeyCode::eKeyA) {
					warunek = false;
				}
				
				if (klawiatura->getLastPressedKey() == RedSunlight::KeyCode::eKeyK)
					g = 0;
				else if (klawiatura->getLastPressedKey() == RedSunlight::KeyCode::eKeyArrowDown)
					g = 162;
			}
			else if (event.type == RedSunlight::EventType::eMouseButtonPressed) {
				auto* mouseButtonsState = mysz->getButtonsState();
				if (mouseButtonsState[0])
					r = 255;
				else if (mouseButtonsState[2])
					r = 0;
			}
			
		}

		okno.clearToColor(r, g, b);

		okno.drawElement(&trojkat);
		okno.drawElement(&prostokat1);
		okno.drawElement(&prostokat2);
		okno.drawElement(&tekst);
		okno.drawElement(&myLover);
		okno.drawElement(&kostka);
		
		okno.displayContent();
	}

	//koñczenie
	RedSunlight::terminate();
	return 0;
}