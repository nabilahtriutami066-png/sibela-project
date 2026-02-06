#include "handleInput.h"

void handleInput(int *ch, InputParams *params, InputType fieldType, int maxLen, mutationFunc func, InputField fields[], fetcherFunc dataFetcher, windowModel *windowM)
{

    switch (fieldType)
    {
    case DATEINPUT:
    case BIRTHDATEINPUT:
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
    default:
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
    case PHONENOINPUT:
    case TINGKATINPUT:
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
                copyStringData(windowM->selectByPage.pengajarPage[windowM->selectedPage].selected.value, &windowM->forms.pengajarPage[windowM->selectedPage].fields[1].value);
                windowM->selectByPage.pengajarPage[windowM->selectedPage].selected = (SelectProp){};
            }
            if (windowM->currWindow == STAFHOME && windowM->selectedPage == JADWAL)
            {
                copyStringData(windowM->selectByPage.staffPage[windowM->selectedPage][1].selected.value, &windowM->forms.staffPage[windowM->selectedPage].fields[1].value);
                windowM->selectByPage.staffPage[windowM->selectedPage][1].selected = (SelectProp){};
                copyStringData(windowM->selectByPage.staffPage[windowM->selectedPage][2].selected.value, &windowM->forms.staffPage[windowM->selectedPage].fields[2].value);
                windowM->selectByPage.staffPage[windowM->selectedPage][2].selected = (SelectProp){};
                copyStringData(windowM->selectByPage.staffPage[windowM->selectedPage][3].selected.value, &windowM->forms.staffPage[windowM->selectedPage].fields[3].value);
                windowM->selectByPage.staffPage[windowM->selectedPage][3].selected = (SelectProp){};
                for (int i = 0; i < windowM->selectByPage.staffPage[windowM->selectedPage][5].nMultiSelected; i++)
                {
                    strcpy(windowM->forms.staffPage[windowM->selectedPage].fields[5].value.multiValue[i], windowM->selectByPage.staffPage[windowM->selectedPage][5].MultiSelected[i].value);
                }
                windowM->forms.staffPage[windowM->selectedPage].fields[5].value.charLen = windowM->selectByPage.staffPage[windowM->selectedPage][5].nMultiSelected;
            }
            if (windowM->currWindow == STAFHOME && windowM->selectedPage == PEMBAYARAN)
            {
                copyStringData(windowM->authUser.id, &windowM->forms.staffPage[windowM->selectedPage].fields[0].value);
                copyStringData(windowM->selectByPage.staffPage[windowM->selectedPage][1].selected.value, &windowM->forms.staffPage[windowM->selectedPage].fields[1].value);
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
                QUERYSTATUS resQuery = func(fields, windowM->dbConn, &windowM->authUser);
                if (resQuery == FAILED)
                {
                    showToast(&windowM->toast, "Kesalahan", "Terjadi kesalahan saat submit form!");
                    return;
                }
                else
                {
                    dataFetcher(&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, NULL);
                    clearFields(fields);
                    windowM->activeSubWindow = READ;
                }
            }
            break;
        }
        break;
    }
}