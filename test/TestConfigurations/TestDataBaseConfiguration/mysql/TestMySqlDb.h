#pragma once

#include <IWebCore>
#include <QtTest>
#include "DataBean.h"
#include "mysql/MySqlModel.h"

class TestMySqlDb : public ITestTaskInterface<TestMySqlDb>
{
    Q_OBJECT
    $AsTest(TestMySqlDb)
public:
    TestMySqlDb();

private slots:
    void init();
    void test_insertAndFetch();

private:
    MySqlModel model;
};

