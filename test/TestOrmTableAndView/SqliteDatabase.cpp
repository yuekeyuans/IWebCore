#include "SqliteDatabase.h"

#include "TableBean.h"

SqliteDatabase::SqliteDatabase()
{
}

IOrmDataSource SqliteDatabase::configDataSource()
{
    IOrmDataSource source;
    source.driverName = "QSQLITE";
    source.databaseName = "jjjjj.db";
    return source;
}

void SqliteDatabase::registerTables()
{
    registerTable<TableBean>();
}
