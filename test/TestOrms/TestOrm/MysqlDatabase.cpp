#include "MysqlDatabase.h"

#include "PhoneBean.h"
#include "types/UserBean.h"
#include "types/NumberBean.h"

const char MySqlDatabaseConnectionName[] = "MySqlConnection";

IOrmDataSource MysqlDatabase::configDataSource()
{
    IOrmDataSource source;
    source.connectionName = MySqlDatabaseConnectionName;
    source.databaseName ="testOrm";
    source.driverName = "QMYSQL";
    source.host = "127.0.0.1";
    source.port = 3306;
    source.userName = "root";
    source.password = "yky00124578";
    return source;
}

void MysqlDatabase::registerEntities()
{
    registerTable<PhoneBean>();
    registerTable<UserBean>();
    registerTable<NumberBean>();
}
