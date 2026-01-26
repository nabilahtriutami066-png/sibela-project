#include "jadwalPertemuan.h"
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void findAllJadwalPertemuan(data *datas, int *nPage, SQLHDBC *dbConn, user *authUser)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];

    SQLLEN rowsFetched = 0;
    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    ret = SQLExecDirect(stmt, (SQLCHAR *)"SELECT COUNT(*) AS row_count FROM jadwal_pertemuan", SQL_NTS);
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
        SQLPrepare(stmt, (SQLCHAR *)"SELECT j.id_num, j.id_pertemuan, s.nama AS nama_staff, p.nama AS nama_pengajar,r.lokasi,m.judul_materi, (SELECT COUNT(*) FROM jadwal_murid WHERE jadwal_murid.id_pertemuan = j.id_pertemuan) AS jumlah_murid,j.waktu, s.id_staff, p.id_pengajar, r.id_ruangan, m.id_materi, SUBSTRING(p.nama, 1, 15) + IIF(LEN(p.nama) >= 15,'...','') AS nama_p_trunc, SUBSTRING(m.judul_materi, 1, 20) + IIF(LEN(m.judul_materi) >= 20,'...','') AS nama_p_trunc FROM jadwal_pertemuan j, staff s, pengajar p, ruangan r, materi m WHERE s.id_staff = j.id_staff AND p.id_pengajar = j.id_pengajar AND r.id_ruangan = j.id_ruangan AND m.id_materi = j.id_materi ORDER BY j.waktu DESC OFFSET ? ROWS FETCH NEXT ? ROWS ONLY", SQL_NTS);
    else
        SQLPrepare(stmt, (SQLCHAR *)"SELECT j.id_num, j.id_pertemuan, s.nama AS nama_staff, p.nama AS nama_pengajar,r.lokasi,m.judul_materi, (SELECT COUNT(*) FROM jadwal_murid WHERE jadwal_murid.id_pertemuan = j.id_pertemuan) AS jumlah_murid,j.waktu, s.id_staff, p.id_pengajar, r.id_ruangan, m.id_materi, SUBSTRING(p.nama, 1, 15) + IIF(LEN(p.nama) >= 15,'...','') AS nama_p_trunc, SUBSTRING(m.judul_materi, 1, 20) + IIF(LEN(m.judul_materi) >= 20,'...','') AS nama_p_trunc FROM jadwal_pertemuan j, staff s, pengajar p, ruangan r, materi m WHERE s.id_staff = j.id_staff AND p.id_pengajar = j.id_pengajar AND r.id_ruangan = j.id_ruangan AND m.id_materi = j.id_materi ORDER BY j.waktu ASC OFFSET ? ROWS FETCH NEXT ? ROWS ONLY", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &offset, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &limit, 0, NULL);

    ret = SQLExecute(stmt);
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        char dateBuff[50];
        int i = (int)rowsFetched;
        datas->jadwalPertemuans[i].jumlah_murid = 0;

        SQLGetData(stmt, 1, SQL_C_LONG,
                   &datas->jadwalPertemuans[i].id_num, sizeof(datas->jadwalPertemuans[i].id_num), NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR,
                   &datas->jadwalPertemuans[i].id_pertemuan, sizeof(datas->jadwalPertemuans[i].id_pertemuan), NULL);
        SQLGetData(stmt, 3, SQL_C_CHAR,
                   &datas->jadwalPertemuans[i].nama_staff, sizeof(datas->jadwalPertemuans[i].nama_staff), NULL);
        SQLGetData(stmt, 4, SQL_C_CHAR,
                   datas->jadwalPertemuans[rowsFetched].nama_pengajar, sizeof(datas->jadwalPertemuans[rowsFetched].nama_pengajar), NULL);
        SQLGetData(stmt, 5, SQL_C_LONG,
                   &datas->jadwalPertemuans[rowsFetched].lokasi, sizeof(datas->jadwalPertemuans[rowsFetched].lokasi), NULL);
        SQLGetData(stmt, 6, SQL_C_CHAR,
                   datas->jadwalPertemuans[rowsFetched].judul_materi, sizeof(datas->jadwalPertemuans[rowsFetched].judul_materi), NULL);
        SQLGetData(stmt, 7, SQL_C_LONG,
                   &datas->jadwalPertemuans[i].jumlah_murid, sizeof(datas->jadwalPertemuans[i].jumlah_murid), NULL);
        SQLGetData(stmt, 8, SQL_C_CHAR,
                   &datas->jadwalPertemuans[i].waktu, sizeof(datas->jadwalPertemuans[i].waktu), NULL);
        SQLGetData(stmt, 9, SQL_C_CHAR,
                   &datas->jadwalPertemuans[i].id_staff, sizeof(datas->jadwalPertemuans[i].id_staff), NULL);
        SQLGetData(stmt, 10, SQL_C_CHAR,
                   &datas->jadwalPertemuans[i].id_pengajar, sizeof(datas->jadwalPertemuans[i].id_pengajar), NULL);
        SQLGetData(stmt, 11, SQL_C_CHAR,
                   &datas->jadwalPertemuans[i].id_ruangan, sizeof(datas->jadwalPertemuans[i].id_ruangan), NULL);
        SQLGetData(stmt, 12, SQL_C_CHAR,
                   &datas->jadwalPertemuans[i].id_materi, sizeof(datas->jadwalPertemuans[i].id_materi), NULL);
        SQLGetData(stmt, 13, SQL_C_CHAR,
                   &datas->jadwalPertemuans[i].nama_peng_truncated, sizeof(datas->jadwalPertemuans[i].nama_peng_truncated), NULL);
        SQLGetData(stmt, 14, SQL_C_CHAR,
                   &datas->jadwalPertemuans[i].judul_materi_truncated, sizeof(datas->jadwalPertemuans[i].judul_materi_truncated), NULL);
        rowsFetched++;
    }
    datas->nJadwalPertemuan = rowsFetched;
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);
}
void findAllJadwalPertemuanByUserId(data *datas, int *nPage, SQLHDBC *dbConn, user *authUser)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count = 0;
    SQLUSMALLINT rowStatus[100];

    SQLLEN rowsFetched = 0;
    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    if (strcmp(authUser->role, "PENGAJAR") == 0)
    {
        SQLPrepare(stmt, (SQLCHAR *)"SELECT COUNT(*) AS row_count FROM jadwal_pertemuan WHERE id_pengajar =  ? AND waktu >= GETDATE()", SQL_NTS);
    }
    else if (strcmp(authUser->role, "MURID") == 0)
    {
        SQLPrepare(stmt, (SQLCHAR *)"SELECT COUNT(jp.id_pertemuan) AS row_count FROM jadwal_pertemuan jp, jadwal_murid jm WHERE jp.id_pertemuan = jm.id_pertemuan AND jm.id_murid = ? AND jp.waktu >= GETDATE()", SQL_NTS);
    }

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
    *nPage = (int)ceilf((float)count / 3.0);
    int limit = 3;
    int offset = (datas->page - 1) * limit;
    *nPage = (int)ceilf((float)count / limit);

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    if (strcmp(authUser->role, "PENGAJAR") == 0)
    {
        if (datas->sortBy == DESC)
            SQLPrepare(stmt, (SQLCHAR *)"SELECT j.id_num, j.id_pertemuan, s.nama AS nama_staff, p.nama AS nama_pengajar,r.lokasi,m.judul_materi, (SELECT COUNT(*) FROM jadwal_murid WHERE jadwal_murid.id_pertemuan = j.id_pertemuan) AS jumlah_murid,j.waktu, map.nama_mapel FROM jadwal_pertemuan j, staff s, pengajar p, ruangan r, materi m, mapel map WHERE j.id_pengajar =  ? AND s.id_staff = j.id_staff AND p.id_pengajar = j.id_pengajar AND r.id_ruangan = j.id_ruangan AND m.id_materi = j.id_materi AND map.id_mapel = m.id_mapel AND j.waktu >= GETDATE() ORDER BY j.waktu DESC OFFSET ? ROWS FETCH NEXT ? ROWS ONLY", SQL_NTS);
        else
            SQLPrepare(stmt, (SQLCHAR *)"SELECT j.id_num, j.id_pertemuan, s.nama AS nama_staff, p.nama AS nama_pengajar,r.lokasi,m.judul_materi, (SELECT COUNT(*) FROM jadwal_murid WHERE jadwal_murid.id_pertemuan = j.id_pertemuan) AS jumlah_murid,j.waktu, map.nama_mapel FROM jadwal_pertemuan j, staff s, pengajar p, ruangan r, materi m, mapel map WHERE j.id_pengajar =  ? AND s.id_staff = j.id_staff AND p.id_pengajar = j.id_pengajar AND r.id_ruangan = j.id_ruangan AND m.id_materi = j.id_materi AND map.id_mapel = m.id_mapel AND j.waktu >= GETDATE() ORDER BY j.waktu ASC OFFSET ? ROWS FETCH NEXT ? ROWS ONLY", SQL_NTS);
    }
    else if (strcmp(authUser->role, "MURID") == 0)
    {
        if (datas->sortBy == DESC)
            SQLPrepare(stmt, (SQLCHAR *)"SELECT j.id_num, j.id_pertemuan, s.nama AS nama_staff, p.nama AS nama_pengajar,r.lokasi,m.judul_materi,j.waktu, map.nama_mapel FROM jadwal_pertemuan j, staff s, pengajar p, ruangan r, materi m, mapel map, jadwal_murid jm WHERE jm.id_pertemuan = j.id_pertemuan AND jm.id_murid =  ? AND s.id_staff = j.id_staff AND p.id_pengajar = j.id_pengajar AND r.id_ruangan = j.id_ruangan AND m.id_materi = j.id_materi AND map.id_mapel = m.id_mapel AND j.waktu >= GETDATE() ORDER BY j.waktu DESC OFFSET ? ROWS FETCH NEXT ? ROWS ONLY", SQL_NTS);
        else
            SQLPrepare(stmt, (SQLCHAR *)"SELECT j.id_num, j.id_pertemuan, s.nama AS nama_staff, p.nama AS nama_pengajar,r.lokasi,m.judul_materi,j.waktu, map.nama_mapel FROM jadwal_pertemuan j, staff s, pengajar p, ruangan r, materi m, mapel map, jadwal_murid jm WHERE jm.id_pertemuan = j.id_pertemuan AND jm.id_murid =  ? AND s.id_staff = j.id_staff AND p.id_pengajar = j.id_pengajar AND r.id_ruangan = j.id_ruangan AND m.id_materi = j.id_materi AND map.id_mapel = m.id_mapel AND j.waktu >= GETDATE() ORDER BY j.waktu ASC OFFSET ? ROWS FETCH NEXT ? ROWS ONLY", SQL_NTS);
    }
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(authUser->id), 0, authUser->id, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &offset, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &limit, 0, NULL);

    ret = SQLExecute(stmt);
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        char dateBuff[50];
        int i = (int)rowsFetched;
        datas->jadwalPertemuans[i].jumlah_murid = 0;

        SQLGetData(stmt, 1, SQL_C_LONG,
                   &datas->jadwalPertemuans[i].id_num, sizeof(datas->jadwalPertemuans[i].id_num), NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR,
                   datas->jadwalPertemuans[i].id_pertemuan, sizeof(datas->jadwalPertemuans[i].id_pertemuan), NULL);
        SQLGetData(stmt, 3, SQL_C_CHAR,
                   datas->jadwalPertemuans[i].nama_staff, sizeof(datas->jadwalPertemuans[i].nama_staff), NULL);
        SQLGetData(stmt, 4, SQL_C_CHAR,
                   datas->jadwalPertemuans[rowsFetched].nama_pengajar, sizeof(datas->jadwalPertemuans[rowsFetched].nama_pengajar), NULL);
        SQLGetData(stmt, 5, SQL_C_CHAR,
                   datas->jadwalPertemuans[rowsFetched].lokasi, sizeof(datas->jadwalPertemuans[rowsFetched].lokasi), NULL);
        SQLGetData(stmt, 6, SQL_C_CHAR,
                   datas->jadwalPertemuans[rowsFetched].judul_materi, sizeof(datas->jadwalPertemuans[rowsFetched].judul_materi), NULL);
        if (strcmp(authUser->role, "PENGAJAR") == 0)
        {
            SQLGetData(stmt, 7, SQL_C_LONG,
                       &datas->jadwalPertemuans[i].jumlah_murid, sizeof(datas->jadwalPertemuans[i].jumlah_murid), NULL);
            SQLGetData(stmt, 8, SQL_C_CHAR,
                       datas->jadwalPertemuans[i].waktu, sizeof(datas->jadwalPertemuans[i].waktu), NULL);
            SQLGetData(stmt, 9, SQL_C_CHAR,
                       datas->jadwalPertemuans[i].nama_mapel, sizeof(datas->jadwalPertemuans[i].nama_mapel), NULL);
        }
        else
        {
            SQLGetData(stmt, 7, SQL_C_CHAR,
                       datas->jadwalPertemuans[i].waktu, sizeof(datas->jadwalPertemuans[i].waktu), NULL);
            SQLGetData(stmt, 8, SQL_C_CHAR,
                       datas->jadwalPertemuans[i].nama_mapel, sizeof(datas->jadwalPertemuans[i].nama_mapel), NULL);
        }

        rowsFetched++;
    }
    datas->nJadwalPertemuan = rowsFetched;
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);
}

QUERYSTATUS createJadwalPertemuan(InputField fields[], SQLHDBC *dbConn, user *authUser)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;
    SQLLEN idind;

    JadwalPertemuan newJadwalPertemuan;

    strcpy(newJadwalPertemuan.id_staff, authUser->id);
    strcpy(newJadwalPertemuan.id_pengajar, fields[1].value.text);
    strcpy(newJadwalPertemuan.id_ruangan, fields[2].value.text);
    strcpy(newJadwalPertemuan.id_materi, fields[3].value.text);
    strcpy(newJadwalPertemuan.waktu, fields[4].value.text);

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"INSERT INTO jadwal_pertemuan (id_staff, id_pengajar, id_ruangan,id_materi,waktu) OUTPUT inserted.id_pertemuan VALUES (?,?,?,?,?)", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newJadwalPertemuan.id_staff), 0, newJadwalPertemuan.id_staff, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newJadwalPertemuan.id_pengajar), 0, newJadwalPertemuan.id_pengajar, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newJadwalPertemuan.id_ruangan), 0, newJadwalPertemuan.id_ruangan, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newJadwalPertemuan.id_materi), 0, newJadwalPertemuan.id_materi, 0, NULL);
    SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newJadwalPertemuan.waktu), 0, newJadwalPertemuan.waktu, 0, NULL);
    ret = SQLExecute(stmt);

    SQLBindCol(stmt, 1, SQL_C_CHAR, newJadwalPertemuan.id_pertemuan, sizeof(newJadwalPertemuan.id_pertemuan), &idind);

    if (SQL_SUCCEEDED(ret))
    {
        ret = SQLFetch(stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);

    createJadwalMurid(fields[5].value, newJadwalPertemuan.id_pertemuan, dbConn);

    switch (ret)
    {
    case SQL_ERROR:
        return FAILED;

    default:
        return SUCCESS;
    }
}

QUERYSTATUS updateJadwalPertemuan(InputField fields[], SQLHDBC *dbConn, user *authUser)
{

    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;

    JadwalPertemuan updatedJadwalPertemuan;

    strcpy(updatedJadwalPertemuan.id_pertemuan, fields[0].value.text);
    strcpy(updatedJadwalPertemuan.id_pengajar, fields[1].value.text);
    strcpy(updatedJadwalPertemuan.id_ruangan, fields[2].value.text);
    strcpy(updatedJadwalPertemuan.id_materi, fields[3].value.text);
    strcpy(updatedJadwalPertemuan.waktu, fields[4].value.text);

    for (int i = 0; i < 5; i++)
    {
        printf("%d: %s\n", i, fields[i].value.text);
    }

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"UPDATE jadwal_pertemuan SET id_pengajar = ?, id_ruangan = ?, id_materi = ?, waktu = ? WHERE id_pertemuan = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedJadwalPertemuan.id_pengajar), 0, updatedJadwalPertemuan.id_pengajar, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedJadwalPertemuan.id_ruangan), 0, updatedJadwalPertemuan.id_ruangan, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedJadwalPertemuan.id_materi), 0, updatedJadwalPertemuan.id_materi, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedJadwalPertemuan.waktu), 0, updatedJadwalPertemuan.waktu, 0, NULL);
    SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedJadwalPertemuan.id_pertemuan), 0, updatedJadwalPertemuan.id_pertemuan, 0, NULL);
    ret = SQLExecute(stmt);

    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);

    deleteteJadwalMuridByPertemuanID(fields[0].value.text, dbConn);
    createJadwalMurid(fields[5].value, updatedJadwalPertemuan.id_pertemuan, dbConn);

    switch (ret)
    {
    case SQL_ERROR:
        return FAILED;

    default:
        return SUCCESS;
    }
}

QUERYSTATUS deleteJadwalPertemuan(SQLHDBC *dbConn, JadwalPertemuanWithDetails updatedPertemuan)
{
    deleteteJadwalMuridByPertemuanID(updatedPertemuan.id_pertemuan, dbConn);

    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"DELETE FROM jadwal_pertemuan WHERE id_pertemuan = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedPertemuan.id_pertemuan), 0, updatedPertemuan.id_pertemuan, 0, NULL);
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