#include <iostream>
#include <RedSunlight.h>

int main()
{
	if (RedSunlight::init() == RED_FAIL)
		return -1;

	//utworzenie okna
	RedSunlight::Window okno(RedSunlight::WindowProperties(1600, 900, "Testujemy", RedSunlight::WindowMode::eWindowed));

	//testowanie prymitywa - trójk¹t
	RedSunlight::Traingle2D trojkat(glm::vec2(0, 0), glm::vec2(200, 400), glm::vec2(300,200), glm::vec4(128, 0, 255, 255));
	RedSunlight::Rectangle2D prostokat(glm::vec2(200, 500), glm::vec2(400, 1000), glm::vec4(255, 127, 39, 255));
	
	RedSunlight::Font czcionka("res/fonts/Segan.ttf", 50);
	RedSunlight::Text tekst(100, 800, czcionka, "Testowe", glm::vec3(0, 0, 0));

	RedSunlight::Sprite myLover(500, 600, 251, 232, "res/images/kenobi.png", std::make_tuple(0, 0, 251, 232));

	RedSunlight::EventManager::getInstance().startEventManager(&okno);
	auto* mysz = RedSunlight::EventManager::getInstance().startMouse();
	auto* klawiatura = RedSunlight::EventManager::getInstance().startKeyboard();

	auto r = 0, g = 162, b = 232;
	auto warunek = true;
	while (warunek)
	{
		auto queue = RedSunlight::EventManager::getInstance().checkForEvents();
		std::cout << queue.size() << std::endl;
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
		okno.drawElement(&prostokat);
		okno.drawElement(&tekst);
		okno.drawElement(&myLover);

		okno.displayContent();
	}

	//koñczenie
	RedSunlight::terminate();
	return 0;
}