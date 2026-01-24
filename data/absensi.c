#include "absensi.h"
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

void getMuridsbyJadwalPertemuan(data *datas, int *nPage, SQLHDBC *dbConn, JadwalPertemuanWithDetails *jadwal)
{

    SQLHSTMT stmt;
    SQLRETURN ret;
    int count = 0;
    SQLUSMALLINT rowStatus[100];
    SQLLEN isAbsensiNull;

    SQLLEN rowsFetched = 0;
    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);

    SQLPrepare(stmt, (SQLCHAR *)"SELECT COUNT(*) FROM jadwal_murid jm WHERE jm.id_pertemuan = ?", SQL_NTS);

    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(jadwal->id_pertemuan), 0, jadwal->id_pertemuan, 0, NULL);

    ret = SQLExecute(stmt);
    if (SQL_SUCCEEDED(ret))
    {
        if (SQL_SUCCEEDED(SQLFetch(stmt)))
        {
            SQLGetData(stmt, 1, SQL_C_LONG, &count, 0, NULL);
        }
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    *nPage = (int)ceilf((float)count / 10.0);
    int limit = 10;
    int offset = (datas->page - 1) * limit;
    *nPage = (int)ceilf((float)count / limit);

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"SELECT m.id_murid, m.nama, abs.isHadir,abs.alasan, abs.waktu_absensi FROM jadwal_murid jm INNER JOIN murid m ON jm.id_murid = m.id_murid LEFT JOIN absensi abs ON abs.id_pertemuan = jm.id_pertemuan AND abs.id_murid = m.id_murid  WHERE jm.id_pertemuan = ? ORDER BY m.nama ASC", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(jadwal->id_pertemuan), 0, jadwal->id_pertemuan, 0, NULL);
    // SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &offset, 0, NULL);
    // SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &limit, 0, NULL);

    ret = SQLExecute(stmt);
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        char dateBuff[50];
        int i = (int)rowsFetched;
        // m.id_murid, m.nama, abs.isHadir,abs.alasan, abs.waktu_absensi
        SQLGetData(stmt, 1, SQL_C_CHAR,
                   &datas->muridAbsensis[i].id_murid, sizeof(datas->muridAbsensis[i].id_murid), NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR,
                   &datas->muridAbsensis[i].nama_murid, sizeof(datas->muridAbsensis[i].nama_murid), NULL);
        SQLGetData(stmt, 3, SQL_C_BIT,
                   &datas->muridAbsensis[i].isHadir, sizeof(datas->muridAbsensis[i].isHadir), &isAbsensiNull);
        if (isAbsensiNull == SQL_NULL_DATA)
        {
            datas->muridAbsensis[i].isHadir = 0;
            strcpy(datas->muridAbsensis[i].alasan, "");
            datas->muridAbsensis[i].charLenAlasan = 0;
            datas->muridAbsensis[i].existed = 0;
            strcpy(datas->muridAbsensis[i].waktu_absensi, "");
        }
        else
        {
            SQLGetData(stmt, 4, SQL_C_CHAR,
                       &datas->muridAbsensis[i].alasan, sizeof(datas->muridAbsensis[i].alasan), NULL);
            datas->muridAbsensis[i].charLenAlasan = strlen(datas->muridAbsensis[i].alasan);
            SQLGetData(stmt, 5, SQL_C_CHAR,
                       &datas->muridAbsensis[i].waktu_absensi, sizeof(datas->muridAbsensis[i].waktu_absensi), NULL);
            datas->muridAbsensis[i].existed = 1;
        }
        rowsFetched++;
    }
    datas->nMuridAbsensi = rowsFetched;
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);
}

QUERYSTATUS createAbsensi(MuridAbsensi murids[], int nMurid, char id_pert[], SQLHDBC *dbConn, user authUser)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;
    Absensi newAbsensi;
    strcpy(newAbsensi.id_pertemuan, id_pert);
    strcpy(newAbsensi.id_pengajar, authUser.id);

    SQLLEN nullDataInd = SQL_NULL_DATA;

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    for (int i = 0; i < nMurid; i++)
    {
        strcpy(newAbsensi.id_murid, murids[i].id_murid);
        strcpy(newAbsensi.alasan, murids[i].alasan);
        newAbsensi.isHadir = murids[i].isHadir;
        if (murids[i].existed)
        {
            SQLPrepare(stmt, (SQLCHAR *)"UPDATE absensi SET isHadir = ?, alasan = ? WHERE id_pertemuan = ? AND id_murid = ?", SQL_NTS);
            SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_BIT, SQL_BIT, sizeof(newAbsensi.isHadir), 0, &newAbsensi.isHadir, 0, NULL);
            SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newAbsensi.alasan), 0, newAbsensi.alasan, 0, newAbsensi.isHadir ? NULL : &nullDataInd);
            SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newAbsensi.id_pertemuan), 0, newAbsensi.id_pertemuan, 0, NULL);
            SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newAbsensi.id_murid), 0, newAbsensi.id_murid, 0, NULL);
        }
        else
        {
            SQLPrepare(stmt, (SQLCHAR *)"INSERT INTO absensi (id_pertemuan, id_murid,id_pengajar, isHadir, alasan) VALUES (?,?,?,?,?)", SQL_NTS);
            SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newAbsensi.id_pertemuan), 0, newAbsensi.id_pertemuan, 0, NULL);
            SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newAbsensi.id_murid), 0, newAbsensi.id_murid, 0, NULL);
            SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newAbsensi.id_pengajar), 0, newAbsensi.id_pengajar, 0, NULL);
            SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_BIT, SQL_BIT, sizeof(newAbsensi.isHadir), 0, &newAbsensi.isHadir, 0, NULL);
            SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newAbsensi.alasan), 0, newAbsensi.alasan, 0, newAbsensi.isHadir ? NULL : &nullDataInd);
        }
        ret = SQLExecute(stmt);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);

    switch (ret)
    {
    case SQL_ERROR:
        return FAILED;

    default:
        return SUCCESS;
    }
}

QUERYSTATUS deleteteAbsensiByPertemuanIDMuridId(MuridAbsensi murid, char id_pert[], SQLHDBC *dbConn)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);

    SQLPrepare(stmt, (SQLCHAR *)"DELETE FROM absensi WHERE id_pertemuan = ? AND id_murid = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(id_pert), 0, id_pert, 0, NULL);
    ret = SQLExecute(stmt);

    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);

    switch (ret)
    {
    case SQL_ERROR:
        return FAILED;

    default:
        return SUCCESS;
    }
}