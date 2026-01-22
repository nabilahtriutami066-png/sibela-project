#include "raygui.h"
#include "read.h"
#include "raylib.h"

void drawMateriMuridRead(windowModel *windowM)
{
    static bool initialized = false;
    MateriPageState *state = &windowM->MuridHomeState.materiPage;

    if (!initialized)
    {
        state->activeSubWindow = MATERI_MAPEL;
        state->expandedIndex = -1;
        initialized = true;
    }

    int x = 600;
    int y = 200;

    Font font = windowM->fontStyle.regular;

    if (state->activeSubWindow == MATERI_MAPEL)
    {
        DrawTextEx(
            font,
            "PILIH MATA PELAJARAN",
            (Vector2){x, y - 60},
            38,
            2,
            WHITE);

        for (int i = 0; i < windowM->datas.nMapel; i++)
        {
            Rectangle btn = {
                x,
                y + i * 70,
                400,
                55};

            if (GuiButton(btn, windowM->datas.Mapels[i].nama_mapel, 0))
            {
                state->selectedMapel = windowM->datas.Mapels[i];
                windowM->datas.page = 1;

                findAllMateriByMapelId(
                    state->selectedMapel.id_mapel,
                    &windowM->datas,
                    &state->nPage,
                    windowM->dbConn,
                    &windowM->authUser);

                state->expandedIndex = -1;
                state->activeSubWindow = MATERI_LIST;
            }
        }
    }
    else if (state->activeSubWindow == MATERI_LIST)
    {
        DrawTextEx(
            font,
            "DAFTAR MATERI",
            (Vector2){x, y - 60},
            38,
            2,
            WHITE);

        DrawTextEx(
            font,
            state->selectedMapel.nama_mapel,
            (Vector2){x, y - 25},
            22,
            2,
            GRAY);

        for (int i = 0; i < windowM->datas.nMateri; i++)
        {
            Rectangle materiHeader = {
                x,
                y + i * 70,
                700,
                50};

            if (GuiButton(materiHeader, windowM->datas.Materis[i].judul_materi, 0))
            {
                state->expandedIndex = i;
                state->activeSubWindow = MATERI_DETAIL;
            }
        }

        if (GuiButton((Rectangle){x, y + 520, 120, 40}, "Kembali", 0))
        {
            state->activeSubWindow = MATERI_MAPEL;
        }
    }
    else if (state->activeSubWindow == MATERI_DETAIL)
    {
        int i = state->expandedIndex;

        DrawTextEx(
            font,
            windowM->datas.Materis[i].judul_materi,
            (Vector2){x, y - 40},
            34,
            2,
            WHITE);

        Rectangle box = {
            x,
            y,
            700,
            300};

        DrawRectangleRounded(box, 0.2f, 8, DARKGRAY);

        DrawTextEx(
            font,
            windowM->datas.Materis[i].isi_materi,
            (Vector2){box.x + 15, box.y + 10},
            18,
            2,
            LIGHTGRAY);

        if (GuiButton((Rectangle){x, y + 330, 120, 40}, "Kembali", 0))
        {
            state->activeSubWindow = MATERI_LIST;
            state->expandedIndex = -1;
        }
    }
}
