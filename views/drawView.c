#include "drawView.h"

void drawRootView(windowModel *window)
{
    switch (window->currWindow)
    {
    case HOME:
        drawHeader();
        drawHome(window);
        break;
    case LOGIN:
        break;
    }
}