#include "./dateRange.h"
#include "../../libs/headers/raygui.h"

void dateRangeSelector(windowModel *windowM, Vector2 position)
{
    struct tm *now = localtime(&windowM->time);
    Rectangle fromMonth = {.height = 40, .width = 60, .x = position.x, .y = position.y};
    // if (GuiDropdownBox(fromMonth, "#01#Januari;#02#Februari", &windowM->datas.dateRange.selected, windowM->datas.dateRange.isEditing))
    // {
    //     windowM->datas.dateRange.isEditing = !windowM->datas.dateRange.isEditing;
    // }
    if (GuiButton(fromMonth, TextFormat("%d", windowM->datas.dateRange.monthFrom), 0))
    {
        if (windowM->datas.dateRange.yearFrom <= now->tm_year + 1900)
        {
            if (windowM->datas.dateRange.monthFrom < 12)
                windowM->datas.dateRange.monthFrom++;
            else
                windowM->datas.dateRange.monthFrom = 1;
        }
        else
        {
            if (windowM->datas.dateRange.monthFrom < now->tm_mon + 1)
                windowM->datas.dateRange.monthFrom++;
            else
                windowM->datas.dateRange.monthFrom = 1;
        }
        windowM->dataFetchers.staffPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, &windowM->authUser);
    }
    Rectangle fromYearMin = {.height = 40, .width = 40, .x = position.x + 70, .y = position.y};
    if (GuiButton(fromYearMin, "-", 0))
    {
        windowM->datas.dateRange.yearFrom--;
        windowM->dataFetchers.staffPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, &windowM->authUser);
    }
    Rectangle fromYear = {.height = 40, .width = 100, .x = position.x + 120, .y = position.y};
    if (GuiButton(fromYear, TextFormat("%d", windowM->datas.dateRange.yearFrom), 0))
    {
    }
    Rectangle fromYearPlus = {.height = 40, .width = 40, .x = position.x + 230, .y = position.y};
    if (GuiButton(fromYearPlus, "+", 0))
    {
        if (windowM->datas.dateRange.yearFrom < now->tm_year + 1900)
            windowM->datas.dateRange.yearFrom++;

        windowM->dataFetchers.staffPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, &windowM->authUser);
    }

    Rectangle toMonth = {.height = 40, .width = 60, .x = position.x, .y = position.y + 100};
    if (GuiButton(toMonth, TextFormat("%d", windowM->datas.dateRange.monthTo), 0))
    {
        if (windowM->datas.dateRange.yearFrom <= now->tm_year + 1900)
        {
            if (windowM->datas.dateRange.monthTo < 12)
                windowM->datas.dateRange.monthTo++;
            else
                windowM->datas.dateRange.monthTo = 1;
        }
        else
        {
            if (windowM->datas.dateRange.monthTo < now->tm_mon + 1)
                windowM->datas.dateRange.monthTo++;
            else
                windowM->datas.dateRange.monthTo = 1;
        }
        windowM->dataFetchers.staffPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, &windowM->authUser);
    }
    Rectangle toyearMin = {.height = 40, .width = 40, .x = position.x + 70, .y = position.y + 100};
    if (GuiButton(toyearMin, "-", 0))
    {
        if (windowM->datas.dateRange.yearFrom < windowM->datas.dateRange.yearTo)
            windowM->datas.dateRange.yearTo--;
        windowM->dataFetchers.staffPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, &windowM->authUser);
    }
    Rectangle toYear = {.height = 40, .width = 100, .x = position.x + 120, .y = position.y + 100};
    if (GuiButton(toYear, TextFormat("%d", windowM->datas.dateRange.yearTo), 0))
    {
    }
    Rectangle toYearPlus = {.height = 40, .width = 40, .x = position.x + 230, .y = position.y + 100};
    if (GuiButton(toYearPlus, "+", 0))
    {
        if (windowM->datas.dateRange.yearTo < now->tm_year + 1900)
            windowM->datas.dateRange.yearTo++;
        windowM->dataFetchers.staffPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, &windowM->authUser);
    }
}