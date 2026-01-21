#include "window.h"
#define RAYGUI_IMPLEMENTATION
#include "../libs/headers/raygui.h"

void closeToast(TOAST *toast)
{
    *toast = (TOAST){.isToastOpened = 0, .toastMessage = "", .toastTitle = ""};
}
void showToast(TOAST *toast, char title[], char message[])
{

    strcpy(toast->toastTitle, title);
    strcpy(toast->toastMessage, message);
    toast->isToastOpened = 1;
}

void initForm(windowModel *windowM)
{
    windowM->forms.staffPage[STAFF].fields[1] = (InputField){.label = "Nama", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[STAFF].fields[2] = (InputField){.label = "Tanggal Lahir", .type = DATEINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[STAFF].fields[3] = (InputField){.label = "No. HP", .type = PHONENOINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[STAFF].fields[4] = (InputField){.label = "Password", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[STAFF].fields[5] = (InputField){.label = "Email", .type = EMAILINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[STAFF].fields[6] = (InputField){.label = "Submit", .type = BUTTONINPUT};
    windowM->forms.staffPage[MANAJERSTAFF].fields[1] = (InputField){.label = "Nama", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[MANAJERSTAFF].fields[2] = (InputField){.label = "Tanggal Lahir", .type = DATEINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[MANAJERSTAFF].fields[3] = (InputField){.label = "No. HP", .type = PHONENOINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[MANAJERSTAFF].fields[4] = (InputField){.label = "Password", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[MANAJERSTAFF].fields[5] = (InputField){.label = "Email", .type = EMAILINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[MANAJERSTAFF].fields[6] = (InputField){.label = "Role", .type = ROLEINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[MANAJERSTAFF].fields[7] = (InputField){.label = "Submit", .type = BUTTONINPUT};
    windowM->forms.staffPage[MURID].fields[1] = (InputField){.label = "Nama", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[MURID].fields[2] = (InputField){.label = "Tanggal Lahir", .type = DATEINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[MURID].fields[3] = (InputField){.label = "No HP", .type = PHONENOINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[MURID].fields[4] = (InputField){.label = "Password", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[MURID].fields[5] = (InputField){.label = "Tingkat", .type = TINGKATINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[MURID].fields[6] = (InputField){.label = "Submit", .type = BUTTONINPUT};
    windowM->forms.staffPage[PENGAJAR].fields[1] = (InputField){.label = "Nama", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[PENGAJAR].fields[2] = (InputField){.label = "Tanggal Lahir", .type = DATEINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[PENGAJAR].fields[3] = (InputField){.label = "No HP", .type = PHONENOINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[PENGAJAR].fields[4] = (InputField){.label = "Password", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[PENGAJAR].fields[5] = (InputField){.label = "Submit", .type = BUTTONINPUT};
    windowM->forms.staffPage[RUANGAN].fields[1] = (InputField){.label = "Lokasi", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[RUANGAN].fields[2] = (InputField){.label = "Deskripsi", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[RUANGAN].fields[3] = (InputField){.label = "Submit", .type = BUTTONINPUT};
    windowM->forms.staffPage[MAPEL].fields[1] = (InputField){.label = "Nama Mapel", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[MAPEL].fields[2] = (InputField){.label = "Submit", .type = BUTTONINPUT};
    windowM->forms.staffPage[STAFF].nField = 6;
    windowM->forms.staffPage[MANAJERSTAFF].nField = 7;
    windowM->forms.staffPage[MURID].nField = 6;
    windowM->forms.staffPage[MAPEL].nField = 2;
    windowM->forms.staffPage[JADWAL].nField = 7;
    windowM->forms.staffPage[PENGAJAR].nField = 5;
    windowM->forms.staffPage[RUANGAN].nField = 3;
    windowM->forms.staffPage[PEMBAYARAN].nField = 4;
    windowM->forms.staffPage[STAFF].fieldPerPage = 4;
    windowM->forms.staffPage[MANAJERSTAFF].fieldPerPage = 4;
    windowM->forms.staffPage[MAPEL].fieldPerPage = 2;
    windowM->forms.staffPage[MURID].fieldPerPage = 4;
    windowM->forms.staffPage[PENGAJAR].fieldPerPage = 5;
    windowM->forms.staffPage[RUANGAN].fieldPerPage = 3;
    windowM->forms.staffPage[STAFF].selectedField = -1;
    windowM->forms.staffPage[MANAJERSTAFF].selectedField = -1;
    windowM->forms.staffPage[MAPEL].selectedField = -1;
    windowM->forms.staffPage[MURID].selectedField = -1;
    windowM->forms.staffPage[PENGAJAR].selectedField = -1;
    windowM->forms.staffPage[RUANGAN].selectedField = -1;
    windowM->forms.staffPage[JADWAL].fieldPerPage = 4;
    windowM->forms.staffPage[PEMBAYARAN].fieldPerPage = 4;
    windowM->forms.staffPage[STAFF].createFunc = createStaff;
    windowM->forms.staffPage[MANAJERSTAFF].createFunc = createStaffManajer;
    windowM->forms.staffPage[STAFF].updateFunction = updateStaff;
    windowM->forms.staffPage[STAFF].updateFunction = updateStaff;
    windowM->forms.staffPage[MAPEL].createFunc = createMapel;
    windowM->forms.staffPage[MAPEL].updateFunction = updateMapel;
    windowM->forms.staffPage[MURID].createFunc = createMurid;
    windowM->forms.staffPage[MURID].updateFunction = updateMurid;
    windowM->forms.staffPage[PENGAJAR].createFunc = createPengajar;
    windowM->forms.staffPage[PENGAJAR].updateFunction = updatePengajar;
    windowM->forms.staffPage[RUANGAN].createFunc = createRuangan;
    windowM->forms.staffPage[RUANGAN].updateFunction = updateRuangan;
    windowM->forms.staffPage[JADWAL].createFunc = createJadwalPertemuan;
    windowM->forms.staffPage[PEMBAYARAN].createFunc = createPembayaran;
    windowM->forms.staffPage[JADWAL].updateFunction = updateJadwalPertemuan;
    windowM->dataFetchers.staffPage[STAFF] = findAllStaff;
    windowM->dataFetchers.staffPage[MANAJERSTAFF] = findAllStaff;
    windowM->dataFetchers.staffPage[MURID] = findAllMurid;
    windowM->dataFetchers.staffPage[PENGAJAR] = findAllPengajar;
    windowM->dataFetchers.staffPage[RUANGAN] = findAllRuangan;
    windowM->dataFetchers.staffPage[MAPEL] = findAllMapel;
    windowM->dataFetchers.staffPage[JADWAL] = findAllJadwalPertemuan;
    windowM->dataFetchers.muridPage[JADWALMURID] = findAllJadwalPertemuanByUserId;
    windowM->dataFetchers.muridPage[PEMBAYARANMURID] = findAllPembayaranByUserId;
    windowM->dataFetchers.staffPage[PEMBAYARAN] = findAllPembayaran;
    windowM->dataFetchers.staffPage[PEMBAYARANREPORT] = getPembayaranReport;

    windowM->forms.staffPage[JADWAL].fields[1] = (InputField){.label = "ID STAFF", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[JADWAL].fields[2] = (InputField){.label = "ID PENGAJAR", .type = CUSTOMMODAL, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[JADWAL].fields[3] = (InputField){.label = "ID RUANGAN", .type = CUSTOMMODAL, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[JADWAL].fields[4] = (InputField){.label = "ID MATERI", .type = CUSTOMMODAL, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[JADWAL].fields[5] = (InputField){.label = "WAKTU", .type = DATETIMEINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[JADWAL].fields[6] = (InputField){.label = "MURID", .type = CUSTOMMODALMULTI, .value = (InputParams){.charLen = 0, .multiValue = {}}};
    windowM->forms.staffPage[JADWAL].fields[7] = (InputField){.label = "SUBMIT", .type = BUTTONINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[JADWAL].optionFetcher[2] = findAllPengajarSelect;
    windowM->forms.staffPage[JADWAL].optionFetcher[3] = findAllRuanganSelect;
    windowM->forms.staffPage[JADWAL].optionFetcher[4] = findAllMateriSelect;
    windowM->forms.staffPage[JADWAL].optionFetcher[6] = findAllMuridSelect;
    windowM->forms.staffPage[JADWAL].selectedField = -1;

    windowM->forms.staffPage[PEMBAYARAN].fields[1] = (InputField){.label = "SISWA", .type = CUSTOMMODAL, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[PEMBAYARAN].fields[2] = (InputField){.label = "Jumlah Bayar", .type = NUMERICINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[PEMBAYARAN].fields[3] = (InputField){.label = "METODE PEMBAYARAN", .type = PAYMENTMETHODINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[PEMBAYARAN].fields[4] = (InputField){.label = "SUBMIT", .type = BUTTONINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[PEMBAYARAN].optionFetcher[1] = findAllMuridSelect;
    windowM->forms.staffPage[PEMBAYARAN].selectedField = -1;

    windowM->selectByPage.staffPage = (Select(*)[6])malloc(sizeof(Select) * 6 * 10);

    windowM->forms.pengajarPage[MATERI].fields[1] = (InputField){.label = "ID MAPEL", .type = CUSTOMMODAL, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.pengajarPage[MATERI].fields[2] = (InputField){.label = "Judul Materi", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.pengajarPage[MATERI].fields[3] = (InputField){.label = "Isi Materi", .type = LONGTEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.pengajarPage[MATERI].fields[4] = (InputField){.label = "SUBMIT", .type = BUTTONINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->dataFetchers.pengajarPage[2] = findAllMateri;
    windowM->forms.pengajarPage[MATERI].createFunc = createMateri;
    windowM->forms.pengajarPage[MATERI].updateFunction = updateMateri;
    windowM->forms.pengajarPage[MATERI].fieldPerPage = 4;
    windowM->forms.pengajarPage[MATERI].nField = 4;
    windowM->forms.pengajarPage[MATERI].optionFetcher[2] = findAllMapelSelect;
    windowM->forms.pengajarPage[MATERI].selectedField = -1;

    windowM->dataFetchers.pengajarPage[ABSENSI] = findAllJadwalPertemuanByUserId;
    windowM->dataFetchers.pengajarPage[PERTEMUAN] = findAllJadwalPertemuanByUserId;
    windowM->pengajarHomeState.absensiPage.activeSubWindow = MAIN;
    windowM->pengajarHomeState.absensiPage.getMurids = getMuridsbyJadwalPertemuan;
    windowM->pengajarHomeState.absensiPage.submitFunc = createAbsensi;
}

void initAssets(windowModel *windowM)
{
    windowM->members[0]
        .image = LoadTexture("assets/images/member/rayyan.png");
    windowM->members[1].image = LoadTexture("assets/images/member/rasya.png");
    windowM->members[2].image = LoadTexture("assets/images/member/bayu.png");
    windowM->members[3].image = LoadTexture("assets/images/member/rijal.png");
    windowM->members[4].image = LoadTexture("assets/images/member/nabilah.png");

    // Logo Sibela
    windowM->images.logo = LoadTexture("assets/images/Logo_SIBELA_New.png");
    // Logo Robot Sibela
    windowM->images.logoRobot = LoadTexture("assets/images/Robot_Sibela.png");

    windowM->isLoading = true;
    windowM->loadingTime = 0.0f;

    // FONTS
    windowM->fontStyle.medium = LoadFontEx("assets/fonts/Poppins-Medium.ttf", 224, 0, 250);
    windowM->fontStyle.thin = LoadFontEx("assets/fonts/Poppins-Thin.ttf", 224, 0, 250);
    windowM->fontStyle.regular = LoadFontEx("assets/fonts/Poppins-Regular.ttf", 224, 0, 250);
    windowM->fontStyle.mediumItalic = LoadFontEx("assets/fonts/Poppins-MediumItalic.ttf", 224, 0, 250);
    windowM->fontStyle.semiBold = LoadFontEx("assets/fonts/Poppins-SemiBold.ttf", 224, 0, 250);
    windowM->fontStyle.bold = LoadFontEx("assets/fonts/Poppins-Bold.ttf", 224, 0, 250);
    windowM->fontStyle.extraBold = LoadFontEx("assets/fonts/Poppins-ExtraBold.ttf", 224, 0, 250);
    windowM->fontStyle.black = LoadFontEx("assets/fonts/Poppins-Black.ttf", 224, 0, 250);
    GuiSetFont(windowM->fontStyle.regular);
    GuiSetStyle(DEFAULT, TEXT_SIZE, (int)32);
    GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, 0x3A475000);
    GuiSetStyle(DEFAULT, BASE_COLOR_FOCUSED, 0x0080FF00);
    GuiSetStyle(DEFAULT, BASE_COLOR_PRESSED, 0x0080FF00);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0xF3F3F3FF);
    GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, 0xF3F3F3FF);
    GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, 0xF3F3F3FF);
    GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, 0xF3F3F3FF);
    GuiSetStyle(DEFAULT, BORDER, 0xF3F3F3FF);
    GuiSetStyle(DEFAULT, BORDER_COLOR_FOCUSED, 0x0080FFFF);
    GuiSetStyle(DEFAULT, BORDER_COLOR_PRESSED, 0x0080FFFF);
    GuiSetStyle(DEFAULT, BORDER_WIDTH, 3);
}

void initWindow(windowModel *windowM)
{
    *windowM = (windowModel){
        .currWindow = LANDINGPAGE,
        .shouldClose = 0,
        .curPos = 0,
        .page = 1,
        .toast = (TOAST){.isToastOpened = 0, .toastMessage = "", .toastTitle = ""},
        .cursorEnabled = 1,
        .selectedPage = -1,
        .isModalShown = 0,
        .activeSubWindow = READ,
        .loginData = {.email = {.charLen = 0, .text = "\0"}, .activeInput = 0}};
    windowM->datas.page = 1;
    windowM->datas.sortBy = ASC;

    initForm(windowM);
    initAssets(windowM);
}

void unloadAssets(windowModel *windowM)
{
    free(windowM->selectByPage.staffPage);
    UnloadFont(windowM->fontStyle.medium);
    UnloadFont(windowM->fontStyle.thin);
    UnloadFont(windowM->fontStyle.regular);
    UnloadFont(windowM->fontStyle.mediumItalic);
    UnloadFont(windowM->fontStyle.semiBold);
    UnloadFont(windowM->fontStyle.bold);
    UnloadFont(windowM->fontStyle.extraBold);
    UnloadFont(windowM->fontStyle.black);
    UnloadTexture(windowM->images.logo);
    UnloadTexture(windowM->images.logoRobot);
    UnloadTexture(windowM->members[0].image);
    UnloadTexture(windowM->members[1].image);
    UnloadTexture(windowM->members[2].image);
    UnloadTexture(windowM->members[3].image);
    UnloadTexture(windowM->members[4].image);
}