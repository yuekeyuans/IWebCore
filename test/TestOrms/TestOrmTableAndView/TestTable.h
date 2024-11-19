#pragma once

#include <IWebCore>
#include <QtTest>

#include "TableModel.h"

class TestTable : public ITestTaskInterface<TestTable>
{
    Q_OBJECT
    $AsTest(TestTable)
public:
    TestTable();

private slots:
    void init();
    void test_insert();

private:
    TableModel model;
};

