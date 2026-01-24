# SIBELA

Sistem bimbingan belajar (SIBELA) is our final project for our first semester

## Team Members

- Teguh Bayu Pratama (0920250052)
- Rayyan Abdurrahman Qadar (0920250049)
- Ridzal Arif Billah (0920250051)
- Nabilah Tri Utami (0920250044)
- Rasya Bintang Priyanto (0920250048)

## Techstack

- C
- Raylib (UI Framework)
- ODBC (Sql Server connection)

## Adding database connection

1. Import .sql to your DBMS
2. Add NEW ODBC DSN to your system ([See here](https://docs.devart.com/odbc/sqlserver/?configuring_odbc_dsn_on_windows.htm))
3. create a .env file on the project's root folder containing:

```
DSN=YOURDSNNAME;Uid={YOURDBUSER};Pwd={YOURDBPASSWORD}

```

4. Done

## How to build

```bash
# Unix systems
./configure
./build.sh

# Windows systems
mkdir dist/
cd dist/
cmake .. -G "MinGW Makefiles"
cd ..
.\build.ps1
```
