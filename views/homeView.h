#ifndef homeView
#define homeView

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>
#include "../model/model.h"
#include "../libs/utils.h"
#include "../components/header.h"

void drawHome(windowModel *window);

#endif