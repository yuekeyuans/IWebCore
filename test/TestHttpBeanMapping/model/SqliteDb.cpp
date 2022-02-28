#include "SqliteDb.h"

#include "model/UserTable.h"

SqliteDb::SqliteDb()
{

}

IOrmDataSource SqliteDb::configDataSource()
{
    IOrmDataSource source;
    source.driverName = "QSQLITE";
    source.databaseName = "abcddd.db";
    return source;
}

void SqliteDb::registerTables()
{
    registerTable<UserTable>();
}
