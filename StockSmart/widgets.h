#include <iostream>
#include <raylib.h>
#include <fstream>
#include <vector>
#include <string>

class Widgets {
private:


public:

	void WeeklyHistogram(std::vector<int> data, Font font, int width, int height);
	void DailySales(int daily, Font font, int width, int height);
	void YearlyLineGraph(std::vector<int> data, Font font, int width, int height, Color color);
	void TabularData(std::vector<int> data, Font font, int width, int height);


};