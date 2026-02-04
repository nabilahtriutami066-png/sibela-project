#include "create.h"
#include <math.h>
#include <string.h>

/* =========================
   PLACEHOLDER PENGAJAR (SHARED)
   ========================= */
static void initPengajarPlaceholder(FORM *form)
{
    strcpy(form->fields[1].placeholder, "ex: Budi Santoso");
    strcpy(form->fields[2].placeholder, "YYYY-MM-DD");
    strcpy(form->fields[3].placeholder, "ex: 081234567890");
    strcpy(form->fields[4].placeholder, "ex: email@mail.com");
}


static void initPengajarCreatePlaceholder(windowModel *windowM)
{
    FORM *form = &windowM->forms.staffPage[windowM->selectedPage];
    initPengajarPlaceholder(form);
}

// /* =========================
//    DRAW UPDATE PENGAJAR
//    ========================= */
// void drawPengajarCreate(windowModel *windowM)
// {
//     static bool initialized = false;
//     if (!initialized)
//     {
//         initPengajarUpdatePlaceholder(windowM);
//         initialized = true;
//     }

//     int start_x = 1920 / 2 - 600 + 100;
//     int start_y = 1080 / 2 - 300;

//     DrawTextEx(
//         windowM->fontStyle.regular,
//         "UBAH PENGAJAR",
//         (Vector2){start_x + 390, start_y - 120},
//         64, 0,
//         SIBELAWHITE
//     );

//     FORM *form = &windowM->forms.staffPage[windowM->selectedPage];

//     form->totalPages = (int)ceilf((float)form->nField / form->fieldPerPage);
//     form->offset = (windowM->page - 1) * form->fieldPerPage + 1;
//     form->lastIndex = form->offset + form->fieldPerPage - 1;
//     if (form->lastIndex > form->nField)
//         form->lastIndex = form->nField;

//     for (int i = form->offset; i <= form->lastIndex; i++)
//     {
//         InputField *field = &form->fields[i];

//         float posY = start_y + 200 + (i - form->offset) * 150;

//         Rectangle textBox = {1920 / 2.0f - 200, posY, 600, 63};
//         Rectangle buttonBox = {1920 / 2.0f + 20, posY, 160, 67};

//         switch (field->type)
//         {
//         case BUTTONINPUT:
//         {
//             Vector2 textSize = MeasureTextEx(
//                 windowM->fontStyle.medium,
//                 field->label,
//                 40, 0
//             );

//             if (windowM->curPos == i)
//                 DrawRectangleRounded(buttonBox, 0.3f, 0, PRIMARY);
//             else
//                 DrawRectangleRoundedLines(buttonBox, 0.3f, 0, SIBELAWHITE);

//             DrawTextEx(
//                 windowM->fontStyle.medium,
//                 field->label,
//                 (Vector2){
//                     buttonBox.x + buttonBox.width / 2 - textSize.x / 2,
//                     buttonBox.y + buttonBox.height / 2 - textSize.y / 2},
//                 40, 0, SIBELAWHITE
//             );
//         }
//         break;

//         default:
//         {
//             drawInputBox(
//                 windowM,
//                 &field->value,
//                 textBox,
//                 field->label,
//                 i,
//                 0
//             );

//             if (field->value.charLen == 0 && strlen(field->placeholder) > 0)
//             {
//                 DrawTextEx(
//                     windowM->fontStyle.regular,
//                     field->placeholder,
//                     (Vector2){
//                         textBox.x + 12,
//                         textBox.y + (textBox.height / 2) - 12},
//                     24, 0, Fade(GRAY, 0.45f)
//                 );
//             }
//         }
//         break;
//         }
//     }
// }

void drawPengajarCreate(windowModel *windowM)
{
    static bool initialized = false;
    if (!initialized)
    {
        initPengajarCreatePlaceholder(windowM);
        initialized = true;
    }

    int start_x = 1920 / 2 - 600 + 100;
    int start_y = 1080 / 2 - 300;

    DrawTextEx(
        windowM->fontStyle.regular,
        "TAMBAH PENGAJAR",
        (Vector2){start_x + 360, start_y - 120},
        64, 0,
        SIBELAWHITE
    );

    FORM *form = &windowM->forms.staffPage[windowM->selectedPage];

    form->totalPages = (int)ceilf((float)form->nField / form->fieldPerPage);
    form->offset = (windowM->page - 1) * form->fieldPerPage + 1;
    form->lastIndex = form->offset + form->fieldPerPage - 1;
    if (form->lastIndex > form->nField)
        form->lastIndex = form->nField;

    for (int i = form->offset; i <= form->lastIndex; i++)
    {
        InputField *field = &form->fields[i];

        float posY = start_y + 100 + (i - form->offset) * 150;

        Rectangle textBox = {1920 / 2.0f - 200, posY, 600, 63};
        Rectangle buttonBox = {1920 / 2.0f + 20, posY, 160, 67};

        switch (field->type)
        {
        case BUTTONINPUT:
        {
            Vector2 textSize = MeasureTextEx(
                windowM->fontStyle.medium,
                field->label,
                40, 0
            );

            if (windowM->curPos == i)
                DrawRectangleRounded(buttonBox, 0.3f, 0, PRIMARY);
            else
                DrawRectangleRoundedLines(buttonBox, 0.3f, 0, SIBELAWHITE);

            DrawTextEx(
                windowM->fontStyle.medium,
                field->label,
                (Vector2){
                    buttonBox.x + buttonBox.width / 2 - textSize.x / 2,
                    buttonBox.y + buttonBox.height / 2 - textSize.y / 2},
                40, 0, SIBELAWHITE
            );
        }
        break;

        default:
        {
            drawInputBox(
                windowM,
                &field->value,
                textBox,
                field->label,
                i,
                0
            );

            if (field->value.charLen == 0 && strlen(field->placeholder) > 0)
            {
                DrawTextEx(
                    windowM->fontStyle.regular,
                    field->placeholder,
                    (Vector2){
                        textBox.x + 12,
                        textBox.y + (textBox.height / 2) - 12},
                    24, 0, Fade(GRAY, 0.45f)
                );
            }
        }
        break;
        }
    }
}
