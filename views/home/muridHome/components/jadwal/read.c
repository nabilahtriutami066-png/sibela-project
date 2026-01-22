#include "read.h"
#include "../../../../../libs/headers/raygui.h"

void drawJadwalMuridRead(windowModel *windowM)
{
    int row;
    int cell_width = 250;
    int cell_height = 50;
    int start_x = 300 + 1620 / 2;
    int start_y = 1080 / 2 - 300;
    int padding = 5;
    int font_size = 32;

    DrawTextEx(windowM->fontStyle.regular, "JADWAL PERTEMUAN",
               (Vector2){start_x - 225,
                         start_y - 150},
               64, 0,
               SIBELAWHITE);

    if (windowM->datas.nJadwalPertemuan == 0)
    {
        DrawTextEx(
            windowM->fontStyle.regular,
            "Belum ada data Jadwal Pertemuan",
            (Vector2){
                start_x + 380,
                start_y + 290
            },
            40,
            2,
            Fade(SIBELAWHITE, 0.6f)
        );
        return;
    }

    for (row = 0; row < windowM->datas.nJadwalPertemuan; row++)
    {
        DrawMeetingCard(windowM->datas.jadwalPertemuans[row], (Vector2){start_x - 400, start_y + row * 200}, 800, windowM->fontStyle);
    }
    DrawTextEx(windowM->fontStyle.regular, TextFormat("Halaman %d dari %d", windowM->datas.page, windowM->datas.totalPages),
               (Vector2){start_x , start_y + (row * cell_height) + 30},
               40, 0,
               SIBELAWHITE);
}

void DrawMeetingCard(JadwalPertemuanWithDetails jadwal, Vector2 position, float width, FontStyles fonts)
{
    float height = 160.0f;
    float padding = 25.0f;
    float cornerRoundness = 0.15f;

    Rectangle cardBounds = {position.x, position.y, width, height};

    DrawRectangleRounded((Rectangle){cardBounds.x + 2, cardBounds.y + 4, cardBounds.width, cardBounds.height}, cornerRoundness, 10, Fade(BLACK, 0.1f));

    DrawRectangleRounded(cardBounds, cornerRoundness, 10, SIBELAWHITE);

    Rectangle accentBar = {cardBounds.x, cardBounds.y + 20, 5, 40};
    DrawRectangleRec(accentBar, PRIMARY);

    DrawTextEx(fonts.regular, jadwal.waktu, (Vector2){cardBounds.x + padding, cardBounds.y + 18}, 44, 0, TERTIARY);

    float startY = cardBounds.y + 60;
    float labelX = cardBounds.x + padding;
    float valueX = cardBounds.x + 150;

    DrawTextEx(fonts.regular, "Pengajar:", (Vector2){labelX, startY}, 36, 0, SECONDARY);
    DrawTextEx(fonts.regular, jadwal.nama_pengajar, (Vector2){valueX, startY}, 36, 0, TERTIARY);

    DrawTextEx(fonts.regular, "Lokasi:", (Vector2){labelX, startY + 25}, 36, 0, SECONDARY);
    DrawTextEx(fonts.regular, jadwal.lokasi, (Vector2){valueX, startY + 25}, 36, 0, TERTIARY);

    DrawTextEx(fonts.regular, "Subject:", (Vector2){labelX, startY + 50}, 36, 0, SECONDARY);
    DrawTextEx(fonts.regular, jadwal.judul_materi, (Vector2){valueX, startY + 50}, 36, 0, PRIMARY);
}