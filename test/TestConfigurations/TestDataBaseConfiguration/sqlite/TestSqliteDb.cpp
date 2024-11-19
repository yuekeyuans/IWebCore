#include "TestSqliteDb.h"

TestSqliteDb::TestSqliteDb()
{

}

void TestSqliteDb::init()
{
    model.clearTable();
}

void TestSqliteDb::insertAndFetch()
{
    DataBean bean;
    model.insert(bean);
    qDebug() << bean;

    auto bean1 = model.findOneByPriamaryKey(bean.id);
    qDebug() << bean1;

    QTEST_ASSERT(bean == bean1);
}
