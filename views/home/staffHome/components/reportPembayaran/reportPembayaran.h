#ifndef STAFFHOME_PEMBAYARAN_REPORT_H
#define STAFFHOME_PEMBAYARAN_REPORT_H

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include "../../../../../libs/headers/raylib.h"
#include "../../../../../model/window.h"
#include "../../../../../libs/utils.h"
#include "../../../../../components/header.h"
#include "../../../../../components/ui/dateRange.h"
#include "../../../../../components/ui/pieChart.h"
#include "../../../../../data/murid.h"
#include "../../../../../constants/color.h"

void drawPembayaranReport(windowModel *windowM);

#endif