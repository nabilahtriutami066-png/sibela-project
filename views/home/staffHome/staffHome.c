#include "staffHome.h"

void drawStaffHome(windowModel *windowM)
{
    Menus opsi[] = {
        (Menus){"Staff", 0},
        (Menus){"Murid", 0},
        (Menus){"Pengajar", 0},
        (Menus){"Ruangan", 0},
        (Menus){"Mata pelajaran", 0},
        (Menus){"Pembayaran", 0},
        (Menus){"Jadwal", 0},
        (Menus){"Log Out", 1},
    };
    int gap = 50;
    int startX = 35;
    int startY = 375;
    DrawRectangle(0, 0, 300, 1080, SECONDARY);
    // DrawTextEx(windowM->fontStyle.mediumItalic, "SIBELA", (Vector2){50, 64}, 80, 0, SIBELAWHITE);

    // Logo Sibela kiri Atas
    DrawRectangle(0, 0, 300, 200, SIBELAWHITE);
    DrawTextureEx(windowM->images.logo, (Vector2){40, 44}, 0, 0.30, SIBELAWHITE);

    // Logo Robot kiri bawah
    DrawTextureEx(windowM->images.logoRobot, (Vector2){50, 820}, 0, 0.25, SIBELAWHITE);

    for (int i = 0; i < sizeof(opsi) / sizeof(opsi[0]); i++)
    {
        if ((i == windowM->curPos && windowM->cursorEnabled) || (i == windowM->selectedPage && !windowM->cursorEnabled))
            DrawRectangleRounded((Rectangle){.x = startX - 8, .y = startY + i * gap - 7, .width = MeasureTextEx(windowM->fontStyle.medium, opsi[i].nama, 32, 0).x + 20, .height = 44}, 0.2, 0, SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.medium, opsi[i].nama, (Vector2){startX, startY + i * gap}, 32, 0, (opsi[i].selected ? DANGER : (i == windowM->curPos && windowM->cursorEnabled) || (i == windowM->selectedPage && !windowM->cursorEnabled) ? SECONDARY
                                                                                                                                                                                                                                                 : SIBELAWHITE));
    }

    if (windowM->activeSubWindow == READ)
    {
        switch (windowM->selectedPage)
        {
        case STAFF:
            drawStaffRead(windowM);
            break;
        case MURID:
            drawMuridRead(windowM);
            break;
        case PENGAJAR:
            drawPengajarRead(windowM);
            break;
        case RUANGAN:
            drawRuanganRead(windowM);
            break;
        case MAPEL:
            drawMapelRead(windowM);
            break;
        default:
            DrawTextEx(windowM->fontStyle.medium, TextFormat("Halo, %s!", windowM->authUser.nama), (Vector2){300 + 1620 / 2 - MeasureTextEx(windowM->fontStyle.medium, TextFormat("Halo, %s!", windowM->authUser.nama), 80, 0).x / 2, 90}, 80, 0, SIBELAWHITE);
            break;
        }
    }
    if (windowM->activeSubWindow == CREATE)
    {
        switch (windowM->selectedPage)
        {
        case STAFF:
            drawStaffCreate(windowM);
            break;
        case MURID:
            drawMuridCreate(windowM);
            break;
        case PENGAJAR:
            drawPengajarCreate(windowM);
            break;
        case RUANGAN:
            drawRuanganCreate(windowM);
            break;
        case MAPEL:
            drawMapelCreate(windowM);
            break;
        }
    }

    if (windowM->activeSubWindow == UPDATE)
    {
        switch (windowM->selectedPage)
        {
        case STAFF:
            drawStaffUpdate(windowM);
            break;
        case MURID:
            drawMuridUpdate(windowM);
            break;
        case PENGAJAR:
            drawPengajarUpdate(windowM);
            break;
        case RUANGAN:
            drawRuanganUpdate(windowM);
            break;
        case MAPEL:
            drawMapelUpdate(windowM);
            break;
        }
    }
}