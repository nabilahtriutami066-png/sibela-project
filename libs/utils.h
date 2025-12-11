#ifndef utils
#define utils

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <string.h>
#include <time.h>

void readAscii(char name[], char dest[]);
time_t parseDate(char strDate[]);
char *parseDateToString(time_t cDate);

#endif