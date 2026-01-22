#include "utils.h"

void readAscii(char name[], char dest[])
{
    FILE *ascii_file;
    char line[256];
    const char filename[150];

    sprintf(filename, "assets/ascii/%s", name);

    ascii_file = fopen(filename, "r");
    if (ascii_file == NULL)
    {
        perror(filename);
        perror("Error opening file");
    }

    while (fgets(line, sizeof(line), ascii_file) != NULL)
    {
        strcat(dest, line);
    }

    fclose(ascii_file);
}

time_t parseDate(char strDate[])
{
    struct tm tm_info = {0};

    sscanf(strDate, "%d-%d-%d %d:%d:%d", &tm_info.tm_year, &tm_info.tm_mon, &tm_info.tm_mday, &tm_info.tm_hour, &tm_info.tm_min, &tm_info.tm_sec);
    tm_info.tm_year -= 1900;

    return mktime(&tm_info);
}

char *parseDateToString(time_t cDate)
{
    char *dateBuff = (char *)malloc(20 * sizeof(char));
    struct tm *parsedDate;

    if (dateBuff == NULL) return NULL;
    
    parsedDate = localtime(&cDate);

    snprintf(dateBuff, 20, "%d-%d-%d", parsedDate->tm_year + 1900, parsedDate->tm_mon, parsedDate->tm_mday);

    return dateBuff;
}

void copyStringData(char src[], InputParams *dest)
{
    strncpy(dest->text, src, 99);
    dest->text[99] = '\0';
    dest->charLen = strlen(src);
}

void copySelectData(char label[], char value[], SelectProp *dest)
{
    strncpy(dest->label, label, 99);
    dest->label[99] = '\0';
    strncpy(dest->value, value, 99);
    dest->value[99] = '\0';
}

char *intToString(int i)
{
    char *buff = (char *)malloc(20 * sizeof(char));
    if (buff == NULL) return NULL;
    
    snprintf(buff, 20, "%d", i);

    return buff;
}

void clearFields(InputField fields[])
{
    for (int i = 0; i < 10; i++)
    {
        fields[i].value.charLen = 0;
        fields[i].value.text[0] = '\0';
        fields[i].value.selected = -1;
        for (int j = 0; j < 8; j++)
        {
            fields[i].value.multiValue[j][0] = '\0';
        }
    }
}

void clearSelects(Select (*fields)[])
{
    for (int i = 0; i < 6; i++)
    {
        (*fields)[i] = (Select){};
    }
}

int isOptionInMultiSelected(SelectProp target, SelectProp domain[], int nDomain)
{
    for (int i = 0; i < nDomain; i++)
    {
        if (strcmp(domain[i].value, target.value) == 0)
            return 1;
    }

    return 0;
}

int findIdxByTargetProp(SelectProp target, SelectProp domain[], int nDomain)
{
    for (int i = 0; i < nDomain; i++)
    {
        if (strcmp(domain[i].value, target.value) == 0)
            return i;
    }

    return -1;
}

void popMultiSelectArray(SelectProp target, SelectProp domain[], int *nDomain)
{
    int idx = findIdxByTargetProp(target, domain, *nDomain);
    if (idx == -1)
        return;
    *nDomain -= 1;
    for (int i = idx; i < *nDomain; i++)
    {
        domain[i] = domain[i + 1];
    }
    domain[*nDomain] = (SelectProp){};
}

void paginateAbsensi(MuridAbsensi absensis[], int nAbsensi, int nPage, int page, int *outCount, MuridAbsensi sliced[])
{
    *outCount = 0;
    int start = (page - 1) * 10;
    start = start < nAbsensi ? start : -1;
    int end = nAbsensi - start < 10 && start + 10 >= nAbsensi ? nAbsensi : start + 10;

    if (start >= 0)
    {
        for (int i = start; i < end; i++)
        {
            sliced[*outCount] = absensis[i];
            (*outCount)++;
        }
    }
}