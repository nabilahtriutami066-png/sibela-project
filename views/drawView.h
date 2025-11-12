#ifndef drawView
#define drawView

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "../model/model.h"
#include "../libs/utils.h"
#include "../components/header.h"
#include "homeView.h"

void drawRootView(windowModel *window);

#endif