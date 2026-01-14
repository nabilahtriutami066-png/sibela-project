#include "pembayaran.h"
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void findAllPembayaran(data *datas, int *nPage, SQLHDBC *dbConn, user *authUser)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];

    SQLLEN rowsFetched = 0;
    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    ret = SQLExecDirect(stmt, (SQLCHAR *)"SELECT COUNT(*) AS row_count FROM pembayaran", SQL_NTS);
    if (SQL_SUCCEEDED(ret))
    {
        if (SQL_SUCCEEDED(SQLFetch(stmt)))
        {
            SQLGetData(stmt, 1, SQL_C_LONG, &count, 0, NULL);
        }
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    *nPage = (int)ceil((float)count / 10);
    int limit = 10;
    int offset = (datas->page - 1) * limit;
    *nPage = (int)ceil((float)count / limit);

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    if (datas->sortBy == DESC)
        SQLPrepare(stmt, (SQLCHAR *)"SELECT p.id_num, id_pembayaran, p.id_murid,m.nama AS 'nama_murid', tanggal_pembayaran, jumlah_pembayaran, dikonfirmasi, p.id_staff,s.nama AS 'nama_staff', mtd_pembayaran FROM pembayaran p LEFT JOIN murid m ON m.id_murid = p.id_murid LEFT JOIN staff s ON s.id_staff = p.id_staff ORDER BY tanggal_pembayaran DESC OFFSET ? ROWS FETCH NEXT ? ROWS ONLY", SQL_NTS);
    else
        SQLPrepare(stmt, (SQLCHAR *)"SELECT p.id_num, id_pembayaran, p.id_murid,m.nama AS 'nama_murid', tanggal_pembayaran, jumlah_pembayaran, dikonfirmasi, p.id_staff,s.nama AS 'nama_staff', mtd_pembayaran FROM pembayaran p LEFT JOIN murid m ON m.id_murid = p.id_murid LEFT JOIN staff s ON s.id_staff = p.id_staff ORDER BY tanggal_pembayaran ASC OFFSET ? ROWS FETCH NEXT ? ROWS ONLY", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &offset, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &limit, 0, NULL);

    ret = SQLExecute(stmt);
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        int i = (int)rowsFetched;

        SQLGetData(stmt, 1, SQL_C_LONG,
                   &datas->pembayarans[i].id_num, sizeof(datas->pembayarans[i].id_num), NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR,
                   &datas->pembayarans[i].id_pembayaran, sizeof(datas->pembayarans[i].id_pembayaran), NULL);
        SQLGetData(stmt, 3, SQL_C_CHAR,
                   &datas->pembayarans[i].id_murid, sizeof(datas->pembayarans[i].id_murid), NULL);
        SQLGetData(stmt, 4, SQL_C_CHAR,
                   datas->pembayarans[i].nama_murid, sizeof(datas->pembayarans[i].nama_murid), NULL);
        SQLGetData(stmt, 5, SQL_C_CHAR,
                   &datas->pembayarans[i].tanggal_pembayaran, sizeof(datas->pembayarans[i].tanggal_pembayaran), NULL);
        SQLGetData(stmt, 6, SQL_C_LONG,
                   &datas->pembayarans[i].jumlah_pembayaran, sizeof(datas->pembayarans[i].jumlah_pembayaran), NULL);
        SQLGetData(stmt, 7, SQL_C_BIT,
                   &datas->pembayarans[i].dikonfirmasi, sizeof(datas->pembayarans[i].dikonfirmasi), NULL);
        SQLGetData(stmt, 8, SQL_C_CHAR,
                   &datas->pembayarans[i].id_staff, sizeof(datas->pembayarans[i].id_staff), NULL);
        SQLGetData(stmt, 9, SQL_C_CHAR,
                   &datas->pembayarans[i].nama_staff, sizeof(datas->pembayarans[i].nama_staff), NULL);
        SQLGetData(stmt, 10, SQL_C_CHAR,
                   &datas->pembayarans[i].mtd_pembayaran, sizeof(datas->pembayarans[i].mtd_pembayaran), NULL);
        rowsFetched++;
    }
    datas->nPembayaran = rowsFetched;
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);
}
void findAllPembayaranByUserId(data *datas, int *nPage, SQLHDBC *dbConn, user *authUser)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count = 0;
    SQLUSMALLINT rowStatus[100];

    SQLLEN rowsFetched = 0;
    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);

    SQLPrepare(stmt, (SQLCHAR *)"SELECT COUNT(*) AS row_count FROM pembayaran WHERE id_murid =  ?", SQL_NTS);

    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(authUser->id), 0, authUser->id, 0, NULL);

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
    if (datas->sortBy == DESC)
        SQLPrepare(stmt, (SQLCHAR *)"SELECT p.id_num, id_pembayaran, p.id_murid,m.nama AS 'nama_murid', tanggal_pembayaran, jumlah_pembayaran, dikonfirmasi, p.id_staff,s.nama AS 'nama_staff', mtd_pembayaran FROM pembayaran p LEFT JOIN murid m ON m.id_murid = p.id_murid LEFT JOIN staff s ON s.id_staff = p.id_staff WHERE p.id_murid = ? ORDER BY tanggal_pembayaran DESC, id_pembayaran ASC OFFSET ? ROWS FETCH NEXT ? ROWS ONLY", SQL_NTS);
    else
        SQLPrepare(stmt, (SQLCHAR *)"SELECT p.id_num, id_pembayaran, p.id_murid,m.nama AS 'nama_murid', tanggal_pembayaran, jumlah_pembayaran, dikonfirmasi, p.id_staff,s.nama AS 'nama_staff', mtd_pembayaran FROM pembayaran p LEFT JOIN murid m ON m.id_murid = p.id_murid LEFT JOIN staff s ON s.id_staff = p.id_staff WHERE p.id_murid = ? ORDER BY tanggal_pembayaran ASC, id_pembayaran DESC OFFSET ? ROWS FETCH NEXT ? ROWS ONLY", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(authUser->id), 0, authUser->id, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &offset, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &limit, 0, NULL);

    ret = SQLExecute(stmt);
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        char dateBuff[50];
        int i = (int)rowsFetched;

        SQLGetData(stmt, 1, SQL_C_LONG,
                   &datas->pembayarans[i].id_num, sizeof(datas->pembayarans[i].id_num), NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR,
                   &datas->pembayarans[i].id_pembayaran, sizeof(datas->pembayarans[i].id_pembayaran), NULL);
        SQLGetData(stmt, 3, SQL_C_CHAR,
                   &datas->pembayarans[i].id_murid, sizeof(datas->pembayarans[i].id_murid), NULL);
        SQLGetData(stmt, 4, SQL_C_CHAR,
                   datas->pembayarans[i].nama_murid, sizeof(datas->pembayarans[i].nama_murid), NULL);
        SQLGetData(stmt, 5, SQL_C_CHAR,
                   &datas->pembayarans[i].tanggal_pembayaran, sizeof(datas->pembayarans[i].tanggal_pembayaran), NULL);
        SQLGetData(stmt, 6, SQL_C_LONG,
                   &datas->pembayarans[i].jumlah_pembayaran, sizeof(datas->pembayarans[i].jumlah_pembayaran), NULL);
        SQLGetData(stmt, 7, SQL_C_BIT,
                   &datas->pembayarans[i].dikonfirmasi, sizeof(datas->pembayarans[i].dikonfirmasi), NULL);
        SQLGetData(stmt, 8, SQL_C_CHAR,
                   &datas->pembayarans[i].id_staff, sizeof(datas->pembayarans[i].id_staff), NULL);
        SQLGetData(stmt, 9, SQL_C_CHAR,
                   &datas->pembayarans[i].nama_staff, sizeof(datas->pembayarans[i].nama_staff), NULL);
        SQLGetData(stmt, 10, SQL_C_CHAR,
                   &datas->pembayarans[i].mtd_pembayaran, sizeof(datas->pembayarans[i].mtd_pembayaran), NULL);
        rowsFetched++;
    }
    datas->nPembayaran = rowsFetched;
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);
}

QUERYSTATUS createPembayaran(InputField fields[], SQLHDBC *dbConn)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;

    Pembayaran newPayment;

    newPayment.dikonfirmasi = 1;
    strcpy(newPayment.id_staff, fields[0].value.text);
    strcpy(newPayment.id_murid, fields[1].value.text);
    // strcpy(newPayment.jumlah_pembayaran, fields[2].value.text);
    newPayment.jumlah_pembayaran = (double)atoi(fields[2].value.text);
    strcpy(newPayment.mtd_pembayaran, fields[3].value.text);

    // if (newPayment.jumlah_pembayaran <= 0)
    // return FAILED;
    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"INSERT INTO pembayaran (id_staff, dikonfirmasi, id_murid, jumlah_pembayaran, mtd_pembayaran) VALUES (?,?,?,?,?)", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newPayment.id_staff), 0, newPayment.id_staff, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_BIT, SQL_BIT, sizeof(int), 0, &newPayment.dikonfirmasi, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newPayment.id_murid), 0, newPayment.id_murid, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_NUMERIC, sizeof(double), 0, &newPayment.jumlah_pembayaran, 0, NULL);
    SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newPayment.mtd_pembayaran), 0, newPayment.mtd_pembayaran, 0, NULL);
    ret = SQLExecute(stmt);

    if (SQL_SUCCEEDED(ret))
    {
        ret = SQLFetch(stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);

    switch (ret)
    {
    case SQL_SUCCESS:
        return SUCCESS;

    default:
        return FAILED;
    }
}

void getPembayaranReport(data *datas, int *nPage, SQLHDBC *dbConn, user *authUser)
{
    SQLHSTMT stmt;
    SQLRETURN ret;

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);

    SQLPrepare(stmt, (SQLCHAR *)"SELECT SUM(p.jumlah_pembayaran) AS 'TOTAL_BulanIni', COUNT(*) AS 'jumlah_pembayaran' FROM pembayaran p WHERE p.tanggal_pembayaran >= DATEFROMPARTS(YEAR(GETDATE()), MONTH(GETDATE()), 1) AND p.tanggal_pembayaran <= GETDATE()", SQL_NTS);

    ret = SQLExecute(stmt);
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        SQLGetData(stmt, 1, SQL_C_LONG,
                   &datas->pembayaranReport.sumThisMonth, sizeof(datas->pembayaranReport.sumThisMonth), NULL);
        SQLGetData(stmt, 2, SQL_C_LONG,
                   &datas->pembayaranReport.totalThisMonth, sizeof(datas->pembayaranReport.totalThisMonth), NULL);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);
}