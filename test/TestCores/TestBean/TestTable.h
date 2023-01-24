#pragma once

#include <IWebCore>
#include <QtTest>

#include "OneTable.h"

class TestTable : public ITestTaskInterface<TestTable>
{
    Q_OBJECT
    $AsTest(TestTable)
public:
    TestTable();

private slots:
    void init();
    void test_demo();
};

