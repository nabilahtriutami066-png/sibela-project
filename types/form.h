#ifndef FORMTYPES
#define FORMTYPES

#include "../model/model.h"

typedef struct
{
    char text[100];
    int charLen;
} InputParams;

typedef enum
{
    TEXTINPUT,
    BUTTONINPUT,
    SHORTINPUT,
    NUMERICINPUT
} InputType;

typedef struct
{
    char label[25];
    InputParams value;
    InputType type;
} InputField;

typedef QUERYSTATUS (*mutationFunc)(InputField fields[], SQLHDBC *dbConn);

typedef struct
{
    InputField fields[10];
    int nField;
    mutationFunc createFunc;
    mutationFunc updateFunction;
    int fieldPerPage;
    int totalPages;
    int offset;
    int lastIndex;
} FORM;

#endif