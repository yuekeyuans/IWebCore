#include "MySqlDb.h"
#include "DataBean.h"

const char MySqlDbConnection[] = "mysql";

MySqlDb::MySqlDb()
{
//    $ConstructDatabase(MySqlDb)
}

IOrmDataSource MySqlDb::configDataSource()
{
    return IOrmManage::getDataSource("mysql");
}

void MySqlDb::registerEntities()
{
    registerTable<DataBean>();
}
