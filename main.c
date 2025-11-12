#include "libs/utils.h"
#include "model/model.h"
#include "update/update.h"
#include "views/drawView.h"

int main()
{
    windowModel defaultWindow = initWindow();

    while (!defaultWindow.shouldClose)
    {
        clear();
        refresh();
        drawRootView(&defaultWindow);
        updateView(&defaultWindow);
    }

    endwin();

    return 0;
}
