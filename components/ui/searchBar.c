#include "searchBar.h"
#include "../../libs/headers/raygui.h"

void drawSearchBar(windowModel *windowM, Vector2 position)
{
    Rectangle searchBarBound = {.x = position.x, .y = position.y, .width = 200, .height = 64};
    windowM->isKeyboardInterrupted = CheckCollisionPointRec(windowM->mousePosition, searchBarBound);
    GuiTextBox(searchBarBound, windowM->datas.searchString, 20, CheckCollisionPointRec(windowM->mousePosition, searchBarBound));

    Rectangle searchButton = {.x = searchBarBound.x + searchBarBound.width + 10, .y = searchBarBound.y, .height = 64, .width = 100};
    if (GuiButton(searchButton, "Cari", 0))
    {
        if (windowM->currWindow == STAFHOME)
            windowM->dataFetchers.staffPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, &windowM->authUser);
        else
            windowM->dataFetchers.pengajarPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, &windowM->authUser);
    }
    Rectangle clearButton = {.x = searchButton.x + searchButton.width + 10, .y = searchButton.y, .height = 64, .width = 64};
    if (GuiButton(clearButton, "X", 0))
    {
        strcpy(windowM->datas.searchString, "");
        if (windowM->currWindow == STAFHOME)
            windowM->dataFetchers.staffPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, &windowM->authUser);
        else
            windowM->dataFetchers.pengajarPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, &windowM->authUser);
    }
}