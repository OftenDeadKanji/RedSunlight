#pragma once

class RED_API GlobalInformation {
public:
	GlobalInformation(const GlobalInformation&) = delete;
	
	static GlobalInformation& getInstance();
	
	void setScreenResolution(int width, int height);
	std::pair<int, int>& getScreenResolution();

private:
	GlobalInformation();

	std::pair<int, int> m_screenResolution;
};