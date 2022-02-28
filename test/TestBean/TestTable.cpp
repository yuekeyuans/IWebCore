#include "TestTable.h"

TestTable::TestTable()
{

}

void TestTable::init()
{

}

void TestTable::test_demo()
{
    OneTable table;
    qDebug() << table.toJson();
    qDebug() << table.tableInfo().fieldNames;

    OneTable tableB;
    qDebug() << tableB;
}
