#include "validator.h"

int validateInput(InputField *input)
{
    int valid = 0;
    switch (input->type)
    {
    case DATEINPUT:
        valid = strlen(input->value.text) > 0 && strcspn(input->value.text, "-") != strlen(input->value.text) && strcspn(input->value.text, ":") != strlen(input->value.text);
        if (!valid)
        {
            input->value.validation.isInputInvalid = 1;
            strcpy(input->value.validation.errMessage, "Tanggal Invalid");
        }
        break;
    case CUSTOMMODAL:
    case CUSTOMMODALMULTI:

        break;
    default:
        valid = strlen(input->value.text) > 0;
        break;
    }

    return valid;
}