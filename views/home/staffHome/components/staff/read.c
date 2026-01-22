#include "read.h"
#include "../../../../../libs/headers/raygui.h"

void drawStaffRead(windowModel *windowM)
{
    int row;
    int cell_width = 250;
    int cell_height = 50;
    int start_x = 1920 / 2 - 600 + 100;
    int start_y = 1080 / 2 - 300;
    int padding = 5;
    int font_size = 32;
    DrawTextEx(windowM->fontStyle.regular, "DATA STAFF",
               (Vector2){start_x + 390,
                         start_y - 120},
               64, 0,
               SIBELAWHITE);

    if (windowM->datas.nStaf == 0)
    {
        DrawTextEx(
            windowM->fontStyle.regular,
            "Belum ada data Staff",
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
    DrawTextEx(windowM->fontStyle.regular, "Role",
               (Vector2){start_x + 1 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    DrawTextEx(windowM->fontStyle.regular, "Nama",
               (Vector2){start_x + 2 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    DrawTextEx(windowM->fontStyle.regular, "No. Hp",
               (Vector2){start_x + 3 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    DrawTextEx(windowM->fontStyle.regular, "Tangggal Masuk",
               (Vector2){start_x + 4 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);

    for (row = 0; row < windowM->datas.nStaf; row++)
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
                windowM->focusedData.staff = windowM->datas.staffs[row];
                DrawRectangleRec(cellRect, PRIMARY);
            }
            DrawRectangleLinesEx(cellRect, 1, SIBELAWHITE);
        }
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.staffs[row].id_staff,
                   (Vector2){start_x + 0 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.staffs[row].role,
                   (Vector2){start_x + 1 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.staffs[row].nama,
                   (Vector2){start_x + 2 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.staffs[row].no_hp,
                   (Vector2){start_x + 3 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.staffs[row].tanggal_masuk,
                   (Vector2){start_x + 4 * cell_width + padding,
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
        int res = GuiMessageBox((Rectangle){.height = 200, .width = 300, .x = 1920 / 2 - 150, .y = 1080 / 2 - 300}, "Delete Staff?", TextFormat("Apakah anda ingin menghapus staff %s?", windowM->focusedData.staff.id_staff), "Batal;Hapus!");

        if (res == 2)
        {
            deleteStaff(windowM->dbConn, windowM->focusedData.staff);
            windowM->dataFetchers.staffPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn, NULL);
            windowM->isModalShown = 0;
        }
        else if (res >= 0 && res < 2)
            windowM->isModalShown = 0;
    }
}