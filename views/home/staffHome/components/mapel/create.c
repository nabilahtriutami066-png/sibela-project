#include "create.h"
#include <math.h>
#include <string.h>

static void initMapelCreatePlaceholder(windowModel *windowM)
{
    static int initialized = 0;
    if (initialized) return;
    initialized = 1;

    FORM *form = &windowM->forms.staffPage[windowM->selectedPage];

    strcpy(form->fields[1].placeholder, "Contoh: Matematika");
}

void drawMapelCreate(windowModel *windowM)
{
    initMapelCreatePlaceholder(windowM);

    int start_x = 1920 / 2 - 600 + 100;
    int start_y = 1080 / 2 - 300;

    DrawTextEx(
        windowM->fontStyle.regular,
        "TAMBAH MAPEL",
        (Vector2){start_x + 390, start_y - 120},
        64, 0,
        SIBELAWHITE
    );

    FORM *form = &windowM->forms.staffPage[windowM->selectedPage];

    form->totalPages = (int)ceilf(
        (float)form->nField / form->fieldPerPage
    );

    form->offset =
        (windowM->page - 1) * form->fieldPerPage + 1;

    form->lastIndex =
        form->offset + (form->fieldPerPage - 1) > form->nField
            ? form->nField
            : form->offset + (form->fieldPerPage - 1);

    for (int i = form->offset; i <= form->lastIndex; i++)
    {
        Rectangle textBox = {
            1920 / 2.0f - 200,
            start_y + 300 + (i - 1 - form->offset) * 150,
            600,
            63
        };

        Rectangle buttonBox = {
            1920 / 2.0f + 20,
            start_y + 300 + (i - 1 - form->offset) * 150,
            160,
            67
        };

        switch (form->fields[i].type)
        {
        case TEXTINPUT:
            drawInputBox(
                windowM,
                &form->fields[i].value,
                textBox,
                form->fields[i].label,
                i,
                0
            );
            break;

        case BUTTONINPUT:
        {
            const char *label = form->fields[i].label;
            Vector2 textSize = MeasureTextEx(
                windowM->fontStyle.medium,
                label,
                40,
                0
            );

            if (
                (form->selectedField == -1 && windowM->curPos == i) ||
                form->selectedField == i
            )
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
                    buttonBox.x + buttonBox.width / 2 - textSize.x / 2,
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
