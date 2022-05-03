#pragma once

#include <IWebCore>
#include <QtTest>
#include "UserBean.h"
#include "UserModel.h"

class TestOrmBool : public QObject
{
    Q_OBJECT
public:
    TestOrmBool();
    ~TestOrmBool() = default;

private slots:
    void init();
    // 基本
    void test_bool_field_true();
    void test_bool_field_false();

    // 转换
    void test_bean_json_map_convert();
    void test_convertToMapOrJson();

    // 查找
    void test_getBool_true();
    void test_getBool_false();
    void test_getBool_invalid();
    void test_getBools();

    // 还有什么要编写的？

private:
    UserModel model;
};

