#include "widgets.h"


void Widgets::WeeklyHistogram(std::vector<int> data, Font font, int width, int height) {

    int graphX = width / 2 - 20;
    int graphY = height / 20;
    int graphWidth = width / 2;
    int graphHeight = height / 3.5;

    // Draw the outer rounded rectangle
    Rectangle graphRec = { (float)graphX, (float)graphY, (float)graphWidth, (float)graphHeight };
    DrawRectangleRoundedLines(graphRec, 0.1f, 12, 2.0f, PURPLE);

    // Calculate the width of each bar
    int barWidth = graphWidth / 7;
    int maxDataValue = 100;

    for (int i = 0; i < 7; i++) {
        int barHeight = ((data[i] * graphHeight) / maxDataValue) - 30;

        // Ensure the bars fit within the outer rectangle
        int barX = graphX + i * barWidth + 5; // Adding a small margin
        int barY = graphY + graphHeight - barHeight;

        // Draw the bar
        DrawRectangle(barX, barY, barWidth - 10, barHeight, PURPLE);
        Vector2 textPos{ barX + (barWidth - 10) / 2 - 10 , barY - 20 };
        DrawTextEx(font, TextFormat("%i", data[i]), textPos, 20, 2, PURPLE);

    }
}

void Widgets::DailySales(int daily, Font font, int width, int height)
{
    int graphX = 20;
    int graphY = height / 20;
    int graphWidth = width / 2.5;
    int graphHeight = height / 3.5;

    Rectangle graphRec = { (float)graphX, (float)graphY, (float)graphWidth, (float)graphHeight };
    DrawRectangleRoundedLines(graphRec, 0.1f, 12, 2.0f, PURPLE);

    Vector2 textPos1{graphWidth / 4.5, graphHeight / 6};
    Vector2 textPos2{ graphWidth / 2.8, graphHeight / 2 };

    DrawTextEx(font, "DAILY", textPos1, 80, 2, PURPLE);
    DrawTextEx(font, TextFormat("%i", daily), textPos2, 120, 2, PURPLE);

}

void Widgets::YearlyLineGraph(std::vector<int> data, Font font, int width, int height)
{
    int graphX = 20;
    int graphY = height / 2.5;
    int graphWidth = width - 40;
    int graphHeight = height / 3.5;

    Rectangle graphRec = { (float)graphX, (float)graphY, (float)graphWidth, (float)graphHeight };
    DrawRectangleRoundedLines(graphRec, 0.1f, 12, 2.0f, PURPLE);


}

void Widgets::TabularData(std::vector<int> data, Font font, int width, int height)
{
    int graphX = 20;
    int graphY = height / 1.4;
    int graphWidth = width - 40;
    int graphHeight = height / 3.8;

    Rectangle graphRec = { (float)graphX, (float)graphY, (float)graphWidth, (float)graphHeight };
    DrawRectangleRoundedLines(graphRec, 0.1f, 12, 2.0f, PURPLE);
    
    for (int i = 1; i <= 3; i++) {
        int spacing = graphHeight / 4;
        DrawRectangleLines(graphX + spacing * i, )

    }

    for (int j = 0; j < data.size(); j++) {

    }


}
