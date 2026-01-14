#include "validator.h"

int validateInput(InputField *input)
{
    int valid = 1;
    switch (input->type)
    {
    case BUTTONINPUT:
        return 1;
    case DATEINPUT:
        valid = input->value.charLen > 0 && strcspn(input->value.text, "-") != input->value.charLen;
        if (!valid)
        {
            input->value.validation.isInputInvalid = 1;
            strcpy(input->value.validation.errMessage, "Tanggal Invalid");
        }
        break;
    case DATETIMEINPUT:
        valid = input->value.charLen > 0 && strcspn(input->value.text, "-") != input->value.charLen && strcspn(input->value.text, ":") != input->value.charLen;
        if (!valid)
        {
            input->value.validation.isInputInvalid = 1;
            strcpy(input->value.validation.errMessage, "Tanggal Invalid");
        }
        break;
    case CUSTOMMODAL:
    case CUSTOMMODALMULTI:

        break;

    case EMAILINPUT:
        valid = strcspn(input->value.text, "@") != input->value.charLen && strcspn(input->value.text, ".") != input->value.charLen;
        if (!valid)
        {
            input->value.validation.isInputInvalid = 1;
            strcpy(input->value.validation.errMessage, "EMAIL invalid!");
        }
        break;
    default:
        valid = input->value.charLen > 0;
        if (!valid)
        {
            input->value.validation.isInputInvalid = 1;
            strcpy(input->value.validation.errMessage, "Input tidak boleh kosong!");
        }
        break;
    }
    valid = input->value.charLen > 0;
    if (!valid)
    {
        input->value.validation.isInputInvalid = 1;
        strcpy(input->value.validation.errMessage, "Input tidak boleh kosong!");
    }

    return valid;
}