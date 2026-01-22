#ifndef PEMBAYARAN_H
#define PEMBAYARAN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>

#include "../model/model.h"
// #include "../libs/utils.h"
#include "../types/dbTypes.h"
#include "../types/form.h"

void findAllPembayaran(data *datas, int *nPage, SQLHDBC *dbConn, user *authUser);
void findAllPembayaranByUserId(data *datas, int *nPage, SQLHDBC *dbConn, user *authUser);
QUERYSTATUS createPembayaran(InputField fields[], SQLHDBC *dbConn);
void getPembayaranReport(data *datas, int *nPage, SQLHDBC *dbConn, user *authUser);
void findAllPembayaranByDateRange(DateRangeSelector range, data *datas, int *nPage, SQLHDBC *dbConn, user *authUser);

#endif