#ifndef JADWALPERTEMUAN_H
#define JADWALPERTEMUAN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>

#include "../model/model.h"
// #include "../libs/utils.h"
#include "../types/dbTypes.h"
#include "../types/form.h"
#include "jadwalMurid.h"

void findAllJadwalPertemuan(data *datas, int *nPage, SQLHDBC *dbConn, user *authUser);
QUERYSTATUS createJadwalPertemuan(InputField fields[], SQLHDBC *dbConn, user *authUser);
QUERYSTATUS updateJadwalPertemuan(InputField fields[], SQLHDBC *dbConn, user *authUser);
QUERYSTATUS deleteJadwalPertemuan(SQLHDBC *dbConn, JadwalPertemuanWithDetails updatedPertemuan);
void findAllJadwalPertemuanByUserId(data *datas, int *nPage, SQLHDBC *dbConn, user *authUser);

#endif