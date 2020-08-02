#pragma once

class GlobalInformation {
public:
	static GlobalInformation& getInstance();
	
	void setScreenResolution(int width, int height);
	std::pair<int, int>& getScreenResolution();

private:
	GlobalInformation();
	GlobalInformation(const GlobalInformation&);

	std::pair<int, int> screenResolution;
};