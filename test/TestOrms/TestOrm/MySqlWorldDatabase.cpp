#include "MySqlWorldDatabase.h"

#include "world/CityTable.h"
#include "world/CountryTable.h"

const char MySqlWorldConnectionName[] = "world";

MySqlWorldDatabase::MySqlWorldDatabase()
{
}


IOrmDataSource MySqlWorldDatabase::configDataSource()
{
    IOrmDataSource source;
    source.connectionName="world";
    source.databaseName ="world";
    source.driverName = "QMYSQL";
    source.host = "127.0.0.1";
    source.port = 3306;
    source.userName = "root";
    source.password = "yky00124578";
    return source;
}

void MySqlWorldDatabase::registerEntities()
{
    registerTable<CityTable>();
    registerTable<CountryTable>();
}
