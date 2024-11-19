#include "SqliteDatabase.h"
#include "UserBean.h"
#include "EmailBean.h"

SqliteDatabase::SqliteDatabase()
{
    $ConstructDatabase(SqliteDatabase)
}

IOrmDataSource SqliteDatabase::configDataSource()
{
    IOrmDataSource source;
    source.driverName = "QSQLITE";
    source.databaseName = "abc.db";
    return source;
}

void SqliteDatabase::registerTables()
{
    registerTable<UserBean>();
}
