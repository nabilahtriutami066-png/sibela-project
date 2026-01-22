#ifndef TABLE_H
#define TABLE_H

#include "../libs/headers/raylib.h"
#include "../model/model.h"

typedef struct {
    char *label;
    int width;
} TableColumn;

typedef struct {
    int start_x;
    int start_y;
    int cell_height;
    int padding;
    int font_size;
    int num_columns;
    int num_rows;
    int current_row;
    Font font;
} TableConfig;

// Generic table renderer
void drawTable(
    TableConfig config,
    TableColumn columns[],
    char **cell_data,
    Color highlight_color,
    Color text_color,
    Color border_color,
    int total_pages,
    int current_page
);

// Helper to get cell value from data
typedef char* (*CellDataGetter)(void *row_data, int col_index);

void drawTableWithData(
    TableConfig config,
    TableColumn columns[],
    void *data_array,
    int data_size,
    CellDataGetter getter,
    Color highlight_color,
    Color text_color,
    Color border_color,
    int total_pages,
    int current_page
);

#endif
