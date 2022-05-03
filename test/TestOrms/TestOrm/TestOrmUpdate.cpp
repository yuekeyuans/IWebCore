#include "TestOrmUpdate.h"

TestOrmUpdate::TestOrmUpdate()
{

}

void TestOrmUpdate::init()
{
    model.clearTable();
}

void TestOrmUpdate::test_updateBean()
{
    PhoneBean bean;
    model.insert(bean);

    bean.phoneNumber = "123456";
    model.update(bean);

    auto newBean = model.findOneByPriamaryKey(bean.id);
    qDebug() << newBean << bean;
    QTEST_ASSERT(newBean == bean);
}

void TestOrmUpdate::test_updateBeans()
{
    QList<PhoneBean> beans;
    for(int i=0; i<10; i++){
        beans.append(PhoneBean{});
    }
    model.insert(beans);

    for(int i=0; i<10; i++){
        beans[i].phoneNumber = QString::number(i);
    }
    model.update(beans);

    auto newBeans = model.findAll();
    QTEST_ASSERT(beans.length() == newBeans.length());
    for(int i=0; i<10; i++){
        QTEST_ASSERT(beans[i] == newBeans[i]);
    }
}

void TestOrmUpdate::test_updateBeansColumns()
{
    QList<PhoneBean> beans;
    for(int i=0; i<10; i++){
        beans.append(PhoneBean{});
    }
    model.insert(beans);

    for(int i=0; i<10; i++){
        beans[i].phoneNumber = QString::number(i);
    }
    model.update(beans, {PhoneBean::field_phoneNumber});

    auto newBeans = model.findAll();
    QTEST_ASSERT(beans.length() == newBeans.length());
    for(int i=0; i<10; i++){
        QTEST_ASSERT(beans[i] == newBeans[i]);
    }
}

void TestOrmUpdate::test_updateByColumns()
{
    QList<PhoneBean> beans;
    for(int i=0; i<10; i++){
        beans.append(PhoneBean{});
    }
    model.insert(beans);

    model.update(beans, {PhoneBean::field_phoneNumber});

    auto newBeans = model.findAll();
    QTEST_ASSERT(beans.length() == newBeans.length());
    for(int i=0; i<10; i++){
        QTEST_ASSERT(beans[i] == newBeans[i]);
    }
}

void TestOrmUpdate::test_updateByCondition()
{
    QList<PhoneBean> beans;
    for(int i=0; i<10; i++){
        beans.append(PhoneBean{});
    }
    model.insert(beans);

    QMap<QString, QVariant> map;
    map[PhoneBean::field_phoneNumber] = "12131";
    model.update(map, IOrmCondition().whereIsNotNull(PhoneBean::field_id));

    auto newBeans = model.findAll();
    QTEST_ASSERT(beans.length() == newBeans.length());
    for(int i=0; i<10; i++){
        QTEST_ASSERT(newBeans[i].phoneNumber == "12131");
    }
}

void TestOrmUpdate::test_updateBeanColumns()
{
    PhoneBean bean;
    model.insert(bean);

    bean.phoneNumber = "123456";
    model.update(bean, {PhoneBean::field_phoneNumber});

    auto newBean = model.findOneByPriamaryKey(bean.id);
    qDebug() << newBean << bean;
    QTEST_ASSERT(newBean == bean);
}
