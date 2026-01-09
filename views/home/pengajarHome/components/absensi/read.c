#include "read.h"

void drawAbsensiPengajarRead(windowModel *windowM)
{
    int cell_width = 250;
    int cell_height = 50;
    int start_x = 300 + 1620 / 2;
    int start_y = 1080 / 2 - 300;
    int padding = 5;
    int font_size = 32;

    DrawTextEx(windowM->fontStyle.regular, "PILIH JADWAL",
               (Vector2){start_x - 225,
                         start_y - 150},
               64, 0,
               SIBELAWHITE);

    for (int row = 0; row < windowM->datas.nJadwalPertemuan; row++)
    {
        DrawMeetingPengajarCard(windowM->datas.jadwalPertemuans[row], (Vector2){start_x - 400, start_y + row * 200}, 800, windowM->fontStyle);
    }
    DrawTextEx(windowM->fontStyle.regular, TextFormat("Halaman %d dari %d", windowM->datas.page, windowM->datas.totalPages),
               (Vector2){300 + (1620 / 2 - 50),
                         1000},
               40, 0,
               SIBELAWHITE);
}