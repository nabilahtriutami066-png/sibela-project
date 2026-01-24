#include "textArea.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

static bool IsWhitespace(char c)
{
    return (c == ' ' || c == '\t');
}

void drawTextArea(windowModel *windowM,
                  InputParams *input,
                  Rectangle textBox,
                  char Label[],
                  int posIndex)
{
    // Draw Label
    if (Label != NULL && Label[0] != '\0')
    {
        DrawTextEx(windowM->fontStyle.medium,
                   Label,
                   (Vector2){(int)textBox.x, (int)textBox.y - 44},
                   40, 0, SIBELAWHITE);
    }

    // Determine Border Color
    Color borderColor = SIBELAWHITE;
    if (input->validation.isInputInvalid)
    {
        borderColor = RED;
    }
    else
    {
        bool isActive = false;
        if (windowM->currWindow == LOGINMURID ||
            windowM->currWindow == LOGINPENGAJAR ||
            windowM->currWindow == LOGINSTAFF)
        {
            if (windowM->loginData.activeInput == posIndex)
                isActive = true;
        }
        else
        {
            if (windowM->curPos == posIndex)
                isActive = true;
        }

        if (isActive)
            borderColor = PRIMARY;
    }

    // Draw Box
    DrawRectangleRoundedLines(textBox, 0.3, 0, borderColor);

    // Draw Error Message
    if (input->validation.isInputInvalid)
    {
        DrawTextEx(windowM->fontStyle.regular,
                   input->validation.errMessage,
                   (Vector2){(int)textBox.x + 5, (int)textBox.y + textBox.height + 5},
                   20, 0, RED);
    }

    // Text Wrapping
    Font font = windowM->fontStyle.regular;
    float fontSize = 40;
    float spacing = 0;
    Color color = SIBELAWHITE;

    Rectangle textBounds = {
        textBox.x + 10,
        textBox.y + 10,
        textBox.width - 20,
        textBox.height - 20};

    float maxWidth = textBounds.width;
    float currentX = 0;
    float currentY = 0;

    const char *text = input->text;
    int len = strlen(text);
    int i = 0;

    while (i < len)
    {
        // Handle Newlines
        if (text[i] == '\n')
        {
            currentX = 0;
            currentY += fontSize;
            i++;
            continue;
        }

        // Identify token (Word or Whitespace sequence)
        int start = i;
        bool isSpace = IsWhitespace(text[i]);

        while (i < len && text[i] != '\n' && IsWhitespace(text[i]) == isSpace)
        {
            i++;
        }
        int end = i;
        int tokenLen = end - start;

        // Extract token
        char token[1024];
        if (tokenLen > 1023)
            tokenLen = 1023;
        strncpy(token, text + start, tokenLen);
        token[tokenLen] = '\0';

        Vector2 size = MeasureTextEx(font, token, fontSize, spacing);

        // Logic to place token
        if (currentX + size.x <= maxWidth)
        {
            // Fits on current line
            DrawTextEx(font, token, (Vector2){(int)(textBounds.x + currentX), (int)(textBounds.y + currentY)}, fontSize, spacing, color);
            currentX += size.x;
        }
        else
        {
            // Doesn't fit. Try wrapping first.
            if (currentX > 0)
            {
                currentX = 0;
                currentY += fontSize;
            }

            // Check again on new line
            if (size.x <= maxWidth)
            {
                DrawTextEx(font, token, (Vector2){(int)(textBounds.x + currentX), (int)(textBounds.y + currentY)}, fontSize, spacing, color);
                currentX += size.x;
            }
            else
            {
                // Token too long even for empty line -> Break Word (Char by Char)
                for (int k = 0; k < tokenLen; k++)
                {
                    char cStr[2] = {token[k], '\0'};
                    Vector2 cSize = MeasureTextEx(font, cStr, fontSize, spacing);

                    if (currentX + cSize.x > maxWidth)
                    {
                        currentX = 0;
                        currentY += fontSize;
                    }

                    DrawTextEx(font, cStr, (Vector2){(int)(textBounds.x + currentX), (int)(textBounds.y + currentY)}, fontSize, spacing, color);
                    currentX += cSize.x;
                }
            }
        }
    }
}
