#include "pieChart.h"
#include <math.h>

void drawPieChart(windowModel *windowM, Vector2 pos, int value1, int value2, char label1[], char label2[], char chartLabel[], int isMoney)
{
    int hoveredSlice = -1;
    int sliceCount = 2;
    float values[2] = {(float)value1, (float)value2};
    char labels[2][32];
    strcpy(labels[0], label1);
    strcpy(labels[1], label2);
    Color colors[2] = {PRIMARY, SIBELAWHITE};
    const float radius = 205.0f;
    float totalValue = values[0] + values[1];
    Vector2 center = pos;
    float donutInnerRadius = 25.0f;

    float startAngle = 0.0f;
    for (int i = 0; i < sliceCount; i++)
    {
        float sweepAngle = (totalValue > 0) ? (values[i] / totalValue) * 360.0f : 0.0f;
        float midAngle = startAngle + sweepAngle / 2.0f; // Middle angle for label positioning

        Color color = ColorFromHSV((float)i / sliceCount * 360.0f, 0.75f, 0.9f);
        float currentRadius = radius;

        // Make the hovered slice pop out by adding 5 pixels to its radius
        if (i == hoveredSlice)
            currentRadius += 20.0f;

        // Draw the pie slice using raylib's DrawCircleSector function
        DrawCircleSector(center, currentRadius, startAngle, startAngle + sweepAngle, 120, colors[i]);

        // Draw the label for the current slice
        if (values[i] > 0)
        {
            char labelText[64] = {0};
            snprintf(labelText, 64, "%s\n%s%d(%.0f%%)", labels[i], isMoney ? "Rp " : "", (int)values[i], (values[i] / totalValue) * 100.0f);

            Vector2 textSize = MeasureTextEx(GetFontDefault(), labelText, 20, 1);
            float labelRadius = radius * 0.7f;
            Vector2 labelPos = {center.x + cosf(midAngle * DEG2RAD) * labelRadius - textSize.x / 2.0f,
                                center.y + sinf(midAngle * DEG2RAD) * labelRadius - textSize.y / 2.0f};
            DrawText(labelText, (int)labelPos.x, (int)labelPos.y, 20, i == 1 ? PRIMARY : WHITE);
        }

        // donut
        //  DrawCircle(center.x, center.y, donutInnerRadius, RAYWHITE);

        startAngle += sweepAngle;
    }
    Vector2 textLen = MeasureTextEx(windowM->fontStyle.medium, chartLabel, 24, 0);

    DrawTextEx(windowM->fontStyle.medium, chartLabel, (Vector2){(int)center.x - textLen.x / 2, (int)center.y + (int)radius + 5}, 24, 0, SIBELAWHITE);
}