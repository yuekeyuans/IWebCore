#include "TestOrmSelect.h"

void TestOrmSelect::init()
{
    model.clearTable();
}

void TestOrmSelect::test_findOne()
{
    PhoneBean bean;
    model.insert(bean);

    qDebug() << bean.toVariantMap();
    auto value = model.findOne(IOrmCondition().whereEqual(PhoneBean::field_id, bean.id));
    qDebug() << value.toVariantMap();
}

void TestOrmSelect::test_findAll()
{
    QList<PhoneBean> beans;
    for(int i=0; i<10; i++){
        beans.append(PhoneBean{});
    }
    model.insert(beans);
    QList<int> ids;
    for(const auto& bean : beans){
        ids.append(bean.id);
    }

    auto values = model.findAll();
    for(const auto& val : values){
        QTEST_ASSERT(ids.contains(val.id));
    }
    QTEST_ASSERT(values.length() == 10);
}

void TestOrmSelect::test_findAll1()
{
    QList<PhoneBean> beans;
    for(int i=0; i<10; i++){
        beans.append(PhoneBean{});
    }
    model.insert(beans);
    QList<int> ids;
    for(const auto& bean : beans){
        ids.append(bean.id);
    }

    int id = ids[5];
    auto values = model.findAll(IOrmCondition().whereLessThan(PhoneBean::field_id, id));
    for(const auto& val : values){
        QTEST_ASSERT(ids.contains(val.id));
    }
    qDebug() <<values.length();
    QTEST_ASSERT(values.length() == 5);
}

void TestOrmSelect::test_findOneByPk()
{
    PhoneBean bean;
    model.insert(bean);
    qDebug() << bean.toVariantMap();
    auto id = bean.id;

    auto b1 = model.findOneByPriamaryKey(id);
    qDebug() << b1.toVariantMap();
    QTEST_ASSERT(b1.isEqualTo(bean));
}

void TestOrmSelect::test_findColumns1()
{
    QList<PhoneBean> beans;
    for(int i=0; i<10; i++){
        beans.append(PhoneBean{});
    }
    model.insert(beans);

    auto maps = model.findColumns({PhoneBean::field_id, PhoneBean::field_name});
    for(const auto& map : maps){
        QTEST_ASSERT(map.contains(PhoneBean::field_id));
        QTEST_ASSERT(map.contains(PhoneBean::field_name));
        QTEST_ASSERT(!map.contains(PhoneBean::field_phoneNumber));
    }
    QTEST_ASSERT(maps.length() == 10);
}

void TestOrmSelect::test_findColumns2()
{
    QList<PhoneBean> beans;
    for(int i=0; i<10; i++){
        beans.append(PhoneBean{});
    }
    model.insert(beans);

    auto maps = model.findColumns(
                {PhoneBean::field_id, PhoneBean::field_name },
                IOrmCondition().whereLessThan(PhoneBean::field_id, beans[5].id));
    for(const auto& map : maps){
        QTEST_ASSERT(map.contains(PhoneBean::field_id));
        QTEST_ASSERT(map.contains(PhoneBean::field_name));
        QTEST_ASSERT(!map.contains(PhoneBean::field_phoneNumber));
    }
    qDebug() << maps.length();
    QTEST_ASSERT(maps.length() == 5);
}
