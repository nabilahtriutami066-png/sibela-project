#include "staf.h"
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

Staf findStafbyEmail(char email[], SQLHDBC *dbConn)
{
    Staf foundRecord;
    SQLHSTMT stmt;
    SQLRETURN ret;
    char dateBuff[50];
    SQLUSMALLINT rowStatus[100];
    foundRecord.id_num = -1;

    printf("Finding staf\n");
    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);

    SQLPrepare(stmt, (SQLCHAR *)"SELECT * FROM staff WHERE email = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(email), 0, email, 0, NULL);
    ret = SQLExecute(stmt);

    if (SQL_SUCCEEDED(ret))
    {
        ret = SQLFetch(stmt);

        switch (ret)
        {
        case SQL_NO_DATA:
            foundRecord.id_num = -1;
            break;

        default:
            SQLGetData(stmt, 1, SQL_C_LONG,
                       &foundRecord.id_num, sizeof(foundRecord.id_num), NULL);
            SQLGetData(stmt, 2, SQL_C_CHAR,
                       &foundRecord.id_staff, sizeof(foundRecord.id_staff), NULL);
            SQLGetData(stmt, 3, SQL_C_CHAR,
                       &foundRecord.role, sizeof(foundRecord.role), NULL);
            SQLGetData(stmt, 4, SQL_C_CHAR,
                       &foundRecord.nama, sizeof(foundRecord.nama), NULL);
            SQLGetData(stmt, 5, SQL_C_CHAR,
                       dateBuff, sizeof(dateBuff), NULL);
            foundRecord.tanggal_lahir = parseDate(dateBuff);
            SQLGetData(stmt, 6, SQL_C_CHAR,
                       dateBuff, sizeof(dateBuff), NULL);
            foundRecord.tanggal_masuk = parseDate(dateBuff);
            SQLGetData(stmt, 7, SQL_C_CHAR,
                       &foundRecord.no_hp, sizeof(foundRecord.no_hp), NULL);
            SQLGetData(stmt, 8, SQL_C_CHAR,
                       &foundRecord.password, sizeof(foundRecord.password), NULL);
            SQLGetData(stmt, 9, SQL_C_CHAR,
                       &foundRecord.email, sizeof(foundRecord.email), NULL);
            break;
        }
    }
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);

    return foundRecord;
}

void findAllStaff(data *datas, int *nPage, SQLHDBC *dbConn)
{

    if (datas->nStaf > 0)
        return;

    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];

    SQLLEN rowsFetched = 0;
    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    ret = SQLExecDirect(stmt, (SQLCHAR *)"SELECT COUNT(*) AS row_count FROM staff", SQL_NTS);
    if (SQL_SUCCEEDED(ret))
    {
        if (SQL_SUCCEEDED(SQLFetch(stmt)))
        {
            SQLGetData(stmt, 1, SQL_C_LONG, &count, 0, NULL);
        }
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    *nPage = (int)ceil((float)count / 10);
    printf("awikwok %d\n", *nPage);
    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    ret = SQLExecDirect(stmt, (SQLCHAR *)"SELECT * FROM staff", SQL_NTS);
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        printf("Successfully fetched %lld rows\n", rowsFetched);
        char dateBuff[50];
        int i = (int)rowsFetched;
        printf("awikwok %d\n", i);

        SQLGetData(stmt, 1, SQL_C_LONG,
                   &datas->staffs[i].id_num, sizeof(datas->staffs[i].id_num), NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR,
                   &datas->staffs[i].id_staff, sizeof(datas->staffs[i].id_staff), NULL);
        SQLGetData(stmt, 3, SQL_C_CHAR,
                   &datas->staffs[i].role, sizeof(datas->staffs[i].role), NULL);
        SQLGetData(stmt, 4, SQL_C_CHAR,
                   &datas->staffs[i].nama, sizeof(datas->staffs[i].nama), NULL);
        SQLGetData(stmt, 5, SQL_C_CHAR,
                   dateBuff, sizeof(dateBuff), NULL);
        datas->staffs[rowsFetched].tanggal_lahir = parseDate(dateBuff);
        SQLGetData(stmt, 6, SQL_C_CHAR,
                   dateBuff, sizeof(dateBuff), NULL);
        datas->staffs[rowsFetched].tanggal_masuk = parseDate(dateBuff);
        SQLGetData(stmt, 7, SQL_C_CHAR,
                   &datas->staffs[i].no_hp, sizeof(datas->staffs[i].no_hp), NULL);
        SQLGetData(stmt, 8, SQL_C_CHAR,
                   &datas->staffs[i].password, sizeof(datas->staffs[i].password), NULL);
        SQLGetData(stmt, 9, SQL_C_CHAR,
                   &datas->staffs[i].email, sizeof(datas->staffs[i].email), NULL);
        printf("staff %d: %s\n", i, datas->staffs[i].nama);
        rowsFetched++;
    }
    datas->nStaf = rowsFetched;
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);
}

QUERYSTATUS createStaff(data *datas, int *nPage, SQLHDBC *dbConn, Staf newStaff)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"INSERT INTO staff (nama, tanggal_lahir, no_hp, password, email) VALUES (?,?,?,?,?)", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newStaff.nama), 0, newStaff.nama, 0, NULL);
    dateBuff = parseDateToString(newStaff.tanggal_lahir);
    printf("date: %s\n", dateBuff);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_DATE, strlen("2028-10-20"), 0, "2028-10-20", 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newStaff.no_hp), 0, newStaff.no_hp, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newStaff.password), 0, newStaff.password, 0, NULL);
    SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newStaff.email), 0, newStaff.email, 0, NULL);
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

QUERYSTATUS updateStaff(data *datas, int *nPage, SQLHDBC *dbConn, Staf updatedStaff)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"UPDATE staff SET nama = ?, tanggal_lahir = ?, no_hp = ?, password = ?, email = ? WHERE id_staff = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedStaff.nama), 0, updatedStaff.nama, 0, NULL);
    dateBuff = parseDateToString(updatedStaff.tanggal_lahir);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_DATE, strlen(dateBuff), 0, dateBuff, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedStaff.no_hp), 0, updatedStaff.no_hp, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedStaff.password), 0, updatedStaff.password, 0, NULL);
    SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedStaff.email), 0, updatedStaff.email, 0, NULL);
    SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedStaff.id_staff), 0, updatedStaff.id_staff, 0, NULL);
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

QUERYSTATUS deleteStaff(data *datas, int *nPage, SQLHDBC *dbConn, Staf updatedStaff)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"DELETE FROM staff WHERE id_staff = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedStaff.id_staff), 0, updatedStaff.id_staff, 0, NULL);
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