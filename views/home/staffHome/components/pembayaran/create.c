#include "create.h"
#include <math.h>

void drawPembayaranCreate(windowModel *windowM)
{
    int cell_width = 250;
    int cell_height = 50;
    int start_x = 1920 / 2 - 600 + 100;
    int start_y = 1080 / 2 - 300;
    int padding = 5;
    int font_size = 32;
    DrawTextEx(windowM->fontStyle.regular, "CREATE PEMBAYARAN",
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
            start_y + 200 + (i - 1 - windowM->forms.staffPage[windowM->selectedPage].offset) * 150,
            600,
            63,
        };
        Rectangle buttonBox = {
            1920 / 2.0f - 80,
            start_y + 200 + (i - 1 - windowM->forms.staffPage[windowM->selectedPage].offset) * 150,
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
        
        case CUSTOMMODAL:
            DrawTextEx(windowM->fontStyle.medium, windowM->forms.staffPage[windowM->selectedPage].fields[i].label, (Vector2){(int)buttonBox.x, (int)buttonBox.y - 45}, 40, 0, SIBELAWHITE);
            if (windowM->curPos == i)
            {
                DrawRectangleRounded(buttonBox, 0.3, 0, PRIMARY);
            }
            else
                DrawRectangleRoundedLines(buttonBox, 0.3, 0, SIBELAWHITE);
            DrawTextEx(windowM->fontStyle.medium, "PILIH", (Vector2){(int)buttonBox.x + buttonBox.width / 2 - MeasureTextEx(windowM->fontStyle.medium, "PILIH", 40, 0).x / 2, (int)buttonBox.y + MeasureTextEx(windowM->fontStyle.medium, "PILIH", 40, 0).y / 2 - 8}, 40, 0, SIBELAWHITE);
            if (!TextIsEqual(windowM->selectByPage.staffPage[windowM->selectedPage][i].selected.value, ""))
                DrawTextEx(windowM->fontStyle.regular, TextFormat("Tepilih: %s", windowM->selectByPage.staffPage[windowM->selectedPage][i].selected.label), (Vector2){(int)buttonBox.x + buttonBox.width + 20, (int)buttonBox.y + MeasureTextEx(windowM->fontStyle.regular, "PILIH", 32, 0).y / 2}, 32, 0, SIBELAWHITE);
            break;
        }
    }
    if (windowM->forms.staffPage[windowM->selectedPage].selectedField >= 0)
    {
        Rectangle ModalBox = (Rectangle){.width = 800, .height = 600, .x = 300 + 1620 / 2 - 400, .y = 1080 / 2 - 300};
        DrawRectangleRounded(ModalBox, 0.3, 0, SECONDARY);
        for (int i = 0; i < windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].nOptions; i++)
        {
            SelectProp props = windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].Options[i];
            char *text = TextFormat("%d. %s", (windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].page - 1) * 10 + i + 1, props.label);
            Vector2 textMeasure = MeasureTextEx(windowM->fontStyle.regular, text, 25, 0);
            int padding = 40;
            Rectangle selectbg = (Rectangle){.width = 10 + textMeasure.x, .height = 4 + textMeasure.y, .x = (int)ModalBox.x + padding - 5, (int)ModalBox.y + padding + i * 40 - 2};

            if (windowM->curPos == i)
                DrawRectangleRounded(selectbg, 0.3, 0, PRIMARY);

            if (TextIsEqual(props.value, windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].selected.value))
                DrawCircle(ModalBox.x + padding + textMeasure.x + 20, (int)ModalBox.y + padding + i * 40 + textMeasure.y / 2, 8, GREEN);

            DrawTextEx(windowM->fontStyle.regular, text, (Vector2){(int)ModalBox.x + padding, (int)ModalBox.y + padding + i * 40}, 25, 0, SIBELAWHITE);
        }
    }
}