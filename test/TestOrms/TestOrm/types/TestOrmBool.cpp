#include "TestOrmBool.h"

TestOrmBool::TestOrmBool()
{
}

void TestOrmBool::init()
{
    model.clearTable();
}

void TestOrmBool::test_bool_field_true()
{
   UserBean bean;
   bean.isMarried = true;
   model.insert(bean);

   auto id = bean.id;

   auto bean1 = model.findOneByPriamaryKey(id);
   QTEST_ASSERT(bean == bean1);
   QTEST_ASSERT(bean1.isMarried == true);
}

void TestOrmBool::test_bool_field_false()
{
    UserBean bean;
    bean.isMarried = false;
    model.insert(bean);

    auto id = bean.id;


    auto bean1 = model.findOneByPriamaryKey(id);
    QTEST_ASSERT(bean == bean1);
    QTEST_ASSERT(bean1.isMarried == false);
}

/**
 * @brief 测试 bool 类型数据在 json, map, bean 中间的互相转换，
 * 按照道理应该有六个测试案例产生
 */
void TestOrmBool::test_bean_json_map_convert()
{
    UserBean bean;
    bean.id = "hello world";
    bean.isMarried = true;

    // 1 bean -> map -> bean
    auto map1 = IConvertUtil::toMap(bean);
    QTEST_ASSERT(map1["id"] == bean.id);
    QTEST_ASSERT(map1["isMarried"] == bean.isMarried);

    auto bean1 = IConvertUtil::toBean<UserBean>(map1);
    QTEST_ASSERT(bean == bean1);

    // 2 bean -> json -> bean
    auto json1 = IConvertUtil::toJsonObject(bean1);
    qDebug() << json1;

    QTEST_ASSERT(json1["id"] == bean.id);
    QTEST_ASSERT(json1["isMarried"] == bean.isMarried);

    auto bean2 = IConvertUtil::toBean<UserBean>(json1);
    QTEST_ASSERT(bean2 == bean);

    // 3 map -> json -> bean
    auto json3 = IConvertUtil::toJsonObject(map1);
    QTEST_ASSERT(map1["id"].toString() == json3["id"].toString());
    QTEST_ASSERT(map1["isMarried"].toBool() == json3["isMarried"].toBool());

    auto bean3 = IConvertUtil::toBean<UserBean>(json3);
    QTEST_ASSERT(bean3 == bean);

    // 4 json -> map;
    auto map4 = IConvertUtil::toMap(json3);
    QTEST_ASSERT(map4 == map1);
}

void TestOrmBool::test_convertToMapOrJson()
{
    UserBean bean;
    bean.isMarried = false;

    model.insert(bean);

    UserBean bean1 = model.findOneByPriamaryKey(bean.id);
    auto map = IConvertUtil::toMap<UserBean>(bean1);
    qDebug() << map;
    auto json = IConvertUtil::toJsonObject(bean1);
    qDebug() << json;
}

void TestOrmBool::test_getBool_true()
{
    UserBean bean;
    bean.isMarried = true;
    model.insert(bean);
    auto query = model.getQuery();
    query.exec("select isMarried from UserBean");

    bool ok;
    bool value = IOrmUtil::getBool(query, &ok);
    QTEST_ASSERT(ok == true);
    QTEST_ASSERT(value == true);
}

void TestOrmBool::test_getBool_false()
{
    UserBean bean;
    bean.isMarried = false;
    model.insert(bean);
    auto query = model.getQuery();
    query.exec("select isMarried from UserBean");

    bool ok;
    bool value = IOrmUtil::getBool(query, &ok);
    QTEST_ASSERT(ok == true);
    QTEST_ASSERT(value == false);
}

// 查询单个值有非 1 个结果
void TestOrmBool::test_getBool_invalid()
{
    // 0 个结果
    auto query = model.getQuery();
    query.exec("select isMarried from UserBean");

    bool ok;
    bool value = IOrmUtil::getBool(query, &ok);
    qDebug() << value;
    QTEST_ASSERT(ok == false);

    // 多个结果
    QList<UserBean> beans;
    beans.append(UserBean());
    beans.append(UserBean());
    model.insert(beans);

    auto query2 = model.getQuery();
    query2.exec("select isMarried from UserBean");

    bool value2 = IOrmUtil::getBool(query, &ok);
    qDebug() << value2;
    QTEST_ASSERT(ok == false);
}

void TestOrmBool::test_getBools()
{
    QList<UserBean> beans;
    for(int i=0; i<10; i++){
        UserBean bean;
        bean.isMarried = ((i%2) == 0 ? false : true);
        beans.append(bean);
    }
    model.insert(beans);

    auto query = model.getQuery();
    query.exec("select isMarried from UserBean");

    bool ok;
    auto bools = IOrmUtil::getBoolList(query, &ok);
    qDebug() << bools << ok;
    QTEST_ASSERT(bools.length() == 10);
}
