#ifndef loginView
#define loginView

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include "../libs/headers/raylib.h"
#include "../model/window.h"
#include "../libs/utils.h"
#include "../components/header.h"
#include "../data/staf.h"
#include "../constants/color.h"
#include "../components/ui/inputBox.h"

void drawStaffLogin(windowModel *windowM);
void drawMuridTeacherLogin(windowModel *windowM);

#endif