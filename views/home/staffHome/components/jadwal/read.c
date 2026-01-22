#include "read.h"
#include "../../../../../libs/headers/raygui.h"

void drawJadwalRead(windowModel *windowM)
{
    int row;
    int cell_width = 280;
    int cell_height = 50;
    int start_x = 1920 / 2 - 600;
    int start_y = 1080 / 2 - 300;
    int padding = 5;
    int font_size = 32;
    int materiPadding = 100;
    DrawTextEx(windowM->fontStyle.regular, "DATA JADWAL",
               (Vector2){start_x + 390,
                         start_y - 120},
               64, 0,
               SIBELAWHITE);

    if (windowM->datas.nJadwalPertemuan == 0)
    {
        DrawTextEx(
            windowM->fontStyle.regular,
            "Belum ada data jadwal Pertemuan",
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

    for (int col = 0; col < 5; col++)
    {
        Rectangle cellRect = {
            col >= 3 ? start_x + col * cell_width + materiPadding : start_x + col * cell_width,
            start_y - cell_height,
            col == 2 ? cell_width + materiPadding : cell_width,
            cell_height};
        DrawRectangleLinesEx(cellRect, 1, SIBELAWHITE);
    }
    DrawTextEx(windowM->fontStyle.regular, "id",
               (Vector2){start_x + 0 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    DrawTextEx(windowM->fontStyle.regular, "Nama Pengajar",
               (Vector2){start_x + 1 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    DrawTextEx(windowM->fontStyle.regular, "Materi",
               (Vector2){start_x + 2 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    DrawTextEx(windowM->fontStyle.regular, "Jumlah Siswa",
               (Vector2){start_x + 3 * cell_width + padding + materiPadding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    DrawTextEx(windowM->fontStyle.regular, "Waktu",
               (Vector2){start_x + 4 * cell_width + padding + materiPadding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    for (row = 0; row < windowM->datas.nJadwalPertemuan; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            Rectangle cellRect = {
                col >= 3 ? start_x + col * cell_width + materiPadding : start_x + col * cell_width,
                start_y + row * cell_height,
                col == 2 ? cell_width + materiPadding : cell_width,
                cell_height};
            if (row == windowM->curPos)
            {
                windowM->focusedData.jadwal = windowM->datas.jadwalPertemuans[row];
                DrawRectangleRec(cellRect, PRIMARY);
            }
            DrawRectangleLinesEx(cellRect, 1, SIBELAWHITE);
        }
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.jadwalPertemuans[row].id_pertemuan,
                   (Vector2){start_x + 0 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.jadwalPertemuans[row].nama_pengajar,
                   (Vector2){start_x + 1 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.jadwalPertemuans[row].judul_materi,
                   (Vector2){start_x + 2 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, TextFormat("%ld", windowM->datas.jadwalPertemuans[row].jumlah_murid),
                   (Vector2){start_x + 3 * cell_width + padding + materiPadding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.jadwalPertemuans[row].waktu,
                   (Vector2){start_x + 4 * cell_width + padding + materiPadding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
    }
    DrawTextEx(windowM->fontStyle.regular, TextFormat("Halaman %d dari %d", windowM->datas.page, windowM->datas.totalPages),
               (Vector2){start_x , start_y + (row * cell_height) + 30},
               40, 0,
               SIBELAWHITE);
    if (windowM->isModalShown)
    {
        int res = GuiMessageBox((Rectangle){.height = 200, .width = 300, .x = 1920 / 2 - 150, .y = 1080 / 2 - 300}, "Delete Jadwal?", TextFormat("Apakah anda ingin menghapus Jadwal %s?", windowM->focusedData.jadwal.id_pertemuan), "Batal;Hapus!");

        if (res == 2)
        {
            deleteJadwalPertemuan(windowM->dbConn, windowM->focusedData.jadwal);
            windowM->dataFetchers.staffPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, NULL);
            windowM->isModalShown = 0;
        }
        else if (res >= 0 && res < 2)
            windowM->isModalShown = 0;
    }
}