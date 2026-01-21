#include "update.h"
#include <math.h>

void drawRuanganUpdate(windowModel *windowM)
{
    int cell_width = 250;
    int cell_height = 50;
    int start_x = 1920 / 2 - 600 + 100;
    int start_y = 1080 / 2 - 300;
    int padding = 5;
    int font_size = 32;
    DrawTextEx(windowM->fontStyle.regular, "UBAH RUANGAN",
               (Vector2){start_x + 390,
                         start_y - 120},
               64, 0,
               SIBELAWHITE);

    windowM->forms.staffPage[windowM->selectedPage].totalPages = (int)ceilf((float)windowM->forms.staffPage[windowM->selectedPage].nField / windowM->forms.staffPage[windowM->selectedPage].fieldPerPage);
    windowM->forms.staffPage[windowM->selectedPage].offset = (windowM->page - 1) * windowM->forms.staffPage[windowM->selectedPage].fieldPerPage + 1;
    windowM->forms.staffPage[windowM->selectedPage].lastIndex = windowM->forms.staffPage[windowM->selectedPage].offset + (windowM->forms.staffPage[windowM->selectedPage].fieldPerPage - 1) > windowM->forms.staffPage[windowM->selectedPage].nField ? windowM->forms.staffPage[windowM->selectedPage].nField : windowM->forms.staffPage[windowM->selectedPage].offset + (windowM->forms.staffPage[windowM->selectedPage].fieldPerPage - 1);

    for (int i = windowM->forms.staffPage[windowM->selectedPage].offset; i <= windowM->forms.staffPage[windowM->selectedPage].lastIndex; i++)
    {
        Rectangle textBox = {
            1920 / 2.0f - 300,
            start_y + 100 + (i - 1 - windowM->forms.staffPage[windowM->selectedPage].offset) * 150,
            600,
            63,
        };
        Rectangle buttonBox = {
            1920 / 2.0f - 80,
            start_y + 100 + (i - 1 - windowM->forms.staffPage[windowM->selectedPage].offset) * 150,
            160,
            67,
        };
        switch (windowM->forms.staffPage[windowM->selectedPage].fields[i].type)
        {
        default:
            drawInputBox(windowM, &windowM->forms.staffPage[windowM->selectedPage].fields[i].value, textBox, windowM->forms.staffPage[windowM->selectedPage].fields[i].label, i, 0);
            break;

        case BUTTONINPUT:
        {
        const char *label =
        windowM->forms.staffPage[windowM->selectedPage].fields[i].label;

        Vector2 textSize = MeasureTextEx(
        windowM->fontStyle.medium,
        label,
        40,
        0
        );

        if (windowM->curPos == i)
        {
            DrawRectangleRounded(buttonBox, 0.3f, 0, PRIMARY);
        }
        else
        {
            DrawRectangleRoundedLines(buttonBox, 0.3f, 0, SIBELAWHITE);
        }

        DrawTextEx(
        windowM->fontStyle.medium,
        label,
        (Vector2){
            buttonBox.x + buttonBox.width  / 2 - textSize.x / 2,
            buttonBox.y + buttonBox.height / 2 - textSize.y / 2
        },
        40,
        0,
        SIBELAWHITE
        );
        }
        break;
        }
    }
}