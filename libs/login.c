#include "login.h"

void loginFunction(windowModel *windowM)
{

    switch (windowM->currWindow)
    {
    case LOGINSTAFF:
        Staf loginStaf = findStafbyEmail(windowM->loginData.email.text, windowM->dbConn);

        if (loginStaf.id_num == -1)
            return;
        // printf("loginaw: %d\n", strcmp(loginStaf.password, windowM->loginData.password.text));

        if (strcmp(loginStaf.password, windowM->loginData.password.text) == 0)
        {

            strcpy(windowM->loginData.email.text, "\0");
            strcpy(windowM->loginData.password.text, "\0");
            windowM->loginData.password.charLen = 0;
            windowM->loginData.email.charLen = 0;

            strcpy(windowM->authUser.id, loginStaf.id_staff);
            strcpy(windowM->authUser.nama, loginStaf.nama);
            strcpy(windowM->authUser.role, loginStaf.role);
            windowM->currWindow = STAFHOME;
        }
        break;
    case LOGINMURID:
        break;
    case LOGINPENGAJAR:
        break;
    }
}