#ifndef murid
#define murid

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include "../model/model.h"
#include "../libs/utils.h"
#include "../types/dbTypes.h"

Murid findMuridbyPhoneNum(char PhoneNum[], SQLHDBC *dbConn);

// CRUD
QUERYSTATUS createMurid(dataMurid *datas, int *nPage, SQLHDBC *dbConn, Murid newMurid);
void findAllMurid(dataMurid *datas, int *nPage, SQLHDBC *dbConn);
QUERYSTATUS updateMurid(dataMurid *datas, int *nPage, SQLHDBC *dbConn, Murid updatedMurid);
QUERYSTATUS deleteMurid(dataMurid *datas, int *nPage, SQLHDBC *dbConn, Murid updatedMurid);

#endif