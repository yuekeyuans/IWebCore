#include "SqliteDb.h"
#include "DataBean.h"

const char SqlLiteConnectionName[] = "sqlite";

SqliteDb::SqliteDb()
{
//    $ConstructDatabase(SqliteDb)
}

IOrmDataSource SqliteDb::configDataSource()
{
//    return IOrmBase::getDataSource("sqlite");

    IOrmDataSource source;
    source.driverName = "QSQLITE";
    source.databaseName = "abcpp.db";
    source.connectionName = SqlLiteConnectionName;
    return source;
}

void SqliteDb::registerTables()
{
    registerTable<DataBean>();
}
