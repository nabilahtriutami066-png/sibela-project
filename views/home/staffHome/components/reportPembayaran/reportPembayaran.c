#include "reportPembayaran.h"

void DrawMetricCard(const char *label, const char *value, Vector2 pos, float width, FontStyles *fonts);

void drawPembayaranReport(windowModel *windowM)
{
    int row;
    int cell_width = 250;
    int cell_height = 50;
    int start_x = 1920 / 2 - 600;
    int start_y = 1080 / 2;
    int padding = 5;
    int font_size = 32;
    for (int col = 0; col < 6; col++)
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
    DrawTextEx(windowM->fontStyle.regular, "Nama Murid",
               (Vector2){start_x + 1 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    DrawTextEx(windowM->fontStyle.regular, "Jumlah Pembayaran",
               (Vector2){start_x + 2 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    DrawTextEx(windowM->fontStyle.regular, "Metode",
               (Vector2){start_x + 3 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    DrawTextEx(windowM->fontStyle.regular, "Status",
               (Vector2){start_x + 4 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    DrawTextEx(windowM->fontStyle.regular, "Nama Staff",
               (Vector2){start_x + 5 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    for (row = 0; row < windowM->datas.nPembayaran; row++)
    {
        for (int col = 0; col < 6; col++)
        {
            Rectangle cellRect = {
                start_x + col * cell_width,
                start_y + row * cell_height,
                cell_width,
                cell_height};

            DrawRectangleLinesEx(cellRect, 1, SIBELAWHITE);
        }
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.pembayarans[row].id_pembayaran,
                   (Vector2){start_x + 0 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.pembayarans[row].nama_murid,
                   (Vector2){start_x + 1 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, TextFormat("Rp.%ld", windowM->datas.pembayarans[row].jumlah_pembayaran),
                   (Vector2){start_x + 2 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.pembayarans[row].dikonfirmasi ? windowM->datas.pembayarans[row].mtd_pembayaran : "-",
                   (Vector2){start_x + 3 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.pembayarans[row].dikonfirmasi ? "Terkonfirmasi" : "Belum Konfirmasi",
                   (Vector2){start_x + 4 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   windowM->datas.pembayarans[row].dikonfirmasi ? GREEN : RED);
        DrawTextEx(windowM->fontStyle.regular, windowM->datas.pembayarans[row].dikonfirmasi ? windowM->datas.pembayarans[row].nama_staff : "-",
                   (Vector2){start_x + 5 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
    }
    DrawTextEx(windowM->fontStyle.regular, TextFormat("Halaman %d dari %d", windowM->datas.page, windowM->datas.totalPages),
               (Vector2){start_x, start_y + (row * cell_height) + 30},
               40, 0,
               SIBELAWHITE);

    DrawMetricCard("Total Pembayaran", TextFormat("Rp. %d", windowM->datas.pembayaranReport.sumThisMonth), (Vector2){start_x, 330}, 200, &windowM->fontStyle);
    DrawMetricCard("Jumlah Pembayaran", TextFormat("%d", windowM->datas.pembayaranReport.totalThisMonth), (Vector2){start_x + 210, 330}, 200, &windowM->fontStyle);
    dateRangeSelector(windowM, (Vector2){start_x, 200});
    drawPieChart(windowM, (Vector2){1920 - 285, 250}, windowM->datas.pembayaranReport.total_tunai, windowM->datas.pembayaranReport.total_transfer, "Tunai", "Transfer", "Jumlah Pembayaran", 1);
    drawPieChart(windowM, (Vector2){1920 - 285 - 460 - 20, 250}, windowM->datas.pembayaranReport.count_tunai, windowM->datas.pembayaranReport.count_transfer, "Tunai", "Transfer", "Total Pembayaran Dilakukan", 0);
}

void DrawMetricCard(const char *label, const char *value, Vector2 pos, float width, FontStyles *fonts)
{
    float height = 110.0f;
    Rectangle bounds = {pos.x, pos.y, width, height};

    // Card Body
    DrawRectangleRounded(bounds, 0.2f, 10, SIBELAWHITE);

    // Top Accent Line
    DrawRectangleRounded((Rectangle){bounds.x, bounds.y, bounds.width, 6}, 1.0f, 10, PRIMARY);

    // Label
    DrawTextEx(fonts->medium, label, (Vector2){bounds.x + 10, bounds.y + 15}, 24, 0, SECONDARY);

    // Big Value
    DrawTextEx(fonts->regular, value, (Vector2){bounds.x + 10, bounds.y + 35}, 42, 0, PRIMARY);

    // Bottom Helper Text
    DrawTextEx(fonts->regular, "Periode ini", (Vector2){bounds.x + 10, bounds.y + 75}, 24, 0, GRAY);
}