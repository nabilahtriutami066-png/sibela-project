#include "inputBox.h"

void drawInputBox(windowModel *windowM, InputParams *input, Rectangle textBox, char Label[], int posIndex, int isSecret)
{
    DrawTextEx(windowM->fontStyle.medium, Label, (Vector2){(int)textBox.x, (int)textBox.y - 44}, 40, 0, SIBELAWHITE);
    DrawRectangleRoundedLines(textBox, 0.3, 0, input->validation.isInputInvalid ? RED : ((windowM->currWindow == LOGINMURID || windowM->currWindow == LOGINPENGAJAR || windowM->currWindow == LOGINSTAFF) ? windowM->loginData.activeInput : windowM->curPos) == posIndex ? PRIMARY
                                                                                                                                                                                                                                                                          : SIBELAWHITE);

    if (input->validation.isInputInvalid)
    {
        DrawTextEx(windowM->fontStyle.regular, input->validation.errMessage, (Vector2){(int)textBox.x + 5, (int)textBox.y + 70}, 20, 0, RED);
    }
    if (isSecret)
    {
        for (int i = 0; i < input->charLen; i++)
        {
            DrawCircle((int)textBox.x + 16 + i * 28, (int)textBox.y + textBox.height / 2, 12, SIBELAWHITE);
        }
    }
    else
        DrawTextEx(windowM->fontStyle.regular, input->text, (Vector2){(int)textBox.x + 5, (int)textBox.y + 8}, 40, 0, SIBELAWHITE);
}