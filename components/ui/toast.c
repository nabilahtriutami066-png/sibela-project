#include "toast.h"
#include "../../libs/headers/raygui.h"

void drawToast(TOAST *toast)
{
    Rectangle toastBox = (Rectangle){.height = 400, .width = 800, .x = 1920 / 2 - 400, .y = 1080 / 2 - 200};
    if (toast->isToastOpened)
    {
        DrawRectangle(0, 0, 1920, 1080, GetColor(0x1212124C));
        int res = GuiMessageBox(toastBox, toast->toastTitle, toast->toastMessage, "OK");
        if (res >= 0 && res <= 1)
        {
            closeToast(toast);
        }
    }
}