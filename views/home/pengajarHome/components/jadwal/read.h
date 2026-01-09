#ifndef PENGAJARHOME_JADWAL_READ_H
#define PENGAJARHOME_JADWAL_READ_H

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include "../../../../../libs/headers/raylib.h"
#include "../../../../../model/window.h"
#include "../../../../../libs/utils.h"
#include "../../../../../components/header.h"
#include "../../../../../constants/color.h"

void DrawMeetingPengajarCard(JadwalPertemuanWithDetails jadwal, Vector2 position, float width, FontStyles fonts);
void drawJadwalPengajarRead(windowModel *windowM);

#endif