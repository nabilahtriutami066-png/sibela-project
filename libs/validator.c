#include "validator.h"

int validateInput(InputField *input)
{
    int valid = 1;

    if (input->type != CUSTOMMODAL && input->type != CUSTOMMODALMULTI)
    {
        valid = input->value.charLen > 0;
        if (!valid)
        {
            input->value.validation.isInputInvalid = 1;
            strcpy(input->value.validation.errMessage, "Input tidak boleh kosong!");
        }
    }

    int d, m, y, h, min, s;
    switch (input->type)
    {
    case BUTTONINPUT:
        return 1;
    case DATEINPUT:
        valid = valid && input->value.charLen > 0 && strcspn(input->value.text, "-") != input->value.charLen && sscanf(input->value.text, "%d-%d-%d", &y, &m, &d) == 3 && y > 2025 && m >= 0 && m <= 12 && d >= 1 && d <= 31;
        if (!valid)
        {
            input->value.validation.isInputInvalid = 1;
            strcpy(input->value.validation.errMessage, "Tanggal Invalid");
        }
        break;
    case DATETIMEINPUT:
        valid = valid && input->value.charLen > 0 && strcspn(input->value.text, "-") != input->value.charLen && strcspn(input->value.text, ":") != input->value.charLen && sscanf(input->value.text, "%d-%d-%d %d:%d:%d", &y, &m, &d, &h, &min, &s) == 6 && y > 2025 && m >= 0 && m <= 12 && d >= 1 && d <= 31 && h >= 0 && h <= 23 && min >= 0 && min <= 59 && s >= 0 && s <= 59;
        if (!valid)
        {
            input->value.validation.isInputInvalid = 1;
            strcpy(input->value.validation.errMessage, "Tanggal Invalid");
        }
        break;
    case CUSTOMMODAL:
        break;
    case CUSTOMMODALMULTI:
        break;

    case TINGKATINPUT:
        valid = valid && strcmp(input->value.text, "10") == 0 || strcmp(input->value.text, "11") == 0 || strcmp(input->value.text, "12") == 0;
        if (!valid)
        {
            input->value.validation.isInputInvalid = 1;
            strcpy(input->value.validation.errMessage, "Tingkat hanya bisa bernilai 10, 11, atau 12!");
        }
        break;
    case PAYMENTMETHODINPUT:
        valid = valid && strcmp(input->value.text, "TUNAI") == 0 || strcmp(input->value.text, "TRANSFER") == 0;
        if (!valid)
        {
            input->value.validation.isInputInvalid = 1;
            strcpy(input->value.validation.errMessage, "Metode hanya bisa bernilai 'TRANSFER' atau 'TUNAI'");
        }
        break;
    case EMAILINPUT:
        valid = valid && strcspn(input->value.text, "@") != input->value.charLen && strcspn(input->value.text, ".") != input->value.charLen;
        if (!valid)
        {
            input->value.validation.isInputInvalid = 1;
            strcpy(input->value.validation.errMessage, "EMAIL invalid!");
        }
        break;
    case PHONENOINPUT:
        valid = valid && strcspn(input->value.text, "0") == 0 && input->value.charLen <= 13 && input->value.charLen >= 10;
        if (!valid)
        {
            input->value.validation.isInputInvalid = 1;
            strcpy(input->value.validation.errMessage, "No. HP invalid!");
        }
        break;

    case ROLEINPUT:
        valid = valid && strcmp(input->value.text, "FRONTDESK") == 0 || strcmp(input->value.text, "MANAJER") == 0;
        if (!valid)
        {
            input->value.validation.isInputInvalid = 1;
            strcpy(input->value.validation.errMessage, "Role hanya bisa bernilai 'FRONTDESK' atau 'MANAJER'");
        }
        break;
    default:
        valid = valid && input->value.charLen > 0;
        if (!valid)
        {
            input->value.validation.isInputInvalid = 1;
            strcpy(input->value.validation.errMessage, "Input tidak boleh kosong!");
        }
        break;
    }

    return valid;
}