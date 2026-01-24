#include "inputBox.h"

static Texture2D eyeOpen;
static Texture2D eyeClose;
static bool eyeLoaded = false;

void drawInputBox(windowModel *windowM,
                  InputParams *input,
                  Rectangle textBox,
                  char Label[],
                  int posIndex,
                  int isSecret)
{
    if (isSecret && !eyeLoaded)
    {
        eyeOpen = LoadTexture("assets/images/BUKA.png");
        eyeClose = LoadTexture("assets/images/TUTUP.png");
        eyeLoaded = true;
    }

    DrawTextEx(windowM->fontStyle.medium,
               Label,
               (Vector2){(int)textBox.x, (int)textBox.y - 44},
               40, 0, SIBELAWHITE);

    DrawRectangleRoundedLines(
        textBox,
        0.3, 0,

        (((windowM->currWindow == LOGINMURID ||
           windowM->currWindow == LOGINPENGAJAR ||
           windowM->currWindow == LOGINSTAFF)
              ? windowM->loginData.activeInput
              : windowM->curPos) == posIndex
             ? PRIMARY
         : input->validation.isInputInvalid ? RED
                                            : SIBELAWHITE));

    if (input->validation.isInputInvalid)
    {
        DrawTextEx(windowM->fontStyle.regular,
                   input->validation.errMessage,
                   (Vector2){(int)textBox.x + 5, (int)textBox.y + 70},
                   20, 0, RED);
    }

    Rectangle eyeBtn = {
        textBox.x + textBox.width - 45,
        textBox.y + 10,
        35,
        35};

    if (isSecret &&
        CheckCollisionPointRec(GetMousePosition(), eyeBtn) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        input->showSecret = !input->showSecret;
    }

    // Calculate content area and scissoring
    Rectangle contentArea = textBox;
    contentArea.x += 4;
    contentArea.width -= 8;
    if (isSecret)
        contentArea.width -= 45; // Reserve space for eye button

    BeginScissorMode((int)contentArea.x, (int)contentArea.y, (int)contentArea.width, (int)contentArea.height);

    if (isSecret && !input->showSecret)
    {
        float totalWidth = 16 + (input->charLen * 28);
        float offset = 0;
        if (totalWidth > contentArea.width)
            offset = totalWidth - contentArea.width;

        for (int i = 0; i < input->charLen; i++)
        {
            DrawCircle(
                (int)textBox.x + 16 + i * 28 - (int)offset,
                (int)textBox.y + textBox.height / 2,
                12,
                SIBELAWHITE);
        }
    }
    else
    {
        Vector2 textSize = MeasureTextEx(windowM->fontStyle.regular, input->text, 40, 0);
        float offset = 0;
        if (textSize.x > contentArea.width)
            offset = textSize.x - contentArea.width;

        DrawTextEx(windowM->fontStyle.regular,
                   input->text,
                   (Vector2){(int)textBox.x + 5 - (int)offset, (int)textBox.y + 8},
                   40, 0, SIBELAWHITE);
    }
    EndScissorMode();
    if (isSecret)
    {
        Texture2D eyeTex = input->showSecret ? eyeOpen : eyeClose;

        DrawTexturePro(
            eyeTex,
            (Rectangle){0, 0, eyeTex.width, eyeTex.height},
            eyeBtn,
            (Vector2){0, 0},
            0,
            WHITE);
    }
}
