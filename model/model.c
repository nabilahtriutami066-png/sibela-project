#include "model.h"

windowModel initWindow()
{
    initscr();
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    wbkgd(stdscr, COLOR_PAIR(1));

    return (windowModel){
        .currWindow = HOME,
        .shouldClose = 0,
        .curPos = 0,
    };
}