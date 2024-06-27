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
    Font font = LoadFont("resources/test.ttf");

	std::vector<int> values = { 40, 60, 80, 100, 60, 80, 20 };
	int daily = 20;

	while(!WindowShouldClose()) {



		BeginDrawing();
			widget.WeeklyHistogram(values, font, WIDTH, HEIGHT);
			widget.DailySales(daily, font, WIDTH, HEIGHT);
			widget.YearlyLineGraph(values, font, WIDTH, HEIGHT);
			widget.TabularData(values, font, WIDTH, HEIGHT);

			ClearBackground(BLACK);

		EndDrawing();




	}

	CloseWindow();
	



}