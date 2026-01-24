#include "read.h"
#include "../../../../../libs/headers/raygui.h"

void drawMuridRead(windowModel *windowM)
{
    int row;
    int i = 1;
    int cell_width = 250;
    int cell_height = 50;
    int start_x = 485;
    int start_y = 320;
    int padding = 5;
    int font_size = 32;
    DrawTextEx(windowM->fontStyle.bold, "DATA Murid",
               (Vector2){start_x + 3 * (cell_width + padding) - 290,
                         start_y - 200},
               64, 0,
               SIBELAWHITE);

    drawSearchBar(windowM, (Vector2){start_x + 5 * (cell_width + padding) - 410, start_y - cell_height - 85});
    DrawSortControl(windowM, (Vector2){.x = start_x, .y = start_y - cell_height - 65});
    if (windowM->datas.nMurid == 0)
    {
        DrawTextEx(
            windowM->fontStyle.regular,
            "Belum ada data Murid",
            (Vector2){
                start_x + 380,
                start_y + 290},
            40,
            2,
            Fade(SIBELAWHITE, 0.6f));
        return;
    }

    for (int col = 0; col < 5; col++)
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
    DrawTextEx(windowM->fontStyle.regular, "Nama",
               (Vector2){start_x + 1 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    DrawTextEx(windowM->fontStyle.regular, "No. Hp",
               (Vector2){start_x + 2 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    DrawTextEx(windowM->fontStyle.regular, "Tanggal Masuk",
               (Vector2){start_x + 3 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    DrawTextEx(windowM->fontStyle.regular, "Tingkat",
               (Vector2){start_x + 4 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    for (row = 0; row < windowM->datas.nMurid; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            Rectangle cellRect = {
                start_x + col * cell_width,
                start_y + row * cell_height,
                cell_width,
                cell_height};
            if (row == windowM->curPos)
            {
                windowM->focusedData.murid = windowM->datas.murids[row];
                DrawRectangleRec(cellRect, PRIMARY);
            }
            DrawRectangleLinesEx(cellRect, 1, SIBELAWHITE);
        }
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.murids[row].id_murid,
                   (Vector2){start_x + 0 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.murids[row].nama,
                   (Vector2){start_x + 1 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.murids[row].no_hp,
                   (Vector2){start_x + 2 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, FormatDatePretty(ParseSQLDate(windowM->datas.murids[row].tanggal_masuk)),
                   (Vector2){start_x + 3 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, TextFormat("%d", windowM->datas.murids[row].tingkat),
                   (Vector2){start_x + 4 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
    }
    DrawTextEx(windowM->fontStyle.regular, TextFormat("Halaman %d dari %d", windowM->datas.page, windowM->datas.totalPages),
               (Vector2){start_x, start_y + (row * cell_height) + 30},
               40, 0,
               SIBELAWHITE);
    if (windowM->isModalShown)
    {
        int res = GuiMessageBox((Rectangle){.height = 400, .width = 800, .x = 300 + 1620 / 2 - 400, .y = 1080 / 2 - 200}, "Hapus Murid?", TextFormat("Apakah anda ingin menghapus murid %s?", windowM->focusedData.murid.id_murid), "Batal;Hapus!");

        if (res == 2)
        {
            QUERYSTATUS sqlRes = deleteMurid(windowM->dbConn, windowM->focusedData.murid);
            if (sqlRes == SUCCESS)
            {
                windowM->dataFetchers.staffPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, NULL);
                showToast(&windowM->toast, "Terhapus", "Siswa berhasil dihapus!");
            }
            else
            {
                showToast(&windowM->toast, "Gagal Hapus!", "Siswa sudah memiliki relasi!");
            }
            windowM->isModalShown = 0;
        }
        else if (res >= 0 && res < 2)
            windowM->isModalShown = 0;
    }
}