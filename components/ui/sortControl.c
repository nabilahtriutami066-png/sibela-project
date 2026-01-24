#include "sortControl.h"
#include "../../libs/headers/raygui.h"

void DrawSortControl(windowModel *windowM, Vector2 pos)
{
    Vector2 leng = MeasureTextEx(windowM->fontStyle.regular, "Urutkan:", 32, 0);
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
    DrawTextEx(windowM->fontStyle.regular, "Urutkan:", (Vector2){.x = pos.x, .y = pos.y}, 32, 0, SIBELAWHITE);
}