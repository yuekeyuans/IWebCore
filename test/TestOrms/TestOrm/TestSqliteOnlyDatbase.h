#pragma once

#include <IWebCore>
#include <QtTest>
#include "PhoneBean.h"
#include "SqliteModel.h"

class TestSqliteOnlyDatbase : public ITestTaskInterface<TestSqliteOnlyDatbase>
{
    Q_OBJECT
    $AsTest(TestSqliteOnlyDatbase)
public:
    TestSqliteOnlyDatbase();

private slots:
    void init();
    void test1();

private:

private:
    SqliteModel model;
};

