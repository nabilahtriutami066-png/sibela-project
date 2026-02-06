#include "legend.h"
#include "raylib.h"
#include <string.h>

static void drawItem(int x, int y, const char *key, const char *desc, Font font)
{
    DrawTextEx(font, key, (Vector2){x, y}, 22, 0, WHITE);
    DrawTextEx(font, desc, (Vector2){x + 110, y}, 22, 0, WHITE);
}

static void drawLegendManajer(windowModel *windowM, int x, int y, int gap, Font font)
{
    int row = 0;

    if (windowM->cursorEnabled)
    {
        drawItem(x, y + gap * row++, "Atas/Bawah", "Navigasi Menu", font);
        drawItem(x, y + gap * row++, "Enter", "Pilih Menu", font);
        drawItem(x, y + gap * row++, "Esc", "Keluar Aplikasi", font);
        return;
    }

    if (windowM->activeSubWindow == READ)
    {
        switch (windowM->selectedPage)
        {
        case PEMBAYARANREPORT:
            drawItem(x, y + gap * row++, "Tab", "Kembali", font);
            drawItem(x, y + gap * row++, "Esc", "Keluar Aplikasi", font);
            break;

        case MANAJERSTAFF:
            drawItem(x, y + gap * row++, "Atas/Bawah", "Navigasi Data", font);
            drawItem(x, y + gap * row++, "N", "Tambah Staff", font);
            drawItem(x, y + gap * row++, "U", "Ubah Staff", font);
            drawItem(x, y + gap * row++, "D", "Hapus Staff", font);
            drawItem(x, y + gap * row++, "Enter", "Pilih", font);
            drawItem(x, y + gap * row++, "Tab", "Kembali", font);
            drawItem(x, y + gap * row++, "Esc", "Keluar Aplikasi", font);
            break;

        default:
            drawItem(x, y + gap * row++, "Tab", "Kembali", font);
            drawItem(x, y + gap * row++, "Esc", "Keluar Aplikasi", font);
            break;
        }
        return;
    }

    if (windowM->activeSubWindow == CREATE ||
        windowM->activeSubWindow == UPDATE)
    {
        drawItem(x, y + gap * row++, "Atas/Bawah", "Navigasi", font);
        drawItem(x, y + gap * row++, "Enter", "Simpan", font);
        drawItem(x, y + gap * row++, "Tab", "Batal", font);
        drawItem(x, y + gap * row++, "Esc", "Keluar Aplikasi", font);
        return;
    }
}

static void drawLegendStaff(windowModel *windowM, int x, int y, int gap, Font font)
{
    int row = 0;

    if (windowM->cursorEnabled)
    {
        drawItem(x, y + gap * row++, "Atas/Bawah", "Navigasi Menu", font);
        drawItem(x, y + gap * row++, "Enter", "Pilih Menu", font);
        drawItem(x, y + gap * row++, "Esc", "Keluar Aplikasi", font);
        return;
    }

    if (windowM->activeSubWindow == READ)
    {
        switch (windowM->selectedPage)
        {
        case PEMBAYARAN:
            drawItem(x, y + gap * row++, "Atas/Bawah", "Navigasi Data", font);
            drawItem(x, y + gap * row++, "N", "Tambah Data", font);
            drawItem(x, y + gap * row++, "Enter", "Pilih", font);
            drawItem(x, y + gap * row++, "Tab", "Kembali", font);
            drawItem(x, y + gap * row++, "Esc", "Keluar Aplikasi", font);
            break;

        default:
            drawItem(x, y + gap * row++, "Atas/Bawah", "Navigasi Data", font);
            drawItem(x, y + gap * row++, "N", "Tambah Data", font);
            drawItem(x, y + gap * row++, "U", "Ubah Data", font);
            drawItem(x, y + gap * row++, "D", "Hapus Data", font);
            drawItem(x, y + gap * row++, "Enter", "Pilih", font);
            drawItem(x, y + gap * row++, "Tab", "Kembali", font);
            drawItem(x, y + gap * row++, "Esc", "Keluar Aplikasi", font);
            break;
        }
        return;
    }

    if (windowM->activeSubWindow == CREATE ||
        windowM->activeSubWindow == UPDATE)
    {
        drawItem(x, y + gap * row++, "Atas/Bawah", "Navigasi", font);
        drawItem(x, y + gap * row++, "Enter", "Simpan", font);
        drawItem(x, y + gap * row++, "Tab", "Batal", font);
        drawItem(x, y + gap * row++, "Esc", "Keluar Aplikasi", font);
        return;
    }
}

void DrawLegend(windowModel *windowM)
{
    int x = 1920 - 380;
    int y = 1080 - 220;
    int gap = 30;

    Font font = windowM->fontStyle.medium;

    DrawRectangleRounded(
        (Rectangle){x - 20, y - 20, 360, 230},
        0.15f,
        8,
        Fade(BLACK, 0.55f));

    switch (windowM->currWindow)
    {
    case STAFHOME:
        if (strcmp(windowM->authUser.role, "MANAJER") == 0)
            drawLegendManajer(windowM, x, y, gap, font);
        else
            drawLegendStaff(windowM, x, y, gap, font);
        return;

    case PENGAJARHOME:
    {
        int row = 0;

        if (windowM->activeSubWindow == CREATE ||
            windowM->activeSubWindow == UPDATE)
        {
            drawItem(x, y + gap * row++, "Atas/Bawah", "Navigasi", font);
            drawItem(x, y + gap * row++, "Enter", "Simpan", font);
            drawItem(x, y + gap * row++, "Tab", "Batal", font);
            drawItem(x, y + gap * row++, "Esc", "Keluar Aplikasi", font);
            return;
        }

        if (windowM->activeSubWindow == READ)
        {
            switch (windowM->selectedPage)
            {
            case MATERI:
                drawItem(x, y + gap * row++, "Atas/Bawah", "Navigasi Data", font);
                drawItem(x, y + gap * row++, "N", "Tambah Data", font);
                drawItem(x, y + gap * row++, "U", "Ubah Data", font);
                drawItem(x, y + gap * row++, "D", "Hapus Data", font);
                drawItem(x, y + gap * row++, "Enter", "Pilih", font);
                drawItem(x, y + gap * row++, "Tab", "Kembali", font);
                drawItem(x, y + gap * row++, "Esc", "Keluar Aplikasi", font);
                break;

            default:
                drawItem(x, y + gap * row++, "Atas/Bawah", "Navigasi Data", font);
                drawItem(x, y + gap * row++, "Tab", "Kembali", font);
                drawItem(x, y + gap * row++, "Esc", "Keluar Aplikasi", font);
                break;
            }
            return;
        }
        break;
    }

    case MURIDHOME:
    {
        int row = 0;

        if (windowM->cursorEnabled)
        {
            drawItem(x, y + gap * row++, "Atas/Bawah", "Navigasi Menu", font);
            drawItem(x, y + gap * row++, "Enter", "Pilih Menu", font);
            drawItem(x, y + gap * row++, "Esc", "Keluar Aplikasi", font);
            return;
        }

        if (windowM->activeSubWindow == READ)
        {
            drawItem(x, y + gap * row++, "Atas/Bawah", "Navigasi Data", font);
            drawItem(x, y + gap * row++, "Tab", "Kembali", font);
            drawItem(x, y + gap * row++, "Esc", "Keluar Aplikasi", font);
            return;
        }
        break;
    }

    default:
    {
        int row = 0;
        drawItem(x, y + gap * row++, "Atas/Bawah", "Navigasi Menu", font);
        drawItem(x, y + gap * row++, "Enter", "Pilih Menu", font);
        drawItem(x, y + gap * row++, "Esc", "Keluar Aplikasi", font);
        return;
    }
    }
}
