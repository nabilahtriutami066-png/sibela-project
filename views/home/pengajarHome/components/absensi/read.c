#include "read.h"
#include "../../../../../libs/headers/raygui.h"

void drawAbsensiPengajarRead(windowModel *windowM)
{
    int row;
    int cell_width = 250;
    int cell_height = 50;
    int start_x = 300 + 1620 / 2;
    int start_y = 1080 / 2 - 300;
    int padding = 5;
    int font_size = 32;
    switch (windowM->pengajarHomeState.absensiPage.activeSubWindow)
    {
    case MAIN:
        DrawTextEx(windowM->fontStyle.bold, "PILIH JADWAL",
                   (Vector2){start_x - 175,
                             start_y - 150},
                   64, 0,
                   SIBELAWHITE);
        for (row = 0; row < windowM->datas.nJadwalPertemuan; row++)
        {
            if (windowM->curPos == row && row < windowM->datas.nJadwalPertemuan)
            {
                windowM->focusedData.jadwal = windowM->datas.jadwalPertemuans[row];
            }
            DrawMeetingPengajarCard(windowM->datas.jadwalPertemuans[row], (Vector2){start_x - 400, start_y + row * 230}, 800, windowM->fontStyle, windowM->curPos == row);
        }
        DrawTextEx(windowM->fontStyle.regular, TextFormat("Halaman %d dari %d", windowM->datas.page, windowM->datas.totalPages),
                   (Vector2){start_x - 130,
                             1080 - 120},
                   40, 0,
                   SIBELAWHITE);
        break;

    case PRESENSI:
        start_x = 300 + 220;
        cell_width = 400;
        DrawTextEx(windowM->fontStyle.bold, "ABSENSI MURID",
                   (Vector2){start_x + 1.8 * (cell_width + padding) - 310,
                             start_y - 200},
                   64, 0,
                   SIBELAWHITE);
        for (int col = 0; col < 3; col++)
        {
            Rectangle cellRect = {
                start_x + col * cell_width,
                start_y - cell_height,
                cell_width,
                cell_height};
            DrawRectangleLinesEx(cellRect, 1, SIBELAWHITE);
            DrawRectangleLinesEx(cellRect, 1, SIBELAWHITE);
        }
        DrawTextEx(windowM->fontStyle.regular, "Nama",
                   (Vector2){start_x + 0 * cell_width + padding,
                             start_y - cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, "Hadir?",
                   (Vector2){start_x + 1 * cell_width + padding,
                             start_y - cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, "Alasan",
                   (Vector2){start_x + 2 * cell_width + padding,
                             start_y - cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        for (int i = 0; i < windowM->pengajarHomeState.absensiPage.nMurid; i++)
        {
            for (int col = 0; col < 3; col++)
            {
                Rectangle cellRect = {
                    start_x + col * cell_width,
                    start_y + i * cell_height,
                    cell_width,
                    cell_height};
                if (i == windowM->curPos)
                {
                    DrawRectangleRec(cellRect, PRIMARY);
                }
                DrawRectangleLinesEx(cellRect, 1, SIBELAWHITE);
            }
            DrawTextEx(windowM->fontStyle.regular, windowM->pengajarHomeState.absensiPage.paginatedAbsensi[i].nama_murid,
                       (Vector2){start_x + 0 * cell_width + padding,
                                 start_y + i * cell_height + padding},
                       font_size, 0,
                       SIBELAWHITE);
            if (windowM->pengajarHomeState.absensiPage.paginatedAbsensi[i].isHadir)
                DrawTextEx(windowM->fontStyle.regular, "Hadir",
                           (Vector2){start_x + 1 * cell_width + padding,
                                     start_y + i * cell_height + padding},
                           font_size, 0,
                           GREEN);
            else
                DrawTextEx(windowM->fontStyle.regular, "Tidak Hadir",
                           (Vector2){start_x + 1 * cell_width + padding,
                                     start_y + i * cell_height + padding},
                           font_size, 0,
                           DANGER);
            // GuiCheckBox((Rectangle){.x = start_x + 1 * cell_width + padding, .y = start_y + i * cell_height + padding, .height = 40, .width = 40}, "", &windowM->pengajarHomeState.absensiPage.paginatedAbsensi[i].isHadir);
            if (!windowM->pengajarHomeState.absensiPage.paginatedAbsensi[i].isHadir)
            {
                Rectangle input = {.x = start_x + 2 * cell_width + padding,
                                   .y = start_y + i * cell_height + padding,
                                   .width = 350,
                                   .height = 30};
                GuiTextBox(input, windowM->datas.muridAbsensis[i + (windowM->pengajarHomeState.absensiPage.page - 1) * 10].alasan, 200, CheckCollisionPointRec(windowM->mousePosition, input));
            }
            else if (windowM->pengajarHomeState.absensiPage.paginatedAbsensi[i].isHadir)
            {
                DrawTextEx(windowM->fontStyle.regular, "-",
                           (Vector2){start_x + 2 * cell_width + padding,
                                     start_y + i * cell_height + padding},
                           font_size, 0,
                           SIBELAWHITE);
            }

            // char *formattedText = TextFormat("%s %s", windowM->pengajarHomeState.absensiPage.paginatedAbsensi[i].nama_murid, windowM->pengajarHomeState.absensiPage.paginatedAbsensi[i].isHadir ? "HADIR" : "TIDAK HADIR");
            // Vector2 textLen = MeasureTextEx(windowM->fontStyle.regular, formattedText, 64, 0);
            // if (windowM->curPos == i)
            // {
            //     DrawRectangleRounded((Rectangle){start_x - 325 - 15,
            //                                      start_y - 150 - 10 + i * 50, .width = textLen.x + 20, .height = textLen.y + 20},
            //                          0.4, 0, PRIMARY);
            //     if (!windowM->pengajarHomeState.absensiPage.paginatedAbsensi[i].isHadir)
            //     {
            //         Rectangle input = {.x = start_x - 325 + textLen.x + 12,
            //                            .y = start_y - 150 - 10 + i * 50,
            //                            .width = textLen.x + 20,
            //                            .height = textLen.y + 20};
            //         GuiTextBox(input, windowM->datas.muridAbsensis[i + (windowM->pengajarHomeState.absensiPage.page - 1) * 10].alasan, 200, CheckCollisionPointRec(windowM->mousePosition, input));
            //     }
            // }
            // DrawTextEx(windowM->fontStyle.regular, formattedText,
            //            (Vector2){start_x - 325,
            //                      start_y - 150 + i * 50},
            //            64, 0,
            //            SIBELAWHITE);

            Rectangle submitButton = {.x = 300 + 1620 / 2 - 100 + 7,
                                      .y = 1080 - 200,
                                      .width = 200,
                                      .height = 80};
            if (GuiButton(submitButton, "Kumpulkan", 0))
            {
                QUERYSTATUS resSql = windowM->pengajarHomeState.absensiPage.submitFunc(windowM->datas.muridAbsensis, windowM->datas.nMuridAbsensi, windowM->focusedData.jadwal.id_pertemuan, windowM->dbConn, windowM->authUser);
                if (resSql == SUCCESS)
                    showToast(&windowM->toast, "Berhasil disimpan", "Absensi berhasil disimpan!");
                else
                    showToast(&windowM->toast, "Gagal disimpan!", "Absensi Gagal di simpan!");
            }
            DrawTextEx(windowM->fontStyle.regular, TextFormat("Halaman %d dari %d", windowM->pengajarHomeState.absensiPage.page, windowM->pengajarHomeState.absensiPage.nPage),
                       (Vector2){start_x + 1.8 * (cell_width + padding) - 250,
                                 800},
                       40, 0,
                       SIBELAWHITE);
        }
        break;
    }
}