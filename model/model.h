#ifndef model
#define model

typedef void *SQLHANDLE;
typedef SQLHANDLE SQLHDBC;
typedef short SQLSMALLINT;
#include "../types/dbTypes.h"

typedef struct
{
    char id[20];
    char nama[100];
    char role[20];
} user;

typedef enum
{
    ASC = 30,
    DESC
} SORTBY;

typedef struct
{
    int monthFrom;
    int monthTo;
    int yearFrom;
    int yearTo;
} DateRangeSelector;

typedef struct
{
    Staf staffs[100];
    SQLSMALLINT nStaf;
    Pengajar pengajars[100];
    SQLSMALLINT nPengajar;
    Murid murids[100];
    SQLSMALLINT nMurid;
    Ruangan ruangans[100];
    SQLSMALLINT nRuangan;
    Mapel Mapels[100];
    SQLSMALLINT nMapel;
    Materi Materis[100];
    SQLSMALLINT nMateri;
    JadwalPertemuanWithDetails jadwalPertemuans[100];
    SQLSMALLINT nJadwalPertemuan;
    PembayaranFetchAll pembayarans[100];
    SQLSMALLINT nPembayaran;
    MuridAbsensi muridAbsensis[100];
    SQLSMALLINT nMuridAbsensi;

    PembayaranReport pembayaranReport;

    SORTBY sortBy;
    int page;
    int totalPages;
} data;

typedef enum
{
    SUCCESS,
    FAILED
} QUERYSTATUS;

void readDBDsn(char target[]);
void initSQLConn(SQLHDBC *dbConn);
void disconnectDb(SQLHDBC *dbConn);

#endif