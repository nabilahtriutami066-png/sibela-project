#include "update.h"

void updateView(windowModel *windowM)
{
    if (windowM->isLoading)
    {
        windowM->loadingTime += GetFrameTime();
        float progress = windowM->loadingTime / 2.0f;

        if (progress > 1.0f)
            progress = 1.0f;
        windowM->progress = progress;

        if (windowM->loadingTime >= 2.0f)
        {
            windowM->isLoading = false;
            windowM->currWindow = LANDINGPAGE;
        }

        return;
    }
    int ch = GetKeyPressed();
    switch (ch)
    {
    case KEY_ESCAPE:
        windowM->shouldClose = 1;
        break;
    case KEY_F2:
        windowM->currWindow = STAFHOME;
        break;
    case KEY_F3:
        windowM->currWindow = PENGAJARHOME;
    }
    switch (windowM->currWindow)
    {
    case STAFHOME:
        switch (ch)
        {
        case KEY_UP:
            windowM->curPos -= 1;
            break;
        case KEY_DOWN:
            windowM->curPos += 1;
            break;
        case KEY_TAB:
            if (windowM->activeSubWindow == READ)
            {
                windowM->cursorEnabled = 1;
                windowM->selectedPage = -1;
            }
            windowM->activeSubWindow = READ;
            windowM->curPos = 0;
            break;

        default:

            if (!windowM->cursorEnabled && windowM->activeSubWindow == CREATE)
            {
                switch (ch)
                {
                case KEY_RIGHT:
                    windowM->page++;
                    windowM->curPos = windowM->page * windowM->forms.staffPage[windowM->selectedPage].fieldPerPage - windowM->forms.staffPage[windowM->selectedPage].fieldPerPage + 1;
                    break;
                case KEY_LEFT:
                    windowM->page--;
                    windowM->curPos = windowM->page * windowM->forms.staffPage[windowM->selectedPage].fieldPerPage - windowM->forms.staffPage[windowM->selectedPage].fieldPerPage + 1;
                    break;
                default:
                    int selectedPage = windowM->selectedPage;
                    int curPos = windowM->curPos;
                    handleInput(&ch, &windowM->forms.staffPage[selectedPage].fields[curPos].value.charLen, windowM->forms.staffPage[selectedPage].fields[curPos].value.text, windowM->forms.staffPage[selectedPage].fields[curPos].type, 100, windowM->forms.staffPage[selectedPage].createFunc, windowM->forms.staffPage[selectedPage].fields, windowM->dataFetchers.admin[selectedPage], windowM);

                    break;
                }
            }
            if (!windowM->cursorEnabled && windowM->activeSubWindow == UPDATE)
            {
                switch (ch)
                {
                case KEY_RIGHT:
                    windowM->page++;
                    windowM->curPos = windowM->page * windowM->forms.staffPage[windowM->selectedPage].fieldPerPage - windowM->forms.staffPage[windowM->selectedPage].fieldPerPage + 1;
                    break;
                case KEY_LEFT:
                    windowM->page--;
                    windowM->curPos = windowM->page * windowM->forms.staffPage[windowM->selectedPage].fieldPerPage - windowM->forms.staffPage[windowM->selectedPage].fieldPerPage + 1;
                    break;
                default:
                    int selectedPage = windowM->selectedPage;
                    int curPos = windowM->curPos;
                    handleInput(&ch, &windowM->forms.staffPage[selectedPage].fields[curPos].value.charLen, windowM->forms.staffPage[selectedPage].fields[curPos].value.text, windowM->forms.staffPage[selectedPage].fields[curPos].type, 100, windowM->forms.staffPage[selectedPage].updateFunction, windowM->forms.staffPage[selectedPage].fields, windowM->dataFetchers.admin[selectedPage], windowM);

                    break;
                }
            }
            if (!windowM->cursorEnabled && windowM->activeSubWindow == READ)
            {
                switch (ch)
                {
                case KEY_N:
                    windowM->activeSubWindow = CREATE;
                    windowM->page = 1;
                    windowM->curPos = 1;
                    break;
                case KEY_RIGHT:
                    if (windowM->datas.page < windowM->datas.totalPages)
                    {
                        windowM->datas.page++;
                        windowM->curPos = 0;
                        windowM->dataFetchers.admin[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn);
                    }
                    break;
                case KEY_D:
                    windowM->isModalShown = 1;
                    break;
                case KEY_U:
                    switch (windowM->selectedPage)
                    {
                    case STAFF:
                        copyStringData(windowM->focusedData.staff.id_staff, &windowM->forms.staffPage[STAFF].fields[0].value);
                        copyStringData(windowM->focusedData.staff.nama, &windowM->forms.staffPage[STAFF].fields[1].value);
                        copyStringData(windowM->focusedData.staff.tanggal_lahir, &windowM->forms.staffPage[STAFF].fields[2].value);
                        copyStringData(windowM->focusedData.staff.no_hp, &windowM->forms.staffPage[STAFF].fields[3].value);
                        copyStringData(windowM->focusedData.staff.password, &windowM->forms.staffPage[STAFF].fields[4].value);
                        copyStringData(windowM->focusedData.staff.email, &windowM->forms.staffPage[STAFF].fields[5].value);
                        break;
                    case MURID:
                        char tingkatBuff[4];
                        sprintf(tingkatBuff, "%d", windowM->focusedData.murid.tingkat);
                        copyStringData(windowM->focusedData.murid.id_murid, &windowM->forms.staffPage[MURID].fields[0].value);
                        copyStringData(windowM->focusedData.murid.nama, &windowM->forms.staffPage[MURID].fields[1].value);
                        copyStringData(windowM->focusedData.murid.tanggal_lahir, &windowM->forms.staffPage[MURID].fields[2].value);
                        copyStringData(windowM->focusedData.murid.no_hp, &windowM->forms.staffPage[MURID].fields[3].value);
                        copyStringData(windowM->focusedData.murid.password, &windowM->forms.staffPage[MURID].fields[4].value);
                        copyStringData(tingkatBuff, &windowM->forms.staffPage[MURID].fields[5].value);
                        break;
                    case PENGAJAR:
                        copyStringData(windowM->focusedData.pengajar.id_pengajar, &windowM->forms.staffPage[PENGAJAR].fields[0].value);
                        copyStringData(windowM->focusedData.pengajar.nama, &windowM->forms.staffPage[PENGAJAR].fields[1].value);
                        copyStringData(windowM->focusedData.pengajar.tanggal_lahir, &windowM->forms.staffPage[PENGAJAR].fields[2].value);
                        copyStringData(windowM->focusedData.pengajar.no_hp, &windowM->forms.staffPage[PENGAJAR].fields[3].value);
                        copyStringData(windowM->focusedData.pengajar.password, &windowM->forms.staffPage[PENGAJAR].fields[4].value);
                        break;
                    case RUANGAN:
                        copyStringData(windowM->focusedData.ruangan.id_ruangan, &windowM->forms.staffPage[RUANGAN].fields[0].value);
                        copyStringData(windowM->focusedData.ruangan.lokasi, &windowM->forms.staffPage[RUANGAN].fields[1].value);
                        copyStringData(windowM->focusedData.ruangan.deskripsi, &windowM->forms.staffPage[RUANGAN].fields[2].value);
                        break;
                    case MAPEL:
                        copyStringData(windowM->focusedData.mapel.id_mapel, &windowM->forms.staffPage[MAPEL].fields[0].value);
                        copyStringData(windowM->focusedData.mapel.nama_mapel, &windowM->forms.staffPage[MAPEL].fields[1].value);
                        break;
                    }
                    windowM->activeSubWindow = UPDATE;
                    windowM->page = 1;
                    windowM->curPos = 1;
                    break;
                case KEY_LEFT:
                    if (windowM->datas.page > 1)
                    {
                        windowM->datas.page--;
                        windowM->curPos = 0;
                        windowM->dataFetchers.admin[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn);
                    }
                    break;
                }
            }

            if (windowM->cursorEnabled)
            {
                switch (ch)
                {
                case KEY_ENTER:

                    if (windowM->curPos == 7)
                    {
                        logoutFunction(windowM);
                        return;
                    }
                    windowM->dataFetchers.admin[windowM->curPos](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn);
                    windowM->selectedPage = windowM->curPos;
                    windowM->datas.page = 1;
                    windowM->curPos = 0;
                    windowM->cursorEnabled = 0;
                    break;
                }
            }
            break;
        }
        break;
    case PENGAJARHOME:
        switch (ch)
        {
        case KEY_W:
        case KEY_UP:
            windowM->curPos -= 1;
            break;
        case KEY_S:
        case KEY_DOWN:
            windowM->curPos += 1;
            break;

        case KEY_TAB:
            windowM->cursorEnabled = 1;
            windowM->activeSubWindow = READ;
            windowM->selectedPage = -1;
            windowM->curPos = 0;
            break;
        case KEY_SPACE:
        case KEY_ENTER:
            // windowM->dataFetchers.admin[windowM->curPos](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn);
            if (windowM->curPos == 3)
            {
                logoutFunction(windowM);
                return;
            }
            windowM->selectedPage = windowM->curPos;
            windowM->curPos = 0;
            windowM->cursorEnabled = 0;
            break;
        }
        break;
    case MURIDHOME:
        switch (ch)
        {
        case KEY_W:
        case KEY_UP:
            windowM->curPos -= 1;
            break;
        case KEY_S:
        case KEY_DOWN:
            windowM->curPos += 1;
            break;

        case KEY_TAB:
            windowM->cursorEnabled = 1;
            windowM->selectedPage = -1;
            windowM->curPos = 0;
            break;
        case KEY_SPACE:
        case KEY_ENTER:
            // windowM->dataFetchers.admin[windowM->curPos](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn);
            if (windowM->curPos == 3)
            {
                logoutFunction(windowM);
                return;
            }
            windowM->selectedPage = windowM->curPos;
            windowM->curPos = 0;
            windowM->cursorEnabled = 0;
            break;
        }
        break;
    case LOGINSTAFF:
        switch (ch)
        {
        case KEY_TAB:
            break;

        case KEY_DOWN:
            windowM->loginData.activeInput++;
            break;
        case KEY_UP:
            windowM->loginData.activeInput--;
            break;

        default:
            switch (windowM->loginData.activeInput)
            {
            case 0:
                handleInput(&ch, &windowM->loginData.email.charLen, windowM->loginData.email.text, TEXTINPUT, 100, NULL, NULL, NULL, windowM);
                break;
            case 1:
                handleInput(&ch, &windowM->loginData.password.charLen, windowM->loginData.password.text, TEXTINPUT, 100, NULL, NULL, NULL, windowM);
                break;
            case 2:
                switch (ch)
                {
                case KEY_ENTER:
                    loginFunction(windowM);
                    break;
                }
                break;
            }
            break;
        }
        break;
    case LOGINPENGAJAR:
    case LOGINMURID:
        switch (ch)
        {
        case KEY_TAB:
            break;

        case KEY_DOWN:
            windowM->loginData.activeInput++;
            break;
        case KEY_UP:
            windowM->loginData.activeInput--;
            break;

        default:
            switch (windowM->loginData.activeInput)
            {
            case 0:
                handleInput(&ch, &windowM->loginData.phoneNumber.charLen, windowM->loginData.phoneNumber.text, NUMERICINPUT, 15, NULL, NULL, NULL, windowM);
                break;
            case 1:
                handleInput(&ch, &windowM->loginData.password.charLen, windowM->loginData.password.text, TEXTINPUT, 100, NULL, NULL, NULL, windowM);
                break;
            case 2:
                switch (ch)
                {
                case KEY_ENTER:
                    loginFunction(windowM);
                    break;
                }
                break;
            }
            break;
        }
        break;
    case LANDINGPAGE:
        switch (ch)
        {
        case KEY_UP:
            windowM->curPos -= 1;
            break;
        case KEY_DOWN:
            windowM->curPos += 1;
            break;
        case KEY_ENTER:
            windowM->currWindow = windowM->navigation.landingPage[windowM->curPos].targetPage;
            windowM->curPos = 0;
            break;
        }
        break;
    case CONTRIBPAGE:
        switch (ch)
        {
        case KEY_LEFT:
            if (windowM->page > 1)
                windowM->page--;
            break;
        case KEY_RIGHT:
            if (windowM->page < 5)
                windowM->page++;
            break;
        case KEY_TAB:
            windowM->currWindow = LANDINGPAGE;
            windowM->page = 1;
            break;
        }
        break;
    }
}