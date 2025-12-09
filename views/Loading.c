#include "Loading.h"

void LoadingScreen(windowModel *windowM)
{
    Texture2D logo = LoadTexture("sibela_Versi2.png"); // pastikan file ada di folder yang sama

    float progress = 0.0f;

    Color panelColor = (Color){ 38, 50, 66, 255 };

    int boxSize = 22;
    int boxGap  = 8;
    int totalBox = 12;

    int loadingWidth = totalBox * (boxSize + boxGap);

    while (!WindowShouldClose()) {

        if (progress < 1.0f) progress += 0.003f;

        BeginDrawing();
        ClearBackground(panelColor);

        // === Center Logo ===
        int logoX = (1980 - logo.width) / 2;
        int logoY = (1020 / 2) - logo.height - 40; // agak ke atas sedikit

        DrawTexture(logo, logoX, logoY, WHITE);

        // === Loading Bar di bawah logo ===
        int loadingX = (1980 - loadingWidth) / 2;
        int loadingY = logoY + logo.height + 60;

        int filled = (int)(progress * totalBox);

        for (int i = 0; i < totalBox; i++) {
            int x = loadingX + i * (boxSize + boxGap);

            if (i < filled) {
                DrawRectangle(x, loadingY, boxSize, boxSize, BLUE);
            } else {
                DrawRectangleLines(x, loadingY, boxSize, boxSize, BLUE);
            }
        }

        char persen[16];
        sprintf(persen, "%d%%", (int)(progress * 100));

        DrawText(persen, loadingX + loadingWidth + 25, loadingY + 2, 30, BLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
