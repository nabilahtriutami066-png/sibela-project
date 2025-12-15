#ifndef MAPEL_H
#define MAPEL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include "initDb.h"
#include "../model/model.h"
// #include "../libs/utils.h"
#include "../types/dbTypes.h"
#include "../types/form.h"
// #include "../components/header.h"

// void createStaf(int lastIndex);

QUERYSTATUS createMapel(InputField fields[], SQLHDBC *dbConn);
void findAllMapel(data *datas, int *nPage, SQLHDBC *dbConn);
QUERYSTATUS updateMapel(data *datas, int *nPage, SQLHDBC *dbConn, Mapel updatedMapel);
QUERYSTATUS deleteMapel( SQLHDBC *dbConn, Mapel updatedMapel);

#endif