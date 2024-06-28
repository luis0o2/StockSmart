#include <iostream>
#include <raylib.h>
#include <fstream>
#include <vector>
#include "widgets.h"

#define WIDTH 800
#define HEIGHT 1000 




int main() {

	InitWindow(WIDTH, HEIGHT, "StockSmart");
	SetTargetFPS(60);
	Widgets widget;
	Widgets widget2;
    Font font = LoadFont("resources/test.ttf");
	std::ifstream read("C:/Users/ochoa/Downloads/productor-export.csv");


	std::vector<int> values = { 40, 60, 80, 100, 60, 80, 20 };
	std::vector<int> values2 = { 57, 42, 19, 35, 97, 81, 24 };

	int daily = 5000;

	while(!WindowShouldClose()) {



		BeginDrawing();
			widget.WeeklyHistogram(values, font, WIDTH, HEIGHT);
			widget.DailySales(daily, font, WIDTH, HEIGHT);
			widget.YearlyLineGraph(values, font, WIDTH, HEIGHT, GREEN);
			widget2.YearlyLineGraph(values2, font, WIDTH, HEIGHT, YELLOW);
			widget.TabularData(values, font, WIDTH, HEIGHT);

			ClearBackground(BLACK);

		EndDrawing();




	}

	CloseWindow();
	



}