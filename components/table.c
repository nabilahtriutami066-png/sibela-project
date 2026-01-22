#include "table.h"

void drawTable(
    TableConfig config,
    TableColumn columns[],
    char **cell_data,
    Color highlight_color,
    Color text_color,
    Color border_color,
    int total_pages,
    int current_page)
{
    int data_index = 0;
    
    // Draw header row
    for (int col = 0; col < config.num_columns; col++)
    {
        Rectangle cell_rect = {
            config.start_x + col * columns[col].width,
            config.start_y - config.cell_height,
            columns[col].width,
            config.cell_height
        };
        DrawRectangleLinesEx(cell_rect, 1, border_color);
        DrawTextEx(config.font, columns[col].label,
                   (Vector2){cell_rect.x + config.padding, cell_rect.y + config.padding},
                   config.font_size, 0, text_color);
    }

    // Draw data rows
    for (int row = 0; row < config.num_rows; row++)
    {
        for (int col = 0; col < config.num_columns; col++)
        {
            Rectangle cell_rect = {
                config.start_x + col * columns[col].width,
                config.start_y + row * config.cell_height,
                columns[col].width,
                config.cell_height
            };
            
            if (row == config.current_row)
            {
                DrawRectangleRec(cell_rect, highlight_color);
            }
            DrawRectangleLinesEx(cell_rect, 1, border_color);
            
            // Draw cell text
            if (data_index < config.num_rows * config.num_columns && cell_data[data_index] != NULL)
            {
                DrawTextEx(config.font, cell_data[data_index],
                           (Vector2){cell_rect.x + config.padding, cell_rect.y + config.padding},
                           config.font_size, 0, text_color);
                data_index++;
            }
        }
    }

    // Draw pagination info
    char page_text[50];
    snprintf(page_text, 50, "Halaman %d dari %d", current_page, total_pages);
    DrawTextEx(config.font, page_text,
               (Vector2){config.start_x, config.start_y + (config.num_rows * config.cell_height) + 30},
               40, 0, text_color);
}

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
    int current_page)
{
    // Draw header row
    for (int col = 0; col < config.num_columns; col++)
    {
        Rectangle cell_rect = {
            config.start_x + col * columns[col].width,
            config.start_y - config.cell_height,
            columns[col].width,
            config.cell_height
        };
        DrawRectangleLinesEx(cell_rect, 1, border_color);
        DrawTextEx(config.font, columns[col].label,
                   (Vector2){cell_rect.x + config.padding, cell_rect.y + config.padding},
                   config.font_size, 0, text_color);
    }

    // Draw data rows
    for (int row = 0; row < data_size && row < config.num_rows; row++)
    {
        void *row_data = (char *)data_array + (row * sizeof(void *));
        
        for (int col = 0; col < config.num_columns; col++)
        {
            Rectangle cell_rect = {
                config.start_x + col * columns[col].width,
                config.start_y + row * config.cell_height,
                columns[col].width,
                config.cell_height
            };
            
            if (row == config.current_row)
            {
                DrawRectangleRec(cell_rect, highlight_color);
            }
            DrawRectangleLinesEx(cell_rect, 1, border_color);
            
            // Get and draw cell text
            char *cell_text = getter(row_data, col);
            if (cell_text != NULL)
            {
                DrawTextEx(config.font, cell_text,
                           (Vector2){cell_rect.x + config.padding, cell_rect.y + config.padding},
                           config.font_size, 0, text_color);
            }
        }
    }

    // Draw pagination info
    char page_text[50];
    snprintf(page_text, 50, "Halaman %d dari %d", current_page, total_pages);
    DrawTextEx(config.font, page_text,
               (Vector2){config.start_x, config.start_y + (config.num_rows * config.cell_height) + 30},
               40, 0, text_color);
}
