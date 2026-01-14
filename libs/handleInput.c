#include "handleInput.h"

void handleInput(int *ch, InputParams *params, InputType fieldType, int maxLen, mutationFunc func, InputField fields[], fetcherFunc dataFetcher, windowModel *windowM)
{

    switch (fieldType)
    {
    case DATEINPUT:
        *ch = GetCharPressed();
        while (*ch > 0)
        {
            if ((((*ch >= '0') && (*ch <= '9')) || *ch == '-' || *ch == ':') && (params->charLen < maxLen))
            {
                if (params->validation.isInputInvalid)
                {
                    params->validation.isInputInvalid = false;
                    strcpy(params->validation.errMessage, "");
                }
                params->text[params->charLen] = (char)*ch;
                params->text[(params->charLen) + 1] = '\0';
                (params->charLen)++;
            }

            *ch = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            (params->charLen)--;
            if ((params->charLen) < 0)
                (params->charLen) = 0;
            params->text[params->charLen] = '\0';
        }
        break;
    case LONGTEXTINPUT:
    case EMAILINPUT:
    case TEXTINPUT:
        *ch = GetCharPressed();
        while (*ch > 0)
        {
            if ((*ch >= 32) && (*ch <= 125) && (params->charLen < maxLen))
            {
                if (params->validation.isInputInvalid)
                {
                    params->validation.isInputInvalid = false;
                    strcpy(params->validation.errMessage, "");
                }
                params->text[params->charLen] = (char)*ch;
                params->text[(params->charLen) + 1] = '\0';
                (params->charLen)++;
            }

            *ch = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            (params->charLen)--;
            if ((params->charLen) < 0)
                (params->charLen) = 0;
            params->text[params->charLen] = '\0';
        }
        break;
    case NUMERICINPUT:
        *ch = GetCharPressed();
        while (*ch > 0)
        {
            if ((*ch >= '0') && (*ch <= '9') && (params->charLen < maxLen))
            {
                if (params->validation.isInputInvalid)
                {
                    params->validation.isInputInvalid = false;
                    strcpy(params->validation.errMessage, "");
                }
                params->text[params->charLen] = (char)*ch;
                params->text[(params->charLen) + 1] = '\0';
                (params->charLen)++;
            }

            *ch = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            (params->charLen)--;
            if ((params->charLen) < 0)
                (params->charLen) = 0;
            params->text[params->charLen] = '\0';
        }
        break;
    case BUTTONINPUT:
        switch (*ch)
        {
        case KEY_ENTER:
            if (windowM->currWindow == PENGAJARHOME && windowM->selectedPage == MATERI)
            {
                strcpy(windowM->forms.pengajarPage[windowM->selectedPage].fields[1].value.text, windowM->selectByPage.pengajarPage[windowM->selectedPage].selected.value);
                windowM->selectByPage.pengajarPage[windowM->selectedPage].selected = (SelectProp){};
            }
            if (windowM->currWindow == STAFHOME && windowM->selectedPage == JADWAL)
            {
                strcpy(windowM->forms.staffPage[windowM->selectedPage].fields[2].value.text, windowM->selectByPage.staffPage[windowM->selectedPage][2].selected.value);
                windowM->selectByPage.staffPage[windowM->selectedPage][2].selected = (SelectProp){};
                strcpy(windowM->forms.staffPage[windowM->selectedPage].fields[3].value.text, windowM->selectByPage.staffPage[windowM->selectedPage][3].selected.value);
                windowM->selectByPage.staffPage[windowM->selectedPage][3].selected = (SelectProp){};
                strcpy(windowM->forms.staffPage[windowM->selectedPage].fields[4].value.text, windowM->selectByPage.staffPage[windowM->selectedPage][4].selected.value);
                windowM->selectByPage.staffPage[windowM->selectedPage][4].selected = (SelectProp){};
                for (int i = 0; i < windowM->selectByPage.staffPage[windowM->selectedPage][6].nMultiSelected; i++)
                {
                    strcpy(windowM->forms.staffPage[windowM->selectedPage].fields[6].value.multiValue[i], windowM->selectByPage.staffPage[windowM->selectedPage][6].MultiSelected[i].value);
                }
                windowM->forms.staffPage[windowM->selectedPage].fields[6].value.charLen = windowM->selectByPage.staffPage[windowM->selectedPage][6].nMultiSelected;
            }
            if (windowM->currWindow == STAFHOME && windowM->selectedPage == PEMBAYARAN)
            {
                strcpy(windowM->forms.staffPage[windowM->selectedPage].fields[0].value.text, windowM->authUser.id);
                strcpy(windowM->forms.staffPage[windowM->selectedPage].fields[1].value.text, windowM->selectByPage.staffPage[windowM->selectedPage][1].selected.value);
                windowM->selectByPage.staffPage[windowM->selectedPage][1].selected = (SelectProp){};
            }
            if (func != NULL && dataFetcher != NULL)
            {
                int valid = 1;
                for (int i = 1; i < windowM->forms.staffPage[windowM->selectedPage].nField; i++)
                {
                    valid = valid && validateInput(&fields[i]);
                }
                if (!valid)
                {
                    showToast(&windowM->toast, "Input tidak valid!", "Silahkan cek lagi data yang anda masukkan!");
                    return;
                }
                func(fields, windowM->dbConn);
                dataFetcher(&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, NULL);
            }
            clearFields(fields);

            windowM->activeSubWindow = READ;
            break;
        }
        break;
    }
}