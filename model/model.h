#ifndef model
#define model

#include <stdio.h>
#include <ncurses.h>

const int width = 100;
const int height = 19;

typedef enum
{
    HOME,
    LOGIN,
} WINDOWS;

typedef struct
{
    WINDOWS currWindow;
    int shouldClose;
    int curPos;
} windowModel;

windowModel initWindow(void);

#endif