#pragma once

#include <IWebCore>
#include <QtTest>
#include "UserBean.h"
#include "UserModel.h"

class TestOrmDateTime : public QObject
{
    Q_OBJECT
public:
    TestOrmDateTime();
    ~TestOrmDateTime() = default;

private slots:
    void init();
// ----------- date
    // 增加， 查找
    void test_insertAndFind();
    void test_three_type_insert_and_find();

    // json, bean, map convert
    void test_json_bean_convert();

    // test invalid value
    void test_json_map_bean_invalidValue();

    // 测试单个查找
    void test_find_dateTime();


private:
    UserModel model;
};

