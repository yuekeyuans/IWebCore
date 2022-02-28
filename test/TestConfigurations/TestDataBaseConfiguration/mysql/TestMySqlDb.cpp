#include "TestMySqlDb.h"

TestMySqlDb::TestMySqlDb()
{
}

void TestMySqlDb::init()
{
    model.truncateTable();
}

void TestMySqlDb::test_insertAndFetch()
{
    DataBean bean;
    model.insert(bean);
    qDebug() << bean;

    auto bean1 = model.findOneByPriamaryKey(bean.id);
    qDebug() << bean1;

    QTEST_ASSERT(bean == bean1);
}
