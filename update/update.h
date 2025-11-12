#ifndef update
#define update

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>
#include "../model/model.h"
#include "../libs/utils.h"

void updateView(windowModel *window);

#endif