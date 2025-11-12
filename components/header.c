#include "header.h"

void drawHeader()
{
    int line = 2;
    int cols = COLS / 2;

    //     move(line, cols);
    //     printw("                                            ,--,                   \n");
    //     move(line + 1, cols);
    //     printw("                                         ,---.'|                   \n");
    //     move(line + 2, cols);
    //     printw("  .--.--.      ,---,    ,---,.     ,---,.|   | :      ,---,        \n");
    //     move(line + 3, cols);
    //     printw(" /  /    '. ,`--.' |  ,'  .'  \\  ,'  .' |:   : |     '  .' \\       \n");
    //     move(line + 4, cols);
    //     printw("|  :  /`. / |   :  :,---.' .' |,---.'   ||   ' :    /  ;    '.     \n");
    //     move(line + 5, cols);
    //     printw(";  |  |--`  :   |  '|   |  |: ||   |   .';   ; '   :  :       \\    \n");
    //     move(line + 6, cols);
    //     printw("|  :  ;_    |   :  |:   :  :  /:   :  |-,'   | |__ :  |   /\\   \\   \n");
    //     move(line + 7, cols);
    //     printw(" \\  \\    `. '   '  ;:   |    ; :   |  ;/||   | :.'||  :  ' ;.   :  \n");
    //     move(line + 8, cols);
    //     printw("  `----.   \\|   |  ||   :     \\|   :   .''   :    ;|  |  ;/  \\   \\ \n");
    //     move(line + 9, cols);
    //     printw("  __ \\  \\  |'   :  ;|   |   . ||   |  |-,|   |  ./ '  :  | \\  \\ ,' \n");
    //     move(line + 10, cols);
    //     printw(" /  /`--'  /|   |  ''   :  '; |'   :  ;/|;   : ;   |  |  '  '--'   \n");
    //     move(line + 11, cols);
    //     printw("'--'.     / '   :  ||   |  | ; |   |    \\|   ,/    |  :  :         \n");
    //     move(line + 12, cols);
    //     printw("  `--'---'  ;   |.' |   :   /  |   :   .''---'     |  | ,'         \n");
    //     move(line + 13, cols);
    //     printw("            '---'   |   | ,'   |   | ,'            `--''           \n");
    //     move(line + 14, cols);
    //     printw("                    `----'     `----'                              \n");
    //     move(line + 15, cols);
    //     printw("                                                                   \n");

    readAndDrawAscii("logo.txt", cols, line);
}