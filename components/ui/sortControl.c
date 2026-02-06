#include "sortControl.h"
#include "../../libs/headers/raygui.h"

void DrawSortControl(windowModel *windowM, Vector2 pos)
{
    char suffix[50];

    switch (windowM->currWindow)
    {
    case STAFHOME:
        switch (windowM->selectedPage)
        {
        case MANAJERSTAFF:
        case PENGAJAR:
        case MURID:
            strcpy(suffix, "Tgl. Masuk");
            break;
        case PEMBAYARAN:
            strcpy(suffix, "Tgl. Pembayaran");
            break;
        case JADWAL:
            strcpy(suffix, "Waktu Jadwal");
            break;
        case RUANGAN:
            strcpy(suffix, "ID");
            break;
        case MAPEL:
            strcpy(suffix, "Nama Mapel");
            break;
        default:
            strcpy(suffix, "");
            break;
        }
        break;
    case PENGAJARHOME:
        switch (windowM->selectedPage)
        {
        case MATERI:
            strcpy(suffix, "ID");
            break;
        default:
            strcpy(suffix, "");
            break;
        }
        break;
    case MURIDHOME:
        switch (windowM->selectedPage)
        {
        case PEMBAYARANMURID:
            strcpy(suffix, "Tgl. Pembayaran");
            break;
        default:
            strcpy(suffix, "");
            break;
        }
        break;

    default:
        strcpy(suffix, "");
        break;
    }

    Vector2 leng = MeasureTextEx(windowM->fontStyle.regular, TextFormat("Urutkan %s:", suffix), 32, 0);
    Rectangle button = {.width = 160, .height = 50, .x = pos.x + leng.x + 5, .y = pos.y - 10};

    if (GuiButton(button, windowM->datas.sortBy == ASC ? "Terbawah" : "Teratas", 0))
    {
        switch (windowM->datas.sortBy)
        {
        case ASC:
            windowM->datas.sortBy = DESC;
            break;
        case DESC:
            windowM->datas.sortBy = ASC;
            break;
        }
        if (windowM->currWindow == STAFHOME)
            windowM->dataFetchers.staffPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, &windowM->authUser);
        if (windowM->currWindow == PENGAJARHOME)
            windowM->dataFetchers.pengajarPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, &windowM->authUser);
        if (windowM->currWindow == MURIDHOME)
            windowM->dataFetchers.muridPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, &windowM->authUser);
    }
    DrawTextEx(windowM->fontStyle.regular, TextFormat("Urutkan %s:", suffix), (Vector2){.x = pos.x, .y = pos.y}, 32, 0, SIBELAWHITE);
}