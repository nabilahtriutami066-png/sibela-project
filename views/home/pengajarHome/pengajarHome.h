#ifndef PENGAJARHOME_H
#define PENGAJARHOME_H

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include "../../../libs/headers/raylib.h"
#include "../../../model/window.h"
#include "../../../libs/utils.h"
#include "../../../components/header.h"
#include "../../../components/ui/sortControl.h"
#include "../../../data/staf.h"
#include "../../../constants/color.h"
#include "../../../components/ui/welcomePage.h"
#include "components/Materi/create.h"
#include "components/jadwal/read.h"
#include "components/Materi/read.h"
#include "components/Materi/update.h"
#include "components/absensi/read.h"

void drawPengajarHome(windowModel *windowM);

#endif