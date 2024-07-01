#ifndef WIDGETS_H
#define WIDGETS_H
#include <iostream>
#include <raylib.h>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "SalesData.h" 

class Widgets {
private:


public:

	void WeeklyHistogram(std::vector<int> data, Font font, int width, int height);
	void DailySales(int daily, Font font, int width, int height);
	void YearlyLineGraph(std::vector<int>& data, Font& font, int width, int height, Color color, int location, const char* country);
	void TabularData(std::unordered_map<std::string, SalesData>& productSales, Font font, int width, int height);


};

#endif