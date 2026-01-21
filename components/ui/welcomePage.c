#include "welcomePage.h"

void drawWelcomePage(windowModel *windowM)
{
    struct tm *formattedTime = localtime(&windowM->time);
    char *text = TextFormat("%02d:%02d:%02d", formattedTime->tm_hour, formattedTime->tm_min, formattedTime->tm_sec);
    Vector2 measuredText = MeasureTextEx(windowM->fontStyle.bold, text, 150, 0);
    DrawTextEx(windowM->fontStyle.medium, TextFormat("Halo, %s %s!", windowM->authUser.role, windowM->authUser.nama), (Vector2){300 + 1620 / 2 - MeasureTextEx(windowM->fontStyle.medium, TextFormat("Halo, %s %s!", windowM->authUser.role, windowM->authUser.nama), 80, 0).x / 2, 90}, 80, 0, SIBELAWHITE);
    DrawTextEx(windowM->fontStyle.medium, text, (Vector2){300 + 1620 / 2 - measuredText.x / 2, 1080 / 2 - measuredText.y / 2}, 150, 0, SIBELAWHITE);
}