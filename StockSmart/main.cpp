#include <iostream>
#include <raylib.h>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "widgets.h"
#include "SalesData.h" 
#include <map>


#define WIDTH 2000
#define HEIGHT 1200




// Function to check if a string is a valid number (integer or floating-point)
bool isNumeric(const std::string& str) {
	char* endptr = 0;
	strtod(str.c_str(), &endptr);
	return endptr != str.c_str() && *endptr == '\0';
}

// Function to remove leading and trailing quotation marks from a string
void trimQuotes(std::string& str) {
	if (!str.empty() && str.front() == '"' && str.back() == '"') {
		str = str.substr(1, str.size() - 2);
	}
}

std::string getYearMonth(const std::string& date) {
    std::stringstream ss(date);
    std::string month, day, year;
    std::getline(ss, month, '/');
    getline(ss, day, '/');
    getline(ss, year);
    return year + "-" + (month.size() == 1 ? "0" + month : month); // Format as YYYY-MM
}

void processSalesData(const std::string& filename,
    std::unordered_map<std::string, SalesData>& productSales,
    std::unordered_map<std::string, std::unordered_map<std::string, SalesData>>& monthlyCountrySales,
    std::unordered_map<std::string, std::unordered_map<std::string, SalesData>>& countryProductSales) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    std::string line, col;
    std::getline(file, line); // Read header line and discard

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string productType, country, soldStr, returnStr, revenueStr, date, asin, cancelled;

        std::getline(ss, date, ',');
        std::getline(ss, asin, ',');
        std::getline(ss, productType, ',');
        std::getline(ss, country, ',');
        std::getline(ss, cancelled, ',');

        std::getline(ss, returnStr, ',');
        trimQuotes(returnStr);
        int returned = 0;
        if (!returnStr.empty() && isNumeric(returnStr)) {
            returned = stoi(returnStr);
            productSales[productType].returned += returned;
            countryProductSales[productType][country].returned += returned;

        }

        std::getline(ss, soldStr, ',');
        trimQuotes(soldStr);
        int sold = 0;
        if (!soldStr.empty() && isNumeric(soldStr)) {
            sold = stoi(soldStr);
            productSales[productType].sold += sold;
            countryProductSales[productType][country].sold += sold;
            std::string yearMonth = getYearMonth(date);
            monthlyCountrySales[country][yearMonth].sold += sold;
        }

        std::getline(ss, revenueStr, ',');
        trimQuotes(revenueStr);
        double revenue = 0.0;
        if (!revenueStr.empty() && isNumeric(revenueStr)) {
            revenue = stod(revenueStr);
            productSales[productType].revenue += revenue;
            countryProductSales[productType][country].revenue += revenue;
            std::string yearMonth = getYearMonth(date);

            monthlyCountrySales[country][yearMonth].revenue += revenue;

        }


    }
        file.close();

}



int main() {

	InitWindow(WIDTH, HEIGHT, "StockSmart");
	SetTargetFPS(60);
	Widgets widget;
    Widgets usWidget;
    Widgets gbWidget;
    Widgets deWidget;
    Widgets frWidget;
    Widgets itWidget;
    Widgets esWidget;
    Widgets jpWidget;
    Font font = LoadFont("resources/test.ttf");
    std::unordered_map<std::string, SalesData> productSales; // Total sales across all countries
    std::unordered_map<std::string, std::unordered_map<std::string, SalesData>> countryProductSales; // Sales by country
    std::unordered_map<std::string, std::unordered_map<std::string, SalesData>> monthlyCountrySales; //monthly country sales
    std::string filename = "C:/Users/ochoa/Downloads/export.csv";


    std::vector<int> usSalesData;
    std::vector<int> gbSalesData;
    std::vector<int> deSalesData;
    std::vector<int> frSalesData;
    std::vector<int> itSalesData;
    std::vector<int> esSalesData;
    std::vector<int> jpSalesData;

    processSalesData(filename, productSales, monthlyCountrySales, countryProductSales);

  

    int totalSold = 0;
    int totalReturns = 0;
    double totalProfits = 0.0;

    //TOTAL SALES
    for (const auto& pair : productSales) {
       
        totalSold += pair.second.sold;
        totalReturns += pair.second.returned;
        totalProfits += pair.second.revenue;
    }



    int usSold = 0, gbSold = 0, deSold = 0, frSold = 0, itSold = 0, esSold = 0, jpSold = 0;
    int usReturned = 0, gbReturned = 0, deReturned = 0, frReturned = 0, itReturned = 0, esReturned = 0, jpReturned = 0;
    double usProfits = 0.0, gbProfits = 0.0, deProfits = 0.0, frProfits = 0.0, itProfits = 0.0, esProfits = 0.0, jpProfits = 0.0;

    for (const auto& productPair : countryProductSales) {
        const auto& countrySalesMap = productPair.second;

        for (const auto& countryPair : countrySalesMap) {
            const std::string& country = countryPair.first;
            const SalesData& salesData = countryPair.second;

            if (country == "US") { usProfits += salesData.revenue; usSold += salesData.sold; usReturned += salesData.returned; }
            else if (country == "GB") { gbProfits += salesData.revenue; gbSold += salesData.sold; gbReturned += salesData.returned; }
            else if (country == "DE") { deProfits += salesData.revenue; deSold += salesData.sold; deReturned += salesData.returned; }
            else if (country == "FR") { frProfits += salesData.revenue; frSold += salesData.sold; frReturned += salesData.returned; }
            else if (country == "IT") { itProfits += salesData.revenue; itSold += salesData.sold; itReturned += salesData.returned; }
            else if (country == "ES") { esProfits += salesData.revenue; esSold += salesData.sold; esReturned += salesData.returned; }
            else if (country == "JP") { jpProfits += salesData.revenue; jpSold += salesData.sold; jpReturned += salesData.returned; }
        }
    }
    std::vector<int> sales;
    sales.push_back(usSold);
    sales.push_back(gbSold);
    sales.push_back(deSold);
    sales.push_back(frSold);
    sales.push_back(itSold);
    sales.push_back(esSold);
    sales.push_back(jpSold);

    for (const auto& countryPair : monthlyCountrySales) {
        const std::string& country = countryPair.first;
        const auto& monthlySalesMap = countryPair.second;

        for (const auto& monthPair : monthlySalesMap) {
            const std::string& yearMonth = monthPair.first;
            const SalesData& salesData = monthPair.second;

            if (country == "US") { usSalesData.push_back(salesData.sold); }
            else if (country == "GB") { gbSalesData.push_back(salesData.sold); }
            else if (country == "DE") { deSalesData.push_back(salesData.sold); }
            else if (country == "FR") { frSalesData.push_back(salesData.sold); }
            else if (country == "IT") { itSalesData.push_back(salesData.sold); }
            else if (country == "ES") { esSalesData.push_back(salesData.sold); }
            else if (country == "JP") { jpSalesData.push_back(salesData.sold); }

            //cout << "\tMonth: " << yearMonth << ", Sold: " << salesData.sold
            //    << ", Revenue: $" << salesData.revenue << endl;
        }
    }

	std::vector<int> values = { 40, 60, 80, 100, 60, 80, 20 };
	std::vector<int> values2 = { 57, 42, 19, 35, 97, 81, 24 };


	while(!WindowShouldClose()) {



		BeginDrawing();
			widget.WeeklyHistogram(sales, font, WIDTH, HEIGHT);
			widget.DailySales(totalSold, font, WIDTH, HEIGHT);
            widget.YearlyLineGraph(values, font, WIDTH, HEIGHT, GREEN);

            usWidget.YearlyLineGraph(usSalesData, font, WIDTH, HEIGHT, GREEN);
            gbWidget.YearlyLineGraph(gbSalesData, font, WIDTH, HEIGHT, BLUE);
            deWidget.YearlyLineGraph(deSalesData, font, WIDTH, HEIGHT, RED);
            frWidget.YearlyLineGraph(frSalesData, font, WIDTH, HEIGHT, YELLOW);
            itWidget.YearlyLineGraph(itSalesData, font, WIDTH, HEIGHT, PURPLE);
            esWidget.YearlyLineGraph(esSalesData, font, WIDTH, HEIGHT, ORANGE);
            jpWidget.YearlyLineGraph(jpSalesData, font, WIDTH, HEIGHT, PINK);
            
			widget.TabularData(productSales, font, WIDTH, HEIGHT);

			ClearBackground(BLACK);

		EndDrawing();




	}

	CloseWindow();
	



}