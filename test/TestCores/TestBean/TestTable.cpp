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
    qDebug() << table.entityInfo().fieldNames;

    OneTable tableB;
    qDebug() << tableB;
}
