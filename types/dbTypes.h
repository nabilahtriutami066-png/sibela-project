#ifndef dbTypes
#define dbTypes

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <time.h>
// #include "../model/model.h"

typedef enum
{
    X,
    XI,
    XII
} tingkat_enum;
typedef enum
{
    MANAJER,
    FRONTDESK
} staf_role_enum;

typedef enum
{
    MURID,
    PENGAJAR,
    RUANGAN,
    MAPEL,
    PEMBAYARAN,
    JADWAL,
    PEMBAYARANREPORT = 8,
    MANAJERSTAFF
} STAFFSUBWINDOW;

typedef enum
{
    JADWALMURID,
    MATERIMURID,
    PEMBAYARANMURID
} MURIDSUBWINDOW;

typedef enum
{
    ABSENSI,
    PERTEMUAN,
    MATERI
} PENGAJARSUBWINDOW;

typedef struct
{
    int id_num;
    char id_murid[7];
    char nama[101];
    char tanggal_lahir[20];
    int tingkat;
    char tanggal_masuk[20];
    char no_hp[16];
    char password[101];
} Murid;

typedef struct
{
    int id_num;
    char id_pertemuan[8];
    char id_staff[9];
    char id_pengajar[8];
    char id_ruangan[7];
    char id_materi[7];
    char waktu[20];
} JadwalPertemuan;

typedef struct
{
    int id_num;
    char id_jamur[9];
    char id_murid[7];
    char id_pertemuan[8];
} JadwalMurid;

typedef struct
{
    int id_num;
    char id_pertemuan[8];
    char nama_staff[101];
    char nama_pengajar[101];
    char lokasi[101];
    char judul_materi[101];
    char id_staff[9];
    char id_pengajar[8];
    char id_ruangan[7];
    char id_materi[7];
    int jumlah_murid;
    char waktu[20];
} JadwalPertemuanWithDetails;

typedef struct
{
    int id_num;
    char id_pengajar[8];
    char nama[101];
    char tanggal_lahir[20];
    char tanggal_masuk[20];
    char no_hp[16];
    char password[101];
} Pengajar;

typedef struct
{
    int id_num;
    char id_staff[30];
    char role[20];
    char nama[255];
    char tanggal_lahir[20];
    char tanggal_masuk[20];
    char no_hp[20];
    char password[100];
    char email[100];
} Staf;

typedef struct
{
    int id_num;
    char id_ruangan[7];
    char lokasi[101];
    char deskripsi[101];
    char deskripsi_short[31];
} Ruangan;

typedef struct
{
    int id_num;
    char id_mapel[7];
    char nama_mapel[101];
} Mapel;

typedef struct
{
    int id_num;
    char id_materi[7];
    char id_mapel[7];
    char nama_mapel[101];
    char judul_materi[101];
    char isi_materi[256];
} Materi;

typedef struct
{
    int id_num;
    char id_pembayaran[8];
    char id_murid[7];
    char tanggal_pembayaran[11];
    double jumlah_pembayaran;
    char mtd_pembayaran[11];
    int dikonfirmasi;
    char id_staff[9];
} Pembayaran;

typedef struct
{
    int id_num;
    char id_pembayaran[16];
    char id_murid[16];
    char nama_murid[100];
    char tanggal_pembayaran[20];
    int jumlah_pembayaran;
    int dikonfirmasi;
    char id_staff[16];
    char nama_staff[100];
    char mtd_pembayaran[20];
} PembayaranFetchAll;

typedef struct
{
    char id_murid[7];
    char nama_murid[100];
    char alasan[100];
    int charLenAlasan;
    int isHadir;
    char waktu_absensi[30];
    int existed;
} MuridAbsensi;

typedef struct
{
    int id_num;
    char id_absensi[7];
    char id_murid[7];
    char id_pertemuan[8];
    char id_pengajar[8];
    int isHadir;
    char alasan[201];
    char waktu_absensi[20];
} Absensi;

typedef struct
{
    int totalThisMonth;
    int sumThisMonth;
} PembayaranReport;

typedef enum {
    MATERI_MAPEL = 0,
    MATERI_LIST,
    MATERI_DETAIL
} MATERISUBWINDOW;

typedef struct
{
    MATERISUBWINDOW activeSubWindow;

    int page;
    int nPage;

    int nMapel;
    int nMateri;

    Mapel *mapels;
    Materi *materis;

    Mapel selectedMapel;
    int expandedIndex;
} MateriPageState;


// typedef struct
//     {
//         SQLINTEGER id_num;
//         SQLVARCHAR id_staff;
//         SQLVARCHAR role;
//         SQLVARCHAR nama;
//         SQLDATE tanggal_lahir;
//         SQLINTEGER tingat;
//         SQLDATE tanggal_masuk;
//         SQLVARCHAR no_hp;
//         SQLVARCHAR password;
//     } stafSQL;

#endif