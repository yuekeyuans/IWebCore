#include "TestConfig.h"

TestConfig::TestConfig()
{

}

void TestConfig::init()
{

}

void TestConfig::test_1()
{
    DataBean bean;

    qDebug() << bean.age;
    QTEST_ASSERT(bean.age == 110);

    qDebug() << bean.name;
    QTEST_ASSERT(bean.name == "yuekeyuan");

    qDebug() << bean.dbName;
    QTEST_ASSERT(bean.dbName == "testOrm");

    qDebug() << bean.resPath;
    QStringList list;
    list << "a" << "b" << "c";
    QTEST_ASSERT(bean.resPath == list);

    qDebug() << bean.birthDate;
    QDate date = QVariant("2012-01-12").toDate();
    QTEST_ASSERT(bean.birthDate == date);

    qDebug() << bean.isValid;
    QTEST_ASSERT(bean.isValid == false);
}

void TestConfig::test_dataSource()
{
    auto dataSource = IOrmManage::getDataSource("default");
    qDebug() << dataSource;
    QTEST_ASSERT(dataSource.port == 3306);
}

void TestConfig::test_dataSource1()
{
    bool ok;
    auto dataSource = IConfigurationManage::getBean<IOrmDataSource>("dataSource.default", &ok);
    qDebug() << dataSource << ok;
}

