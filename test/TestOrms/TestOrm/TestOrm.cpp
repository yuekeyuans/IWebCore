#include "TestOrm.h"



TestOrm::TestOrm()
{
}

TestOrm::~TestOrm()
{
}

void TestOrm::initTestCase()
{
}

void TestOrm::cleanupTestCase()
{
}

void TestOrm::init()
{
    model.clearTable();
}

void TestOrm::cleanup()
{

}

void TestOrm::test_count()
{
    int count = model.count();
    QCOMPARE(0, count);

    PhoneBean bean;
    model.insert(bean);
    count = model.count();
    QCOMPARE(1, count);

    PhoneBean bean1;
    model.insert(bean1);
    count = model.count();
    QCOMPARE(2, count);
}

void TestOrm::test_insert()
{
    PhoneBean bean;
    model.insert(bean);
    auto count = model.count();
    QTEST_ASSERT(count == 1);
}

void TestOrm::test_insertId()
{
    PhoneBean bean;
    auto pk = bean.id;
    QTEST_ASSERT(pk == 0);
    model.insert(bean);
    auto newPk = bean.id;
    QTEST_ASSERT(pk != newPk);
}

void TestOrm::test_insertMuch()
{
    QList<PhoneBean> beans;
    for(int i=0; i<10; i++){
        beans.append(PhoneBean{});
    }
    model.insert(beans);
    auto count = model.count();
    QTEST_ASSERT(count == 10);
}

void TestOrm::test_deleteById()
{
    PhoneBean bean;
    model.insert(bean);
    QTEST_ASSERT(bean.id != 0);

    auto count = model.count();
    QTEST_ASSERT(count == 1);

    model.deleteByPrimaryKey(bean.id);
    count = model.count();
    QTEST_ASSERT(count == 0);
}

void TestOrm::test_deleteCondition()
{
    PhoneBean bean;

    model.insert(bean);
    auto count = model.count();
    QTEST_ASSERT(count == 1);

    auto id = bean.id;
    model.deleted(IOrmCondition().whereEqual(PhoneBean::field_id, id));
    count = model.count();
    QTEST_ASSERT(count == 0);
}

void TestOrm::test_deleteBean()
{
    PhoneBean bean;

    model.insert(bean);
    auto count = model.count();
    QTEST_ASSERT(count == 1);

    model.deleted(bean);
    count = model.count();
    QTEST_ASSERT(count == 0);
}

void TestOrm::test_deleteBeans()
{
    QList<PhoneBean> beans;
    for(int i=0; i<10; i++){
        beans.append(PhoneBean{});
    }

    model.insert(beans);
    auto count = model.count();
    QTEST_ASSERT(count == 10);

    model.deleted(beans);
    count = model.count();
    QTEST_ASSERT(count == 0);
}

void TestOrm::test_deleteSql()
{
    QList<PhoneBean> beans;
    for(int i=0; i<10; i++){
        beans.append(PhoneBean{});
    }

    model.insert(beans);
    auto count = model.count();
    QTEST_ASSERT(count == 10);

    model.deleted("delete from PhoneBean");
    count = model.count();
    QTEST_ASSERT(count == 0);
}

void TestOrm::test_updateBean()
{
    PhoneBean bean;
    model.insert(bean);

    bean.name = "yuefei";
    model.update(bean);

//    qDebug() << id;

}

void TestOrm::test_count1()
{
    QList<PhoneBean> beans;
    for(int i=0; i<10; i++){
        beans.append(PhoneBean{});
    }
    model.insert(beans);
    auto count = model.count();
    QTEST_ASSERT(count == 10);
}

void TestOrm::test_count2()
{
    QList<PhoneBean> beans;
    for(int i=0; i<10; i++){
        beans.append(PhoneBean{});
    }
    model.insert(beans);
    auto id = beans[5].id;
    auto count = model.count(IOrmCondition().whereLessThan(PhoneBean::field_id, id));
    QTEST_ASSERT(count == 5);
}
