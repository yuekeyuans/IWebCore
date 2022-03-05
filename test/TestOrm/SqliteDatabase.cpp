#include "SqliteDatabase.h"
#include "PhoneBean.h"
#include "types/UserBean.h"
#include "types/NumberBean.h"

const char SqliteConnectionName[] = "sqlite";

SqliteDatabase::SqliteDatabase()
{
//    $ConstructDatabase(SqliteDatabase)
}

void SqliteDatabase::registerEntities()
{
    registerTable<PhoneBean>();
    registerTable<UserBean>();
    registerTable<NumberBean>();
}


IOrmDataSource SqliteDatabase::configDataSource()
{
    IOrmDataSource source;
    source.connectionName = "sqlite";
    source.driverName = "QSQLITE";
    source.databaseName = "abcdef.db";
    return source;
}
