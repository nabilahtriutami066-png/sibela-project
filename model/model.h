#ifndef model
#define model

typedef void *SQLHANDLE;
typedef SQLHANDLE SQLHDBC;
typedef short SQLSMALLINT;
#include "../types/dbTypes.h"

typedef struct
{
    Staf staffs[100];
    SQLSMALLINT nStaf;
    int page;
    int totalPages;
} data;

typedef struct
{
    Murid murids[100];
    SQLSMALLINT nMurid;
    int page;
    int totalPages;
} dataMurid;

typedef enum
{
    SUCCESS,
    FAILED
} QUERYSTATUS;

void readDBDsn(char target[]);
void initSQLConn(SQLHDBC *dbConn);
void disconnectDb(SQLHDBC *dbConn);

#endif