#pragma once

#include <QtTest>
#include <IWebCore>

class TestConditionGroupBy : public ITestInterface<TestConditionGroupBy>
{
    Q_OBJECT
    $AsTest(TestConditionGroupBy)
public:
    TestConditionGroupBy();
private slots:
    void init();
};

