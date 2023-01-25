#include "SqliteDatabase.h"
#include "PhoneBean.h"
#include "types/UserBean.h"
#include "types/NumberBean.h"
#include "world/CityTable.h"
#include "world/CountryTable.h"
#include "world/LanguageModel.h"

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

    registerTable<CityTable>();
    registerTable<CountryTable>();
    registerTable<LanguageTable>();
}


IOrmDataSource SqliteDatabase::configDataSource()
{
    IOrmDataSource source;
    source.connectionName = "sqlite";
    source.driverName = "QSQLITE";
    source.databaseName = "abcdef.db";
    return source;
}
