#include "src/RedLightBulb.h"

void init()
{
	RedLightBulb::init();

}

void term()
{
	RedLightBulb::terminate();
}

int main()
{
	init();

	//RedLightBulb::Window window;

	term();
	return 0;
}
