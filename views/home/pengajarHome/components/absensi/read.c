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
    DrawTextEx(windowM->fontStyle.regular, "PILIH JADWAL",
        (Vector2){start_x - 225,
            start_y - 150},
            64, 0,
            SIBELAWHITE);
            
            if (windowM->datas.nRuangan == 0)
            {
                DrawTextEx(
                    windowM->fontStyle.regular,
                    "Belum ada data Pembayaran",
                    (Vector2){
                        start_x + 380,
                        start_y + 290},
                    40,
                    2,
                    Fade(SIBELAWHITE, 0.6f));
                return;
            }
            else
        for (row = 0; row < windowM->datas.nJadwalPertemuan; row++)
        {
            if (windowM->curPos == row && row < windowM->datas.nJadwalPertemuan)
            {
                windowM->focusedData.jadwal = windowM->datas.jadwalPertemuans[row];
            }
            DrawMeetingPengajarCard(windowM->datas.jadwalPertemuans[row], (Vector2){start_x - 400, start_y + row * 200}, 800, windowM->fontStyle, windowM->curPos == row);
        }
        DrawTextEx(windowM->fontStyle.regular, TextFormat("Halaman %d dari %d", windowM->datas.page, windowM->datas.totalPages),
                   (Vector2){start_x, start_y + (row * cell_height) + 30},
                   40, 0,
                   SIBELAWHITE);
        break;

    case PRESENSI:

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
        else
            for (int i = 0; i < windowM->pengajarHomeState.absensiPage.nMurid; i++)
            {
                char *formattedText = TextFormat("%s %s", windowM->pengajarHomeState.absensiPage.paginatedAbsensi[i].nama_murid, windowM->pengajarHomeState.absensiPage.paginatedAbsensi[i].isHadir ? "HADIR" : "Belom");
                Vector2 textLen = MeasureTextEx(windowM->fontStyle.regular, formattedText, 64, 0);
                if (windowM->curPos == i)
                {
                    DrawRectangleRounded((Rectangle){start_x - 325 - 15,
                                                     start_y - 150 - 10 + i * 50, .width = textLen.x + 20, .height = textLen.y + 20},
                                         0.4, 0, PRIMARY);
                    if (!windowM->pengajarHomeState.absensiPage.paginatedAbsensi[i].isHadir)
                    {
                        Rectangle input = {.x = start_x - 325 + textLen.x + 12,
                                           .y = start_y - 150 - 10 + i * 50,
                                           .width = textLen.x + 20,
                                           .height = textLen.y + 20};
                        GuiTextBox(input, windowM->datas.muridAbsensis[i + (windowM->pengajarHomeState.absensiPage.page - 1) * 10].alasan, 200, CheckCollisionPointRec(windowM->mousePosition, input));
                    }
                }
                DrawTextEx(windowM->fontStyle.regular, formattedText,
                           (Vector2){start_x - 325,
                                     start_y - 150 + i * 50},
                           64, 0,
                           SIBELAWHITE);

                Rectangle submitButton = {.x = 1920 / 2 - 100,
                                          .y = 1080 - 150,
                                          .width = 200,
                                          .height = 80};
                if (GuiButton(submitButton, "Submit"))
                {
                    windowM->pengajarHomeState.absensiPage.submitFunc(windowM->pengajarHomeState.absensiPage.paginatedAbsensi, windowM->datas.nMuridAbsensi, windowM->focusedData.jadwal.id_pertemuan, windowM->dbConn, windowM->authUser);
                }
                DrawTextEx(windowM->fontStyle.regular, TextFormat("Halaman %d dari %d", windowM->pengajarHomeState.absensiPage.page, windowM->pengajarHomeState.absensiPage.nPage),
                           (Vector2){300 + (1620 / 2 - 50),
                                     1000},
                           40, 0,
                           SIBELAWHITE);
            }
        break;
    }
}