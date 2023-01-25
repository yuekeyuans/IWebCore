#pragma once

#include <IWebCore>
#include <QtTest>
#include "DataBean.h"
#include "sqlite/SqliteModel.h"

class TestSqliteDb : public ITestTaskInterface<TestSqliteDb>
{
    Q_OBJECT
    $AsTest(TestSqliteDb)
public:
    TestSqliteDb();

private slots:
    void init();
    void insertAndFetch();

private:
    SqliteModel model;
};

