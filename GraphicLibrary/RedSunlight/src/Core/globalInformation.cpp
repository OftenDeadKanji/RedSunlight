#include "pch.h"

GlobalInformation::GlobalInformation()
{}

GlobalInformation& GlobalInformation::getInstance()
{
	static GlobalInformation instance;
	return instance;
}

void GlobalInformation::setScreenResolution(int width, int height)
{
	screenResolution = std::pair<int, int>(width, height);
}

std::pair<int, int>& GlobalInformation::getScreenResolution()
{
	return screenResolution;
}
