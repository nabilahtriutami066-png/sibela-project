#include "homeView.h"

void drawHome(windowModel *window)
{
    char options[3][15] = {"admin", "pelajar", "wikwok"};

    WINDOW *menus = newwin(5, 15, LINES - 10, COLS / 2 - 7);
    wborder(menus, '|', '|', '-', '-', '+', '+', '+', '+');

    for (int i = 0; i < sizeof(options) / sizeof(options[0]); i++)
    {
        if (window->curPos == i)
        {
            wattron(menus, COLOR_PAIR(2));
        }
        mvwprintw(menus, i + 1, 2, options[i]);
        wattroff(menus, COLOR_PAIR(2));
    }

    wrefresh(menus);
}
