
#include <IWebCore>
#include <QtTest>
#include "sqlite/SqliteDb.h"
#include "sqlite/TestSqliteDb.h"
#include "mysql/MySqlDb.h"
#include "mysql/TestMySqlDb.h"

int main(int argc, char *argv[])
{
    $ITestBegin
    ITaskManage::run(argc, argv);

//    $RegisterDatabase(SqliteDb)
//    $RegisterDatabase(MySqlDb)

    $ITestClass(TestSqliteDb)
//    $ITestClass(TestMySqlDb)

    $ITestEnd
}
