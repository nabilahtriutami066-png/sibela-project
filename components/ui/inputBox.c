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
        eyeOpen  = LoadTexture("assets/images/BUKA.png");
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
        input->validation.isInputInvalid ? RED :
        (((windowM->currWindow == LOGINMURID ||
           windowM->currWindow == LOGINPENGAJAR ||
           windowM->currWindow == LOGINSTAFF)
           ? windowM->loginData.activeInput
           : windowM->curPos) == posIndex
           ? PRIMARY
           : SIBELAWHITE)
    );

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
        35
    };

    if (isSecret &&
        CheckCollisionPointRec(GetMousePosition(), eyeBtn) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        input->showSecret = !input->showSecret;
    }

    if (isSecret && !input->showSecret)
    {
        for (int i = 0; i < input->charLen; i++)
        {
            DrawCircle(
                (int)textBox.x + 16 + i * 28,
                (int)textBox.y + textBox.height / 2,
                12,
                SIBELAWHITE
            );
        }
    }
    else
    {
        DrawTextEx(windowM->fontStyle.regular,
                   input->text,
                   (Vector2){(int)textBox.x + 5, (int)textBox.y + 8},
                   40, 0, SIBELAWHITE);
    }
    if (isSecret)
    {
        Texture2D eyeTex = input->showSecret ? eyeOpen : eyeClose;

        DrawTexturePro(
            eyeTex,
            (Rectangle){0, 0, eyeTex.width, eyeTex.height},
            eyeBtn,
            (Vector2){0, 0},
            0,
            WHITE
        );
    }
}
