#ifndef MURIDHOME_H
#define MURIDHOME_H

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include "../../../libs/headers/raylib.h"
#include "../../../model/window.h"
#include "../../../libs/utils.h"
#include "../../../components/header.h"
#include "../../../components/ui/sortControl.h"
#include "../../../components/ui/welcomePage.h"
#include "../../../constants/color.h"
#include "components/jadwal/read.h"
#include "components/pembayaran/read.h"

void drawMuridHome(windowModel *windowM);

#endif