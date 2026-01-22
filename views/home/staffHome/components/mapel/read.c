#include "read.h"
#include "../../../../../libs/headers/raygui.h"

void drawMapelRead(windowModel *windowM)
{
    int row;
    int cell_width = 450;
    int cell_height = 50;
    int start_x = 1920 / 2 - 600 + 250;
    int start_y = 1080 / 2 - 300;
    int padding = 5;
    int font_size = 32;
    DrawTextEx(windowM->fontStyle.regular, "DATA MAPEL",
               (Vector2){start_x + 390,
                         start_y - 120},
               64, 0,
               SIBELAWHITE);

    if (windowM->datas.nMapel == 0)
    {
        DrawTextEx(
            windowM->fontStyle.regular,
            "Belum ada data Pelajaran",
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

    for (int col = 0; col < 2; col++)
    {
        Rectangle cellRect = {
            start_x + col * cell_width,
            start_y - cell_height,
            cell_width,
            cell_height};
        DrawRectangleLinesEx(cellRect, 1, SIBELAWHITE);
        DrawRectangleLinesEx(cellRect, 1, SIBELAWHITE);
    }
    DrawTextEx(windowM->fontStyle.regular, "id",
               (Vector2){start_x + 0 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    DrawTextEx(windowM->fontStyle.regular, "Nama Mapel",
               (Vector2){start_x + 1 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    for (row = 0; row < windowM->datas.nMapel; row++)
    {
        for (int col = 0; col < 2; col++)
        {
            Rectangle cellRect = {
                start_x + col * cell_width,
                start_y + row * cell_height,
                cell_width,
                cell_height};
            if (row == windowM->curPos)
            {
                windowM->focusedData.mapel = windowM->datas.Mapels[row];
                DrawRectangleRec(cellRect, PRIMARY);
            }
            DrawRectangleLinesEx(cellRect, 1, SIBELAWHITE);
        }
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.Mapels[row].id_mapel,
                   (Vector2){start_x + 0 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.Mapels[row].nama_mapel,
                   (Vector2){start_x + 1 * cell_width + padding,
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
        int res = GuiMessageBox((Rectangle){.height = 200, .width = 300, .x = 1920 / 2 - 150, .y = 1080 / 2 - 300}, "Delete Mapel?", TextFormat("Apakah anda ingin menghapus mapel %s?", windowM->focusedData.mapel.id_mapel), "Batal;Hapus!");

        if (res == 2)
        {
            deleteMapel(windowM->dbConn, windowM->focusedData.mapel);
            windowM->dataFetchers.staffPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, NULL);
            windowM->isModalShown = 0;
        }
        else if (res >= 0 && res < 2)
            windowM->isModalShown = 0;
    }
}