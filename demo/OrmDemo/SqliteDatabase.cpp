#include "SqliteDatabase.h"

#include "UserTable.h"

SqliteDatabase::SqliteDatabase()
{

}

IOrmDataSource SqliteDatabase::configDataSource()
{
    IOrmDataSource source;

    source.driverName = "QSQLITE";
    source.databaseName = "SqliteDatabase.db";

    return source;
}

void SqliteDatabase::registerTables()
{
    registerTable<UserTable>();
}
