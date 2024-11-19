#include "TestBeanListMapConvertion.h"
#include "DataBean.h"

void TestBeanListMapConvertion::test_Bean()
{
    DataBean bean;
    qDebug() << bean;
    qDebug() << bean.toJson();
    qDebug() << bean.toVariantMap();
    qDebug().noquote() << bean.toString();

    QString result = R"({"id":10,"name":"yuekeyuan"})";
    QTEST_ASSERT(bean.toString() == result);
}

void TestBeanListMapConvertion::test_QListBean()
{
    QList<DataBean> beans;
    beans.append(DataBean{});
    beans.append(DataBean{});
    beans.append(DataBean{});
    qDebug() << IJsonUtil::toString(beans);
    qDebug() << IJsonUtil::toJsonValue(beans);

    QMap<QString, DataBean> beanMap;
    beanMap["a"] = DataBean{};
    beanMap["b"] = DataBean{};
    qDebug() << IJsonUtil::toJsonValue(beanMap);

    QList<QMap<QString, DataBean>> beanListMap;
    beanListMap.append(beanMap);
    beanListMap.append(beanMap);
    qDebug() << IJsonUtil::toJsonValue(beanListMap);
}

void TestBeanListMapConvertion::test_normalContainer()
{
    QList<QString> names;
    names << "hello" << "world";
    auto value2 = IJsonUtil::toJsonValue(names).value();
    QTEST_ASSERT(value2 == QJsonValue{QJsonArray({"hello","world"})});

    QList<int> intVals;
    intVals << 1 << 2;
    auto value1 = IConvertUtil::toJsonValue(intVals).value();
    QTEST_ASSERT(value1 == QJsonValue{QJsonArray({1, 2})});


    QStringList demo1 {"12", "32"};
    auto value = IConvertUtil::toJsonValue(demo1).value();
    QTEST_ASSERT(value == QJsonValue{QJsonArray({"12","32"})});
}
