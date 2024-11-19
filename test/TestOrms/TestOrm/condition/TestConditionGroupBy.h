#pragma once

#include <QtTest>
#include <IWebCore>

class TestConditionGroupBy : public ITestTaskInterface<TestConditionGroupBy>
{
    Q_OBJECT
    $AsTest(TestConditionGroupBy)
public:
    TestConditionGroupBy();
private slots:
    void init();
};

