#include "TestOrmDateTime.h"

TestOrmDateTime::TestOrmDateTime()
{

}

void TestOrmDateTime::init()
{
    model.clearTable();
}

void TestOrmDateTime::test_insertAndFind()
{
    UserBean bean;
    bean.birthDate = QDate::currentDate();
    model.insert(bean);

    auto bean1 = model.findOneByPriamaryKey(bean.id);
    qDebug() << bean1.birthDate;
    QTEST_ASSERT(bean == bean1);
}

void TestOrmDateTime::test_json_bean_convert()
{
    UserBean bean;
    bean.birthDate = QDate::currentDate().addDays(10);
    auto json = IOrmUtil::toJsonObject(bean);
    qDebug() << json;

    // NOTE: 神奇，这里转换居然不用自己转。
    // NOTE: 具体的实现方式参见文章，可以肯定的是，所有的 QDate QTime QDateTime 都没有问题。
    // 感叹一句， Qt 是一个很厚重的封装。
    auto bean1 = IOrmUtil::toBean<UserBean>(json);
    QTEST_ASSERT(bean == bean1);
}

void TestOrmDateTime::test_json_map_bean_invalidValue()
{
    UserBean bean;
    QTEST_ASSERT(!bean.wakeTime.isValid());
    QTEST_ASSERT(!bean.lastLoginTime.isValid());
    QTEST_ASSERT(!bean.birthDate.isValid());

    auto map = IConvertUtil::toMap(bean);
    qDebug() << map;
    qDebug() << map["wakeTime"].isValid() << map["wakeTime"].toTime().isValid();
    QTEST_ASSERT(!map["wakeTime"].toTime().isValid());
    QTEST_ASSERT(!map["lastLoginTime"].toDateTime().isValid());
    QTEST_ASSERT(!map["birthDate"].toDate().isValid());

    auto beanMap = IConvertUtil::toBean<UserBean>(map);
    QTEST_ASSERT(bean == beanMap);

    auto json = IConvertUtil::toJsonObject(bean);
    qDebug() << json;
    QTEST_ASSERT(json["wakeTime"].toString().isEmpty());
    QTEST_ASSERT(json["lastLoginTime"].toString().isEmpty());
    QTEST_ASSERT(json["birthDate"].toString().isEmpty());
    auto beanJson = IConvertUtil::toBean<UserBean>(json);
    QTEST_ASSERT(bean == beanJson);

    // map 转 json， 再转bean
    auto json2 = IConvertUtil::toJsonObject(map);
    QTEST_ASSERT(json2["wakeTime"].toString().isEmpty());
    QTEST_ASSERT(json2["lastLoginTime"].toString().isEmpty());
    QTEST_ASSERT(json2["birthDate"].toString().isEmpty());

    auto bean2 = IOrmUtil::toBean<UserBean>(json2);
    QTEST_ASSERT(bean == bean2);

    // json 转 map 再转 bean
    auto map3 = IConvertUtil::toMap(json);
    auto bean3 = IConvertUtil::toBean<UserBean>(map3);
    QTEST_ASSERT(bean == bean3);
}

void TestOrmDateTime::test_find_dateTime()
{
    UserBean bean;
    bean.wakeTime = QTime::currentTime();
    bean.birthDate = QDate::currentDate();
    bean.lastLoginTime = QDateTime::currentDateTime();

    model.insert(bean);
    auto query = model.getQuery();
    query.exec("select birthDate from UserBean");
    auto date = IOrmUtil::getDate(query);
    QTEST_ASSERT(date == bean.birthDate);
    // other two could no test

    model.clearTable();
    QList<UserBean> beans;
    for(int i=0; i<10; i++){
        beans.append(bean);
    }
    model.insert(beans);

    auto query1 = model.getQuery();
    query1.exec("select wakeTime from userBean");
    auto times = IOrmUtil::getTimeList(query1);
    QTEST_ASSERT(times.length() == 10);
    QTEST_ASSERT(times.first() == bean.wakeTime);

}

void TestOrmDateTime::test_three_type_insert_and_find()
{
    UserBean bean;
    bean.birthDate = QDate::currentDate();
    bean.wakeTime = QTime::currentTime();
    bean.lastLoginTime = QDateTime::currentDateTime();
    model.insert(bean);

    auto bean1 = model.findOneByPriamaryKey(bean.id);
    qDebug() << bean1.birthDate <<bean1.wakeTime << bean1.lastLoginTime;
    QTEST_ASSERT(bean == bean1);
}
