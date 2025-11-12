#include "update.h"

void updateView(windowModel *window)
{
    int ch = getch();
    switch (ch)
    {
    case 'w':
    case KEY_UP:
        window->curPos -= 1;
        break;
    case 's':
    case KEY_DOWN:
        window->curPos += 1;
        break;
    case 'q':
        window->shouldClose = 1;
        break;
    }
}