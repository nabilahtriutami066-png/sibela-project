#include "loginView.h"

void drawStaffLogin(windowModel *windowM)
{

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    Rectangle textBox = {
        screenWidth / 2.0f - 300,
        screenHeight - 400,
        600,
        63,
    };
    Rectangle textBoxPass = {
        screenWidth / 2.0f - 300,
        screenHeight - 400 + 63 + 80,
        600,
        63,
    };
    Rectangle buttonBox = {
        screenWidth / 2.0f - 80,
        screenHeight - 400 + 63 + 180,
        160,
        67,
    };
    drawInputBox(windowM, &windowM->loginData.email, textBox, "Email", 0, 0);

    drawInputBox(windowM, &windowM->loginData.password, textBoxPass, "Kata Sandi", 1, 1);

    if (windowM->loginData.activeInput == 2)
    {
        DrawRectangleRounded(buttonBox, 0.3, 0, PRIMARY);
    }
    else
        DrawRectangleRoundedLines(buttonBox, 0.3, 0, SIBELAWHITE);
    DrawTextEx(windowM->fontStyle.medium, "Masuk", (Vector2){(int)buttonBox.x + MeasureTextEx(windowM->fontStyle.medium, "Masuk", 40, 0).x / 2, (int)buttonBox.y + MeasureTextEx(windowM->fontStyle.medium, "Masuk", 40, 0).y / 2 - 8}, 40, 0, SIBELAWHITE);
}

void drawMuridTeacherLogin(windowModel *windowM)
{

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    Rectangle textBox = {
        screenWidth / 2.0f - 300,
        screenHeight - 400,
        600,
        63,
    };
    Rectangle textBoxPass = {
        screenWidth / 2.0f - 300,
        screenHeight - 400 + 63 + 80,
        600,
        63,
    };
    Rectangle buttonBox = {
        screenWidth / 2.0f - 80,
        screenHeight - 400 + 63 + 180,
        160,
        67,
    };
    drawInputBox(windowM, &windowM->loginData.phoneNumber, textBox, "No. Telp", 0, 0);
    drawInputBox(windowM, &windowM->loginData.password, textBoxPass, "Kata Sandi", 1, 1);

    if (windowM->loginData.activeInput == 2)
    {
        DrawRectangleRounded(buttonBox, 0.3, 0, PRIMARY);
    }
    else
        DrawRectangleRoundedLines(buttonBox, 0.3, 0, SIBELAWHITE);
    DrawTextEx(windowM->fontStyle.medium, "Masuk", (Vector2){(int)buttonBox.x + MeasureTextEx(windowM->fontStyle.medium, "Masuk", 40, 0).x / 2, (int)buttonBox.y + MeasureTextEx(windowM->fontStyle.medium, "Masuk", 40, 0).y / 2 - 8}, 40, 0, SIBELAWHITE);
}