#include <iostream>
#include <RedSunlight.h>

int main()
{
	if (RedSunlight::init() == RED_FAIL)
		return -1;
	
	RedSunlight::Window window(RedSunlight::WindowProperties(1600, 900, RedSunlight::WindowMode::eWindowed, "Testing"));
	
	int trLeft[2] = { 0,0 };
	int trUp[2] = { 200,400 };
	int trRight[2] = { 300,200 };
	int trColor[4] = { 128, 0, 255, 255 };
	RedSunlight::Triangle2D triangle(trLeft, trUp, trRight, trColor);

	int prLewy[2] = { 200, 500 };
	int prPrawy[2] = { 400, 1000 };
	int prKolor[4] = { 255, 127, 39, 255 };
	RedSunlight::Rectangle2D rectangle(prLewy, prPrawy, prKolor);

	RedSunlight::Font font("res/fonts/Segan.ttf", 50);
	RedSunlight::Text text(100, 450, "Just for test", font);

	int wspTekstury[4] = { 0, 0, 251, 232 };
	RedSunlight::Sprite myLover(500, 600, 125, 116, "res/images/kenobi.png", wspTekstury);

	RedSunlight::EventManager eventManager;
	window.attachEventManager(eventManager);
	
	RedSunlight::Mouse mouse;
	eventManager.registerMouse(mouse);
	RedSunlight::Keyboard keyboard;
	eventManager.registerKeyboard(keyboard);

	auto loopCondition = true;
	while (loopCondition)
	{
		RedSunlight::EventManager::checkForEvents();
		
		while (!eventManager.isEventQueueEmpty()) {
			const auto event = eventManager.popEvent();
			if (event.type == RedSunlight::EventType::eWindowClosed) {
				loopCondition = false;
			}

		}

		RedSunlight::Window::clearToColor(157, 217, 234);
		
		triangle.draw();
		text.draw();
		myLover.draw();

		window.displayContent();
	}

	//cleaning
	RedSunlight::terminate();
	return 0;
}