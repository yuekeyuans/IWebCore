
#include <IWebCore>
#include <QtTest>
#include "sqlite/SqliteDb.h"
#include "sqlite/TestSqliteDb.h"
#include "mysql/MySqlDb.h"
#include "mysql/TestMySqlDb.h"

$EnableCatagory(Test)
$DisableTest(TestMySqlDb);
int main(int argc, char *argv[])
{
    IApplication app(argc, argv);
    return app.exec();
}
