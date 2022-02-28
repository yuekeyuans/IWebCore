#include "TestTable.h"

TestTable::TestTable()
{

}

void TestTable::init()
{

}

void TestTable::test_insert()
{
    TableBean bean;
    model.insert(bean);
    qDebug() << bean;
}


