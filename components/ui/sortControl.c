#include "sortControl.h"
#include "../../libs/headers/raygui.h"

void DrawSortControl(windowModel *windowM, Vector2 pos)
{
    Rectangle button = {.width = 120, .height = 50, .x = pos.x + 5, .y = pos.y};
    Vector2 leng = MeasureTextEx(windowM->fontStyle.regular, "Urutkan:", 20, 0);

    if (GuiButton(button, windowM->datas.sortBy == ASC ? "Teratas" : "Terbawah", 0))
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
        windowM->dataFetchers.staffPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, &windowM->authUser);
    }
    DrawTextEx(windowM->fontStyle.regular, "Urutkan:", (Vector2){.x = pos.x - leng.x - 5, .y = pos.y}, 20, 0, SIBELAWHITE);
}