#ifndef UI_INPUTBOX_H
#define UI_INPUTBOX_H

#include "../../model/window.h"
#include "../../constants/color.h"

void drawInputBox(windowModel *windowM, InputParams *input, Rectangle textBox, char Label[], int posIndex, int isSecret, int isMonetary);

#endif