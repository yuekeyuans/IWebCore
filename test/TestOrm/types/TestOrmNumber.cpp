#include "TestOrmNumber.h"

TestOrmNumber::TestOrmNumber()
{

}

void TestOrmNumber::init()
{
    model.clearTable();
}

void TestOrmNumber::testInsertFind()
{
    NumberBean bean;
//    bean.a = 1;
//    bean.b = 1;
    bean.c = 1;
    bean.d = 1;
    bean.e = 1;
    bean.f = 1;
    bean.g = 1;
    bean.h = 1;
    bean.i = 1;
    bean.j = 1;
    bean.k = 1;
    bean.l = 1;

    model.insert(bean);
    qDebug() << bean;

    auto map = IOrmUtil::toMap(bean);
    qDebug() << map;

    auto bean1 = IOrmUtil::toBean<NumberBean>(map);
    QTEST_ASSERT(bean == bean1);

    auto json = IOrmUtil::toJsonObject(bean);
    qDebug() << json;

    auto bean2 = IOrmUtil::toBean<NumberBean>(json);
    QTEST_ASSERT(bean == bean2);
}

