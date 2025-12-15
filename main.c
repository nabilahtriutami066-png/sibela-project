#include "libs/utils.h"
#include "model/model.h"
#include "model/window.h"
#include "update/update.h"
#include "views/drawView.h"
#include "data/staf.h"
#include "data/mapel.h"
#include "data/ruangan.h"
#include "views/Loading.h"

int main()
{
    // SetConfigFlags(FLAG_FULLSCREEN_MODE);
    // SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1920, 1080, "Sibela");

    ToggleFullscreen();

    Font poppinsMedium = LoadFontEx("assets/fonts/Poppins-Medium.ttf", 224, 0, 250);
    Font poppinsRegular = LoadFontEx("assets/fonts/Poppins-Regular.ttf", 224, 0, 250);
    Font poppinsMediumItalic = LoadFontEx("assets/fonts/Poppins-MediumItalic.ttf", 224, 0, 250);

    SQLHDBC dbConn;
    initSQLConn(&dbConn);
    windowModel defaultWindow = (windowModel){
        .currWindow = LANDINGPAGE,
        .shouldClose = 0,
        .curPos = 0,
        .page = 1,
        .cursorEnabled = 1,
        .selectedPage = -1,
        .isModalShown = 0,
        .dbConn = &dbConn,
        .activeSubWindow = READ,
        .loginData = {.email = {.charLen = 0, .text = "\0"}, .activeInput = 0}};
    defaultWindow.fontStyle.medium = &poppinsMedium;
    defaultWindow.fontStyle.regular = &poppinsRegular;
    defaultWindow.fontStyle.mediumItalic = &poppinsMediumItalic;
    defaultWindow.datas.page = 1;
    defaultWindow.forms[STAFF].fields[1] = (InputField){.label = "Nama", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    defaultWindow.forms[STAFF].fields[2] = (InputField){.label = "Tanggal Lahir", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    defaultWindow.forms[STAFF].fields[3] = (InputField){.label = "No. HP", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    defaultWindow.forms[STAFF].fields[4] = (InputField){.label = "Password", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    defaultWindow.forms[STAFF].fields[5] = (InputField){.label = "Email", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    defaultWindow.forms[STAFF].fields[6] = (InputField){.label = "Submit", .type = BUTTONINPUT};
    defaultWindow.forms[MURID].fields[1] = (InputField){.label = "Nama", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    defaultWindow.forms[MURID].fields[2] = (InputField){.label = "Tanggal Lahir", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    defaultWindow.forms[MURID].fields[3] = (InputField){.label = "No HP", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    defaultWindow.forms[MURID].fields[4] = (InputField){.label = "Password", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    defaultWindow.forms[MURID].fields[5] = (InputField){.label = "Tingkat", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    defaultWindow.forms[MURID].fields[6] = (InputField){.label = "Submit", .type = BUTTONINPUT};
    defaultWindow.forms[PENGAJAR].fields[1] = (InputField){.label = "Nama", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    defaultWindow.forms[PENGAJAR].fields[2] = (InputField){.label = "Tanggal Lahir", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    defaultWindow.forms[PENGAJAR].fields[3] = (InputField){.label = "No HP", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    defaultWindow.forms[PENGAJAR].fields[4] = (InputField){.label = "Password", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    defaultWindow.forms[PENGAJAR].fields[5] = (InputField){.label = "Submit", .type = BUTTONINPUT};
    defaultWindow.forms[RUANGAN].fields[1] = (InputField){.label = "Lokasi", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    defaultWindow.forms[RUANGAN].fields[2] = (InputField){.label = "Deskripsi", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    defaultWindow.forms[RUANGAN].fields[3] = (InputField){.label = "Submit", .type = BUTTONINPUT};
    defaultWindow.forms[MAPEL].fields[1] = (InputField){.label = "Nama Mapel", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    defaultWindow.forms[MAPEL].fields[2] = (InputField){.label = "Submit", .type = BUTTONINPUT};
    defaultWindow.forms[STAFF].nField = 6;
    defaultWindow.forms[MURID].nField = 6;
    defaultWindow.forms[MAPEL].nField = 2;
    defaultWindow.forms[PENGAJAR].nField = 5;
    defaultWindow.forms[RUANGAN].nField = 3;
    defaultWindow.forms[STAFF].fieldPerPage = 4;
    defaultWindow.forms[MAPEL].fieldPerPage = 2;
    defaultWindow.forms[MURID].fieldPerPage = 4;
    defaultWindow.forms[PENGAJAR].fieldPerPage = 5;
    defaultWindow.forms[RUANGAN].fieldPerPage = 3;
    defaultWindow.forms[STAFF].func = createStaff;
    defaultWindow.forms[MAPEL].func = createMapel;
    defaultWindow.forms[MURID].func = createMurid;
    defaultWindow.forms[PENGAJAR].func = createPengajar;
    defaultWindow.forms[RUANGAN].func = createRuangan;
    // Image Member
    defaultWindow.members[0].image = LoadTexture("assets/images/member/rayyan.png");
    defaultWindow.members[1].image = LoadTexture("assets/images/member/rasya.png");
    defaultWindow.members[2].image = LoadTexture("assets/images/member/bayu.png");
    defaultWindow.members[3].image = LoadTexture("assets/images/member/rijal.png");
    defaultWindow.members[4].image = LoadTexture("assets/images/member/nabilah.png");
    defaultWindow.dataFetchers.admin[0] = findAllStaff;
    defaultWindow.dataFetchers.admin[1] = findAllMurid;
    defaultWindow.dataFetchers.admin[2] = findAllPengajar;
    defaultWindow.dataFetchers.admin[3] = findAllRuangan;
    defaultWindow.dataFetchers.admin[4] = findAllMapel;

    // Logo Sibela
    defaultWindow.images.logo = LoadTexture("assets/images/sibela_Versi2.png");
    // Logo Robot Sibela
    defaultWindow.images.logoRobot = LoadTexture("assets/images/Robot_Sibela.png");

    defaultWindow.isLoading = true;
    defaultWindow.loadingTime = 0.0f;

    // findAllStaff(&defaultWindow.datas, defaultWindow.dbConn);
    SetTargetFPS(120);

    while (!WindowShouldClose() && !defaultWindow.shouldClose)
    {
        updateView(&defaultWindow);
        BeginDrawing();
        drawRootView(&defaultWindow);
        EndDrawing();
    }

    disconnectDb(&dbConn);
    UnloadFont(poppinsMedium);
    UnloadFont(poppinsRegular);
    UnloadFont(poppinsMediumItalic);
    UnloadTexture(defaultWindow.images.logo);
    UnloadTexture(defaultWindow.images.logoRobot);
    UnloadTexture(defaultWindow.members[0].image);
    UnloadTexture(defaultWindow.members[1].image);
    UnloadTexture(defaultWindow.members[2].image);
    UnloadTexture(defaultWindow.members[3].image);
    UnloadTexture(defaultWindow.members[4].image);
    CloseWindow();

    return 0;
}
