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
        if (data[i] < (maxDataValue / 2)) {
            DrawRectangle(barX, barY, barWidth - 10, barHeight, DARKPURPLE);
        }else if (data[i] < (maxDataValue / 1.5)) {
            DrawRectangle(barX, barY, barWidth - 10, barHeight, PURPLE);
        }
        else {
            DrawRectangle(barX, barY, barWidth - 10, barHeight, VIOLET);
        }
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

    // Measure the text dimensions
    Vector2 totalTextSize = MeasureTextEx(font, "TOTAL", 80, 2);
    Vector2 dailyTextSize = MeasureTextEx(font, TextFormat("%i", daily), 120, 2);

    // Calculate the centered position for the text
    Vector2 textPos1 = {
        graphX + (graphWidth - totalTextSize.x) / 2,
        graphY + (graphHeight / 2 - totalTextSize.y) / 2
    };
    Vector2 textPos2 = {
        graphX + (graphWidth - dailyTextSize.x) / 2,
        graphY + (graphHeight / 2 - dailyTextSize.y) / 2 + graphHeight / 2
    };

    DrawTextEx(font, "TOTAL", textPos1, 80, 2, PURPLE);
    DrawTextEx(font, TextFormat("%i", daily), textPos2, 120, 2, PURPLE);

}

void Widgets::YearlyLineGraph(std::vector<int> data, Font font, int width, int height, Color color) {
    int graphX = 20;
    int graphY = height / 2.5;
    int graphWidth = width - 40;
    int graphHeight = height / 3.5;

    Rectangle graphRec = { (float)graphX, (float)graphY, (float)graphWidth, (float)graphHeight };
    DrawRectangleRoundedLines(graphRec, 0.1f, 12, 2.0f, PURPLE);

    // Calculate the positions of data points
    int maxDataValue = *std::max_element(data.begin(), data.end());
    std::vector<Vector2> points(data.size());
    for (int i = 0; i < data.size(); i++) {
        float x = graphX + (i * (graphWidth / (data.size() - 1)));
        float y = graphY + graphHeight - ((data[i] / (float)maxDataValue) * graphHeight - 20);
        points[i] = { x, y };
    }

    // Draw the lines connecting data points
    for (int i = 0; i < points.size() - 1; i++) {
        DrawLineEx(points[i], points[i + 1], 2.0f, color);
    }

    // Draw data points (optional)
    for (int i = 0; i < points.size(); i++) {
        DrawCircleV(points[i], 5, color);
        Vector2 pos{ points[i].x - 10, points[i].y - 20 };
        DrawTextEx(font, TextFormat("%d", data[i]), pos, 20, 2, color);
    }
}

void Widgets::TabularData(std::vector<int> data, Font font, int width, int height)
{
    int graphX = 20;
    int graphY = height / 1.4;
    int graphWidth = width - 40;
    int graphHeight = height / 3.8;

    std::vector<std::string> tabularInfo{ "TYPE", "PUBLISHED", "SOLD", "REVENUE", "RETURN%" };

    Rectangle graphRec = { (float)graphX, (float)graphY, (float)graphWidth, (float)graphHeight };
    DrawRectangleRoundedLines(graphRec, 0.1f, 12, 2.0f, PURPLE);

    int numColumns = data.size();
    int numRows = tabularInfo.size();

    // Draw horizontal grid lines
    for (int i = 1; i < numRows; i++) {
        int spacing = graphHeight / (numRows);
        DrawLine(graphX, graphY + spacing * i, graphX + graphWidth, graphY + spacing * i, PURPLE);
    }

    // Draw vertical grid lines
    for (int j = 1; j <= numColumns; j++) {
        int spacing = graphWidth / (numColumns + 1);
        DrawLine(graphX + spacing * j, graphY, graphX + spacing * j, graphY + graphHeight, PURPLE);
    }

    // Draw headers (top to bottom)
    for (int i = 0; i < numRows; i++) {
        int spacing = graphHeight / (numRows + 1) + 10;
        Vector2 headerPos = { graphX + 10, (graphY + spacing * i) + 20};
        DrawTextEx(font, tabularInfo[i].c_str(), headerPos, 12, 2, PURPLE);
    }

    // Draw data (left to right in rows)
    for (int j = 0; j < numColumns; j++) {
        int columnSpacing = graphWidth / (numColumns);
        Vector2 dataPos = { graphX + columnSpacing * (j + 1) - MeasureTextEx(font, TextFormat("%d", data[j]), 20, 2).x / 2, graphY + graphHeight / (numRows + 1) + 10 };
        DrawTextEx(font, TextFormat("%d", data[j]), dataPos, 20, 2, PURPLE);
    }
}