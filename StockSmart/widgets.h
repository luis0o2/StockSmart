#include <iostream>
#include <raylib.h>
#include <fstream>
#include <vector>

class Widgets {
private:


public:

	void WeeklyHistogram(std::vector<int> data, Font font, int width, int height);
	void DailySales(int daily, Font font, int width, int height);
	void YearlyLineGraph(std::vector<int> data, Font font, int width, int height);
	void TabularData(std::vector<int> data, Font font, int width, int height);


};